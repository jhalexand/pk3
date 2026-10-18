// The gameplay screen: client-side object state (PKClient's object list and
// PKClientObject extrapolation) plus drawing (GREngine, GRLifeDisplay).
//
// Feed it host messages with handle(msg); it renders to a 516x432 canvas.

import { OnscreenGraphic, loadImage } from './Sprites.js';
import { LetterWriter } from './LetterWriter.js';
import { ANIM, DIM, BACKGROUNDS } from '../engine/ids.js';

const ANIM_MS = 30; // GREngine's graphics timer
const NUMBER_WORDS = ['', 'ONE', 'TWO', 'THREE'];
const CHARACTER_NAMES = ['Liu Kang', 'Jade', 'Kabal', 'Cyrax', 'Reptile', 'Scorpion', 'Smoke', 'Sonya', 'Sub Zero'];

export const characterName = (type) => CHARACTER_NAMES[Math.trunc((type - 1) / 2)] || '';

export class GameView {
  constructor({ canvas, sprites, audio, players, background, font }) {
    this.canvas = canvas;
    this.ctx = canvas.getContext('2d');
    this.ctx.imageSmoothingEnabled = false;
    this.sprites = sprites;
    this.audio = audio;
    this.players = players; // paddle type per player number, or -1
    this.font = new LetterWriter(font);
    this.objects = new Map(); // id -> {type, x, y, vx, vy, anim, t, gfx}
    this.life = players.map((p) => (p < 0 ? -1 : 100));
    this.paused = false;
    this.showPaused = false; // only a player's pause shows the pause screen
    this.banner = null; // {text, until}
    this.animAcc = 0;
    this.lastFrame = 0;
    this.running = false;
    this.background = null;
    this.bgReady = loadImage(`assets/gfx/backgrounds/${BACKGROUNDS[background] || 'space'}.png`).then((img) => { this.background = img; });

    // GRLifeDisplay: left-side players fill from the left, right from the right.
    let left = 23, right = DIM.SCREEN_WIDTH - 123;
    this.hudX = players.map((p) => {
      if (p < 0) return null;
      if (p % 2 === 1) { const x = left; left += 123; return x; }
      const x = right; right -= 123; return x;
    });
  }

  start() {
    this.running = true;
    const loop = (t) => {
      if (!this.running) return;
      this.frame(t);
      requestAnimationFrame(loop);
    };
    requestAnimationFrame(loop);
  }

  stop() { this.running = false; }

  handle(m) {
    const now = performance.now();
    switch (m.t) {
      case 'add': {
        const o = { type: m.type, x: m.x, y: m.y, vx: m.vx, vy: m.vy, anim: ANIM.NOT, t: now };
        o.gfx = new OnscreenGraphic(this.sprites, m.type);
        this.objects.delete(m.id); // keep draw order = insertion order
        this.objects.set(m.id, o);
        break;
      }
      case 'update': {
        const o = this.objects.get(m.id);
        if (o) Object.assign(o, { x: m.x, y: m.y, vx: m.vx, vy: m.vy, t: now });
        break;
      }
      case 'sync':
        for (const [id, x, y, vx, vy] of m.objs) {
          const o = this.objects.get(id);
          if (o) Object.assign(o, { x, y, vx, vy, t: now });
        }
        break;
      case 'remove': this.objects.delete(m.id); break;
      case 'anim': {
        const o = this.objects.get(m.id);
        if (o) o.anim = m.anim;
        break;
      }
      case 'sound': this.audio?.play(m.id); break;
      case 'status': this.life = m.life; break;
      case 'pause':
        this.paused = m.paused;
        this.showPaused = m.paused && !m.quiet;
        for (const o of this.objects.values()) o.t = now;
        break;
      case 'round':
        this.objects.clear();
        this.paused = false;
        this.showPaused = false;
        this.score = m.score;
        this.showBanner(`ROUND ${NUMBER_WORDS[Math.min(m.n, 3)]}`, 1500);
        setTimeout(() => this.showBanner('FIGHT', 900), 1500);
        break;
      case 'roundEnd': {
        const name = this.winnerName(m.winner);
        this.score = m.score;
        this.showBanner(`${name} WINS`, 3000);
        this.audio?.announceWinner(name);
        break;
      }
    }
  }

  winnerName(team) {
    const t = this.players.find((p) => p >= 0 && (p % 2 === 1) === (team === 1));
    return t ? characterName(t) : `TEAM ${team}`;
  }

  showBanner(text, ms) {
    this.banner = { text, until: performance.now() + ms };
  }

  // PKClientObject::update: pos += elapsed * vector * 1e-8 (ns), i.e. v px per 100ms.
  extrapolate(now) {
    if (this.paused) return;
    for (const o of this.objects.values()) {
      const dt = now - o.t;
      o.x += (o.vx * dt) / 100;
      o.y += (o.vy * dt) / 100;
      o.t = now;
    }
  }

  frame(now) {
    this.extrapolate(now);
    if (!this.lastFrame) this.lastFrame = now;
    this.animAcc = Math.min(this.animAcc + now - this.lastFrame, 300);
    this.lastFrame = now;
    while (this.animAcc >= ANIM_MS) {
      this.animAcc -= ANIM_MS;
      if (!this.paused) for (const o of this.objects.values()) o.gfx.step(o);
    }
    this.draw(now);
  }

  draw(now) {
    const ctx = this.ctx;
    if (this.background) ctx.drawImage(this.background, 0, 0);
    else { ctx.fillStyle = '#000'; ctx.fillRect(0, 0, DIM.SCREEN_WIDTH, DIM.SCREEN_HEIGHT); }
    this.drawHud(ctx);
    for (const o of this.objects.values()) o.gfx.draw(ctx, o.x, o.y);
    if (this.banner && now < this.banner.until) {
      this.font.printCentered(ctx, DIM.SCREEN_WIDTH / 2, 200, this.banner.text, 3);
    }
    if (this.showPaused && !(this.banner && now < this.banner.until)) {
      this.font.printCentered(ctx, DIM.SCREEN_WIDTH / 2, 200, 'PAUSED', 3);
      this.font.printCentered(ctx, DIM.SCREEN_WIDTH / 2, 240, 'PRESS U', 2);
    }
  }

  drawHud(ctx) {
    this.players.forEach((type, i) => {
      const x = this.hudX[i];
      if (x === null) return;
      const life = Math.max(0, Math.min(100, this.life[i] ?? 0));
      ctx.fillStyle = '#0000ff';
      ctx.fillRect(x, 30, life, 20);
      ctx.fillStyle = '#ff0000';
      ctx.fillRect(x + life, 30, 100 - life, 20);
      this.font.print(ctx, x, 60, characterName(type));
    });
    // Round wins, shown as small markers under each side's bar.
    if (this.score) {
      ctx.fillStyle = '#ffcc00';
      for (let i = 0; i < this.score[0]; i++) ctx.fillRect(23 + i * 12, 72, 8, 8);
      for (let i = 0; i < this.score[1]; i++) ctx.fillRect(DIM.SCREEN_WIDTH - 23 - 8 - i * 12, 72, 8, 8);
    }
  }
}
