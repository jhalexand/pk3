// The client application: screen flow from PKClient.C (opening -> konnect ->
// game gathering -> gameplay -> back), talking to a Host over a link.

import { SpriteSet, loadImage } from '../client/Sprites.js';
import { GameView, characterName } from '../client/GameView.js';
import { LetterWriter } from '../client/LetterWriter.js';
import { Audio } from '../client/Audio.js';
import { PaddleKeys, bindKeyboard, moveList } from '../input/PaddleKeys.js';
import { Host } from '../net/Host.js';
import { joinPeer, normalizeCode, CODE_LENGTH } from '../net/links.js';
import { CHARACTERS, A, SND } from '../engine/ids.js';

const $ = (s) => document.querySelector(s);
const audio = new Audio();
const SCREENS = ['opening', 'konnect', 'gather', 'vs', 'game', 'gameover', 'credits'];
const MUSIC = { opening: 'introMusic', konnect: 'introMusic', gather: 'selectmusic' };
const SPECIAL_NAMES = { [A.SPECIAL_1]: 'Special 1', [A.SPECIAL_2]: 'Special 2', [A.SPECIAL_3]: 'Special 3' };

const state = {
  name: '',
  host: null,      // Host, if this browser runs the game
  link: null,      // our link to the host
  you: 0,
  lobby: null,
  multiplayer: false,
  view: null,
  unbindKeys: null,
  players: null,
  leaving: false,
};

let sprites, font, letters;

// --- screens ---------------------------------------------------------------
function show(name) {
  for (const s of SCREENS) $(`#screen-${s}`).hidden = s !== name;
  state.screen = name;
  fit();
  if (name in MUSIC) audio.playMusic(MUSIC[name]);
  else audio.stopMusic();
  const focus = { opening: '#btn-single', konnect: '#konnect-name', gameover: '#btn-continue', credits: '#btn-credits-back' }[name];
  if (focus) $(focus).focus();
}

// Scale fixed-size pixel-art windows to fit the browser.
function fit() {
  const win = $(`#screen-${state.screen}`);
  if (!win) return;
  win.style.zoom = '';
  if (!['opening', 'vs', 'game', 'gameover'].includes(state.screen)) return;
  const w = win.offsetWidth, h = win.offsetHeight;
  const avail = Math.min((innerWidth - 32) / w, (innerHeight - 32) / h);
  const scale = avail >= 1 ? Math.max(1, Math.floor(avail * 2) / 2) : avail;
  win.style.zoom = String(scale);
}
addEventListener('resize', fit);

function dialog(text) {
  $('#dialog-text').textContent = text;
  $('#dialog').hidden = false;
  $('#dialog-ok').focus();
}
$('#dialog-ok').onclick = () => { $('#dialog').hidden = true; };

// --- leaving / connecting ------------------------------------------------
function disconnect() {
  state.leaving = true;
  endGameView();
  state.link?.close();
  state.host?.close();
  state.link = state.host = state.lobby = null;
  state.leaving = false;
}

function connect(link) {
  state.link = link;
  link.onMessage = onMessage;
  link.onClose = () => {
    if (state.leaving) return;
    state.link = null;
    disconnect();
    show('opening');
    dialog('Lost the connection to the game host.');
  };
  link.send({ t: 'hello', name: state.name });
}

function send(m) { state.link?.send(m); }

// --- messages from the host ----------------------------------------------
function onMessage(m) {
  switch (m.t) {
    case 'welcome':
      state.you = m.you;
      state.multiplayer = m.multiplayer;
      $('#chat-log').replaceChildren();
      show('gather');
      break;
    case 'lobby':
      state.lobby = m;
      if (state.screen === 'gather') renderGather();
      break;
    case 'chat': addChat(m.name, m.text); break;
    case 'start': beginMatch(m); break;
    case 'matchEnd':
      state.view?.handle(m);
      setTimeout(() => gameOver(m), 1500);
      break;
    case 'abort':
      endGameView();
      show('gather');
      renderGather();
      dialog(m.text);
      break;
    case 'error':
      state.leaving = true;
      disconnect();
      show('opening');
      dialog(m.text);
      break;
    default:
      state.view?.handle(m);
  }
}

// --- 1. opening ----------------------------------------------------------
$('#btn-single').onclick = () => {
  state.name = state.name || loadName() || 'Player';
  state.host = new Host({ name: state.name, multiplayer: false });
  connect(state.host.localLink);
};
$('#btn-multi').onclick = () => {
  $('#konnect-name').value = loadName();
  $('#konnect-status').textContent = '';
  show('konnect');
};
$('#btn-quit').onclick = () => show('credits');
$('#btn-credits-back').onclick = () => show('opening');

