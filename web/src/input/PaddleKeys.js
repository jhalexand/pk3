// Port of src/gui/PKPaddleKeys.C and the per-character PK<Char>{Left,Right}Keys.h
// combo detectors. Combos are written once in terms of forward (F) and back (B);
// for the right-side player forward is the left arrow.
//
// Like the original, a key press immediately sends its basic action (punch,
// kick, ...) and special moves are recognised from the last five released
// keys, mostly when an attack key is released.

import { A, T } from '../engine/ids.js';

const NS_PER_MS = 1e6;

// Combo tables. seq is oldest -> newest, not counting the triggering key.
// on: 'release' (checked when `key` is released) or 'press' (checked when it
// is pressed, replacing the normal press action).
const COMBOS = {
  [T.LIU_KANG_1]: [
    { on: 'release', key: 'P', seq: ['F', 'F'], within: 1000, action: A.SPECIAL_1 }, // fireball
    { on: 'release', key: 'K', seq: ['F', 'F'], within: 1000, action: A.SPECIAL_3 }, // flying kick
    { on: 'release', key: 'K', heldFor: 1500, action: A.SPECIAL_2 },                // bicycle kick
  ],
  [T.JADE_1]: [
    { on: 'press', key: 'P', seq: ['B', 'B', 'F', 'F'], within: 500, action: A.SPECIAL_2 }, // triple shot
    { on: 'press', key: 'P', seq: ['B', 'F'], within: 500, action: A.SPECIAL_1 },
    { on: 'release', key: 'K', seq: ['B', 'F'], within: 500, action: A.SPECIAL_3 },         // shield
  ],
  [T.KABAL_1]: [
    { on: 'press', key: 'BL', seq: ['B', 'B', 'B'], within: 500, action: A.SPECIAL_3 }, // buzzsaw
    { on: 'release', key: 'P', seq: ['B', 'B'], within: 500, action: A.SPECIAL_1 },
    { on: 'release', key: 'K', seq: ['B', 'F'], within: 500, action: A.SPECIAL_2 },     // spin dash
  ],
  [T.CYRAX_1]: [
    // Fix: the original checked the plain B,B,K net first, so the
    // hold-punch variant below it could never fire.
    { on: 'release', key: 'K', seq: ['F', 'F'], holding: 'P', within: 500, action: A.SPECIAL_2 }, // bomb
    { on: 'release', key: 'K', seq: ['B', 'B'], holding: 'P', within: 500, action: A.SPECIAL_2 },
    { on: 'release', key: 'K', seq: ['B', 'B'], within: 500, action: A.SPECIAL_1 },                // net
  ],
  [T.REPTILE_1]: [
    { on: 'release', key: 'P', seq: ['F', 'F'], within: 500, action: A.SPECIAL_1 },
    { on: 'release', key: 'K', seq: ['U', 'U', 'D'], within: 500, action: A.SPECIAL_2 }, // invisibility
  ],
  [T.SUB_ZERO_1]: [
    { on: 'release', key: 'P', seq: ['D', 'F'], within: 500, action: A.SPECIAL_1 },      // ice ball
    { on: 'release', key: 'P', seq: ['F', 'D', 'B'], within: 500, action: A.SPECIAL_2 }, // homing ice
    { on: 'release', key: 'K', seq: ['D', 'B'], within: 500, action: A.SPECIAL_3 },
  ],
};

export function combosFor(type) {
  const base = type % 2 === 1 ? type : type - 1;
  return COMBOS[base] || COMBOS[T.LIU_KANG_1];
}

// Human-readable move list for the help screen: one entry per special move,
// in order (1, 2, 3). A move with more than one input lists them all.
export function moveList(type) {
  const name = { P: 'Punch', K: 'Kick', BL: 'Block', F: '→', B: '←', U: '↑', D: '↓' };
  const byAction = new Map();
  for (const c of combosFor(type)) {
    const keys = c.heldFor ? `hold ${name[c.key]} ${c.heldFor / 1000}s` :
      [...c.seq.map((k) => name[k]), (c.holding ? `${name[c.key]} (holding ${name[c.holding]})` : name[c.key])].join(' ');
    byAction.set(c.action, [...(byAction.get(c.action) || []), keys]);
  }
  return [...byAction]
    .sort(([a], [b]) => a - b)
    .map(([action, keys]) => ({ action, keys: keys.join(' or ') }));
}

export class PaddleKeys {
  // team 1 plays on the left (forward = right arrow).
  constructor({ type, sendAction, clock = () => performance.now() * NS_PER_MS }) {
    this.combos = combosFor(type);
    this.forward = type % 2 === 1 ? 'RIGHT' : 'LEFT';
    this.back = type % 2 === 1 ? 'LEFT' : 'RIGHT';
    this.send = sendAction;
    this.clock = clock;
    this.down = new Set();
    this.downtime = {};
    this.lastkeys = [];   // newest first, up to 5
    this.lasttime = [];
  }

