// Port of src/ai/PKAIClient.C, the "dumb" computer opponent. Like the
// original it is just another client: it watches the host's message stream
// and sends actions back.
//
// Every 100 ms it moves toward the ball, and every 5 s it fires its first
// special move if an opponent is roughly level with it.
//
// Fix: the original's update handler looked objects up but never stored
// their new position or velocity, so it chased a ball that never bounced.

import { A, T, isPaddle, ANIM } from '../engine/ids.js';

const UPDATE_MS = 100;
const FIRE_RATE_MS = 5000;
const FIRE_OFF = 25;

export class AIClient {
  constructor({ playerNum, sendAction }) {
    this.playerNum = playerNum;
    this.send = sendAction;
    this.objects = new Map();
    this.hidden = new Set();
    this.lastFire = performance.now();
    this.paused = false;
    this.timer = setInterval(() => this.think(), UPDATE_MS);
  }

  stop() { clearInterval(this.timer); }

  handle(m) {
    const now = performance.now();
    switch (m.t) {
      case 'add':
      case 'update': {
        const o = this.objects.get(m.id) || { type: m.type };
        Object.assign(o, { x: m.x, y: m.y, vx: m.vx, vy: m.vy, t: now });
        this.objects.set(m.id, o);
        break;
      }
      case 'sync':
        for (const [id, x, y, vx, vy] of m.objs) {
          const o = this.objects.get(id);
          if (o) Object.assign(o, { x, y, vx, vy, t: now });
        }
        break;
      case 'remove': this.objects.delete(m.id); this.hidden.delete(m.id); break;
      case 'anim':
        if (m.anim === ANIM.INVISIBLE) this.hidden.add(m.id);
        else if (m.anim === ANIM.VISIBLE) this.hidden.delete(m.id);
        break;
      case 'round': this.objects.clear(); this.hidden.clear(); this.paused = false; break;
      case 'pause': this.paused = m.paused; break;
    }
  }

  // Player objects are added first, so the AI's object id is its player number.
  self() { return this.objects.get(this.playerNum); }

  where(o, now) {
    const dt = now - o.t;
    return { x: o.x + (o.vx * dt) / 100, y: o.y + (o.vy * dt) / 100 };
  }

  think() {
    if (this.paused) return;
    const self = this.self();
    const ball = [...this.objects.values()].find((o) => o.type === T.BALL);
    if (!self || !ball) return;
    const now = performance.now();
    const me = this.where(self, now);
    const b = this.where(ball, now);
    const direction = Math.sign(self.vy);
    if (b.y > me.y && direction !== 1) this.send(A.DOWN);
    else if (b.y < me.y && direction !== -1) this.send(A.UP);

    if (now - this.lastFire > FIRE_RATE_MS) {
      for (const [id, o] of this.objects) {
        if (id === this.playerNum || !isPaddle(o.type) || this.hidden.has(id)) continue;
        if ((o.type % 2) === (self.type % 2)) continue; // teammates
        if (Math.abs(this.where(o, now).y - me.y) < FIRE_OFF) {
          this.send(A.SPECIAL_1);
          this.lastFire = now;
          break;
        }
      }
    }
  }
}