// --- 2. konnect ----------------------------------------------------------
function loadName() { try { return localStorage.getItem('pk3.name') || ''; } catch { return ''; } }
function takeName() {
  const name = $('#konnect-name').value.trim().slice(0, 16);
  if (!name) { $('#konnect-status').textContent = 'Enter a user name first.'; $('#konnect-name').focus(); return null; }
  state.name = name;
  try { localStorage.setItem('pk3.name', name); } catch {}
  return name;
}
function busy(on, text = '') {
  for (const b of ['#btn-create', '#btn-join']) $(b).disabled = on;
  $('#konnect-status').textContent = text;
}
$('#btn-create').onclick = async () => {
  if (!takeName()) return;
  busy(true, 'Creating game…');
  const host = new Host({ name: state.name, multiplayer: true });
  try {
    await host.open();
  } catch (e) {
    host.close();
    busy(false, e.message);
    return;
  }
  busy(false);
  state.host = host;
  connect(host.localLink);
};
$('#btn-join').onclick = async () => {
  if (!takeName()) return;
  const code = normalizeCode($('#konnect-code').value);
  if (code.length !== CODE_LENGTH) {
    $('#konnect-status').textContent = `Game codes are ${CODE_LENGTH} letters and numbers.`;
    $('#konnect-code').focus();
    return;
  }
  busy(true, 'Konnecting…');
  try {
    const link = await joinPeer(code);
    busy(false);
    connect(link);
  } catch (e) {
    busy(false, e.message);
  }
};
$('#konnect-code').addEventListener('keydown', (e) => { if (e.key === 'Enter') $('#btn-join').click(); });
$('#konnect-name').addEventListener('keydown', (e) => { if (e.key === 'Enter') $('#konnect-code').focus(); });
$('#btn-konnect-back').onclick = () => show('opening');

// --- 3. game gathering ---------------------------------------------------
function renderGather() {
  const lobby = state.lobby;
  if (!lobby) return;
  const isHost = !!state.host;
  $('#code-banner').hidden = !lobby.code;
  $('#chat-box').hidden = !state.multiplayer;
  $('#code-text').textContent = lobby.code || '';
  lobby.slots.forEach((slot, i) => renderPanel($(`.player-panel[data-slot="${i}"]`), slot, i, isHost));
  const ready = lobby.slots.every((s) => s.present);
  $('#btn-start').hidden = !isHost;
  $('#btn-start').disabled = !ready || lobby.inGame;
  $('#start-hint').textContent = isHost
    ? (ready ? 'Press Start when you are both ready.' : 'Waiting for an opponent to join… or Computerize one.')
    : 'Waiting for the host to start the game.';
  const mine = lobby.slots[state.you];
  $('#moves-title').textContent = `${characterName(mine.type)}'s special moves`;
  $('#moves-list').replaceChildren(...moveList(mine.type).map((mv) => {
    const tr = document.createElement('tr');
    tr.innerHTML = '<td></td><td></td>';
    tr.cells[0].textContent = mv.keys;
    tr.cells[1].textContent = SPECIAL_NAMES[mv.action];
    return tr;
  }));
}

function renderPanel(el, slot, i, isHost) {
  const mine = i === state.you;
  const canPick = mine || (isHost && slot.ai);
  el.replaceChildren();
  const left = document.createElement('div');
  const sel = document.createElement('select');
  sel.setAttribute('aria-label', `Fighter for player ${i + 1}`);
  for (const c of CHARACTERS) sel.add(new Option(c.name, c.type, false, c.type === slot.type));
  sel.disabled = !canPick || !slot.present;
  sel.onchange = () => send({ t: 'paddle', type: Number(sel.value), slot: i });
  const portrait = document.createElement('div');
  portrait.className = 'portrait';
  const img = new Image();
  const ch = CHARACTERS.find((c) => c.type === slot.type);
  img.src = `assets/gfx/paddles/startup/${slot.present && ch ? ch.portrait : 'blank'}.png`;
  img.alt = slot.present && ch ? ch.name : 'Empty slot';
  if (i === 1) img.style.transform = 'scaleX(-1)';
  portrait.append(img);
  left.append(sel, portrait);

  const info = document.createElement('div');
  info.className = 'info';
  const name = document.createElement('div');
  name.className = 'name';
  name.textContent = slot.present ? slot.name || 'Player' : 'Waiting for player…';
  const side = document.createElement('div');
  side.className = 'side';
  side.textContent = i === 0 ? 'Team 1 · left side' : 'Team 2 · right side';
  info.append(name, side);
  if (mine) {
    const you = document.createElement('span');
    you.className = 'you';
    you.textContent = 'YOU';
    info.append(you);
  }
  if (isHost && i === 1 && state.multiplayer) {
    if (!slot.present) info.append(button('Computerize', () => send({ t: 'computerize' })));
    else info.append(button(slot.ai ? 'Remove computer' : 'Reject', () => send({ t: 'reject' })));
  }
  el.append(left, info);
}

function button(text, onclick) {
  const b = document.createElement('button');
  b.className = 'motif-btn';
  b.textContent = text;
  b.onclick = onclick;
  return b;
}