  // Map an abstract combo token to a physical key for this side.
  phys(tok) {
    return { F: this.forward, B: this.back, U: 'UP', D: 'DOWN', P: 'PUNCH', K: 'KICK', BL: 'BLOCK' }[tok];
  }

  // seq oldest->newest must match hist (newest first) starting at `offset`.
  matches(seq, offset, refTime, within) {
    for (let i = 0; i < seq.length; i++) {
      const h = offset + (seq.length - 1 - i);
      if (this.lastkeys[h] !== this.phys(seq[i])) return false;
      if (refTime - this.lasttime[h] >= within * NS_PER_MS) return false;
    }
    return true;
  }

  keyPress(key) {
    if (this.down.has(key)) return; // ignore auto-repeat
    const now = this.clock();
    this.down.add(key);
    this.downtime[key] = now;
    for (const c of this.combos) {
      if (c.on === 'press' && this.phys(c.key) === key && this.matches(c.seq, 0, now, c.within)) {
        this.send(c.action);
        return;
      }
    }
    const act = {
      UP: A.UP, DOWN: A.DOWN, LEFT: A.LEFT, RIGHT: A.RIGHT,
      BLOCK: A.BLOCK, PUNCH: A.PUNCH, KICK: A.KICK, PAUSE: A.PAUSE, UNPAUSE: A.UNPAUSE,
    }[key];
    if (act !== undefined) this.send(act);
  }

  keyRelease(key) {
    if (!this.down.has(key)) return;
    const now = this.clock();
    this.down.delete(key);
    this.lastkeys.unshift(key);
    this.lasttime.unshift(now);
    this.lastkeys.length = Math.min(this.lastkeys.length, 5);
    this.lasttime.length = Math.min(this.lasttime.length, 5);

    if (key === 'PUNCH' && this.down.has('DOWN')) return this.send(A.CUT_DOWN);
    if (key === 'PUNCH' && this.down.has('UP')) return this.send(A.CUT_UP);
    if (key === 'KICK' && this.down.has(this.back)) return this.send(A.SWEEP);
    for (const c of this.combos) {
      if (c.on !== 'release' || this.phys(c.key) !== key) continue;
      if (c.holding && !this.down.has(this.phys(c.holding))) continue;
      if (c.heldFor ? now - this.downtime[key] > c.heldFor * NS_PER_MS : this.matches(c.seq, 1, now, c.within)) {
        return this.send(c.action);
      }
    }
    this.doDefaults(key);
  }

  doDefaults(key) {
    // Fix: releasing one direction while still holding the opposite one used
    // to stop the paddle dead; now it keeps going the held way.
    if (key === 'UP' || key === 'DOWN') {
      const other = key === 'UP' ? 'DOWN' : 'UP';
      this.send(this.down.has(other) ? A[other] : A.STOP_VERTICAL);
    } else if (key === 'LEFT' || key === 'RIGHT') {
      const other = key === 'LEFT' ? 'RIGHT' : 'LEFT';
      this.send(this.down.has(other) ? A[other] : A.STOP_HORIZONTAL);
    } else if (key === 'BLOCK') {
      this.send(A.UNBLOCK);
    }
  }

  releaseAll() {
    for (const k of [...this.down]) this.keyRelease(k);
  }
}

// Default key bindings from PKClient::enterGamePlay.
export const KEYMAP = {
  ArrowUp: 'UP', ArrowDown: 'DOWN', ArrowLeft: 'LEFT', ArrowRight: 'RIGHT',
  a: 'PUNCH', s: 'KICK', d: 'BLOCK', p: 'PAUSE', u: 'UNPAUSE',
};

// Attach keyboard listeners; returns a function that detaches them.
export function bindKeyboard(target, keys) {
  const keyOf = (e) => KEYMAP[e.key.length === 1 ? e.key.toLowerCase() : e.key];
  const down = (e) => {
    const k = keyOf(e);
    if (!k || e.target.closest?.('input, textarea')) return;
    e.preventDefault();
    if (!e.repeat) keys.keyPress(k);
  };
  const up = (e) => {
    const k = keyOf(e);
    if (!k) return;
    e.preventDefault();
    keys.keyRelease(k);
  };
  const blur = () => keys.releaseAll();
  target.addEventListener('keydown', down);
  target.addEventListener('keyup', up);
  window.addEventListener('blur', blur);
  return () => {
    target.removeEventListener('keydown', down);
    target.removeEventListener('keyup', up);
    window.removeEventListener('blur', blur);
  };
}
