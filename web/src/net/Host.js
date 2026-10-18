// The host: what pkd (lobby) and pkgameserver (engine) did, now running in
// the browser of whoever created the game. Two slots: the host is player 0
// (left side), the other slot is a remote human or the AI.

import { RoundEngine, TICK_MS } from '../engine/RoundEngine.js';
import { CHARACTERS, BACKGROUNDS, paddleForTeam, T } from '../engine/ids.js';
import { AIClient } from '../ai/AIClient.js';
import { localPair, hostPeer, makeCode } from './links.js';

const VS_SCREEN_MS = 2500;
const clock = () => performance.now() * 1e6;

export class Host {
  constructor({ name, multiplayer }) {
    this.multiplayer = multiplayer;
    this.slots = [
      { name, type: T.LIU_KANG_1, ai: false, link: null },
      { name: '', type: T.SUB_ZERO_1, ai: false, link: null },
    ];
    this.code = null;
    this.peer = null;
    this.round = null;
    this.loop = null;
    this.ai = null;
    this.inGame = false;
    const [hostSide, clientSide] = localPair();
    this.attach(0, hostSide);
    this.localLink = clientSide; // given to the host's own Client
    if (!multiplayer) this.computerize(1);
  }

  async open() {
    if (!this.multiplayer) return;
    for (let tries = 0; tries < 3 && !this.peer; tries++) {
      this.code = makeCode();
      try {
        this.peer = await hostPeer(this.code, (link) => this.onJoin(link));
      } catch (e) {
        if (tries === 2 || !/in use/.test(e.message)) throw e;
      }
    }
  }

  onJoin(link) {
    const slot = this.slots[1];
    if (slot.link || this.inGame) {
      link.send({ t: 'error', text: slot.link ? 'That game is full.' : 'That game has already started.' });
      setTimeout(() => link.close(), 500);
      return;
    }
    if (slot.ai) this.decomputerize();
    this.attach(1, link);
  }

  attach(n, link) {
    const slot = this.slots[n];
    slot.link = link;
    link.onMessage = (m) => this.receive(n, m);
    link.onClose = () => {
      if (slot.link !== link) return;
      const who = slot.name || 'Your opponent';
      slot.link = null;
      slot.name = '';
      if (n === 1) {
        if (this.inGame) this.abortGame(`${who} disconnected.`);
        this.broadcast({ t: 'chat', name: '', text: `${who} left.` });
        this.sendLobby();
      }
    };
  }

  receive(n, m) {
    const slot = this.slots[n];
    switch (m.t) {
      case 'hello':
        // Reply only once the client is listening (it says hello first).
        slot.name = String(m.name || 'Player').slice(0, 16);
        slot.link?.send({ t: 'welcome', you: n, code: this.code, multiplayer: this.multiplayer });
        if (n === 1) this.broadcast({ t: 'chat', name: '', text: `${slot.name} joined.` });
        this.sendLobby();
        break;
      case 'paddle':
        if (!this.inGame && CHARACTERS.some((c) => c.type === m.type)) {
          // The host also picks the computer player's fighter.
          const target = n === 0 && m.slot === 1 && this.slots[1].ai ? 1 : n;
          this.slots[target].type = m.type;
          this.sendLobby();
        }
        break;
      case 'chat':
        this.broadcast({ t: 'chat', name: slot.name, text: String(m.text).slice(0, 200) });
        break;
      case 'action':
        if (this.inGame) this.round?.handleAction(n, m.a);
        break;
      // Host-only controls (from the host's own client).
      case 'computerize': if (n === 0) this.computerize(1); break;
      case 'reject': if (n === 0) this.reject(); break;
      case 'start': if (n === 0) this.startGame(); break;
    }
  }

  computerize(n) {
    const slot = this.slots[n];
    if (slot.link) return;
    slot.ai = true;
    slot.name = 'Computer';
    this.sendLobby();
  }

  decomputerize() {
    Object.assign(this.slots[1], { ai: false, name: '' });
  }

  reject() {
    const slot = this.slots[1];
    if (slot.ai) { this.decomputerize(); this.sendLobby(); return; }
    if (slot.link) {
      slot.link.send({ t: 'error', text: 'The host removed you from the game.' });
      const l = slot.link;
      setTimeout(() => l.close(), 300);
    }
  }

  sendLobby() {
    const slots = this.slots.map((s) => ({ name: s.name, type: s.type, ai: s.ai, present: !!(s.link || s.ai) }));
    this.broadcast({ t: 'lobby', slots, code: this.code, inGame: this.inGame });
  }

  broadcast(m) {
    for (const s of this.slots) s.link?.send(m);
    if (this.ai) this.ai.handle(m);
  }

  canStart() { return this.slots.every((s) => s.link || s.ai) && !this.inGame; }

  startGame() {
    if (!this.canStart()) return;
    this.inGame = true;
    const players = this.slots.map((s, i) => paddleForTeam(s.type, i === 0 ? 1 : 2));
    const background = Math.floor(Math.random() * BACKGROUNDS.length);
    if (this.slots[1].ai) {
      this.ai = new AIClient({ playerNum: 1, sendAction: (a) => this.round?.handleAction(1, a) });
    }
    this.broadcast({ t: 'start', players, names: this.slots.map((s) => s.name), background });
    this.round = new RoundEngine({ players, clock, emit: (m) => this.onEngine(m) });
    this.startTimer = setTimeout(() => {
      this.round.start();
      this.loop = setInterval(() => this.round.tick(), TICK_MS);
    }, VS_SCREEN_MS);
  }

  onEngine(m) {
    this.broadcast(m);
    if (m.t === 'matchEnd') this.finishGame();
  }

  finishGame() {
    clearInterval(this.loop);
    clearTimeout(this.startTimer);
    this.loop = null;
    this.round?.stop();
    this.round = null;
    this.ai?.stop();
    this.ai = null;
    this.inGame = false;
    this.sendLobby();
  }

  abortGame(text) {
    if (!this.inGame) return;
    this.finishGame();
    this.broadcast({ t: 'abort', text });
  }

  close() {
    this.finishGame();
    for (const s of this.slots) s.link?.close();
    this.peer?.destroy();
  }
}