function addChat(name, text) {
  const line = document.createElement('div');
  if (name) line.textContent = `${name}: ${text}`;
  else { line.className = 'sys'; line.textContent = text; }
  const log = $('#chat-log');
  log.append(line);
  log.scrollTop = log.scrollHeight;
}
$('#chat-input').addEventListener('keydown', (e) => {
  if (e.key !== 'Enter') return;
  const text = e.target.value.trim();
  if (text) send({ t: 'chat', text });
  e.target.value = '';
});
$('#btn-start').onclick = () => send({ t: 'start' });
$('#btn-cancel').onclick = () => { disconnect(); show('opening'); };
$('#btn-copy-code').onclick = async () => {
  try {
    await navigator.clipboard.writeText(state.lobby.code);
    $('#code-hint').textContent = 'Copied. Send it to your opponent.';
  } catch {
    $('#code-hint').textContent = 'Select the code and copy it.';
  }
};

// --- 4. match ------------------------------------------------------------
function beginMatch(m) {
  state.players = m.players;
  // VS splash with the two fighters' portraits.
  const [l, r] = m.players.map((t) => CHARACTERS.find((c) => c.type === (t % 2 ? t : t - 1)));
  $('#vs-left').src = `assets/gfx/paddles/startup/${l.portrait}.png`;
  $('#vs-right').src = `assets/gfx/paddles/startup/${r.portrait}.png`;
  const vc = $('#vs-names').getContext('2d');
  vc.clearRect(0, 0, 516, 432);
  letters.printCentered(vc, 131, 320, l.name, 2);
  letters.printCentered(vc, 385, 320, r.name, 2);
  letters.printCentered(vc, 131, 345, m.names[0] || '', 1);
  letters.printCentered(vc, 385, 345, m.names[1] || '', 1);
  show('vs');
  audio.play(SND.TOASTY);

  endGameView();
  state.view = new GameView({
    canvas: $('#game-canvas'), sprites, audio, players: m.players, background: m.background, font,
  });
  setTimeout(() => {
    if (!state.view) return;
    show('game');
    state.view.start();
    const keys = new PaddleKeys({ type: m.players[state.you], sendAction: (a) => send({ t: 'action', a }) });
    state.unbindKeys = bindKeyboard(document, keys);
  }, 2400);
}

function endGameView() {
  state.unbindKeys?.();
  state.unbindKeys = null;
  state.view?.stop();
  state.view = null;
}

function gameOver(m) {
  endGameView();
  const c = $('#gameover-text').getContext('2d');
  c.clearRect(0, 0, 400, 40);
  const winnerType = state.players.find((t) => (t % 2 === 1) === (m.winner === 1));
  const youWon = (state.you === 0) === (m.winner === 1);
  letters.printCentered(c, 200, 4, `${characterName(winnerType)} WINS`, 2);
  const flawless = Math.min(...m.score) === 0;
  letters.printCentered(c, 200, 26, youWon ? (flawless ? 'YOU WIN TWO ROUNDS TO NONE' : 'YOU WIN') : 'NICE TRY', 1);
  show('gameover');
}
$('#btn-continue').onclick = () => {
  if (state.link) { show('gather'); renderGather(); }
  else show('opening');
};
$('#btn-game-quit').onclick = () => { disconnect(); show('opening'); };

$('#btn-mute').onclick = () => {
  audio.setMuted(!audio.muted);
  syncMute();
};
function syncMute() {
  $('#btn-mute').textContent = audio.muted ? 'Sound off' : 'Sound on';
  $('#btn-mute').setAttribute('aria-pressed', String(audio.muted));
}

// Audio can only start after a user gesture.
addEventListener('pointerdown', () => audio.unlock(), { capture: true });
addEventListener('keydown', () => audio.unlock(), { capture: true });

// Leaving the tab or the browser suspends the audio and pauses a game in
// progress. Coming back resumes the audio; the game stays paused until a
// player presses U.
let away = false;
function setAway(a) {
  if (a === away) return;
  away = a;
  audio.setBackground(away);
  if (away && state.view) send({ t: 'action', a: A.PAUSE });
}
document.addEventListener('visibilitychange', () => setAway(document.hidden || !document.hasFocus()));
addEventListener('blur', () => setAway(true));
addEventListener('focus', () => setAway(document.hidden));

// --- boot ----------------------------------------------------------------
(async () => {
  syncMute();
  [sprites, font] = await Promise.all([SpriteSet.load(), loadImage('assets/gfx/objects/phrases2.png')]);
  letters = new LetterWriter(font);
  state.name = loadName();
  show('opening');
  // A game code in the URL (#ABCDE) goes straight to joining.
  const code = normalizeCode(location.hash.slice(1));
  if (code.length === CODE_LENGTH) {
    $('#konnect-name').value = state.name;
    $('#konnect-code').value = code;
    show('konnect');
  }
})().catch((e) => dialog(`Could not load the game: ${e.message}`));
