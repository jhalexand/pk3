// Port of PKPhysicsInterface (Benoit Hudson, 1997). The C++ source was lost;
// this was recovered from the SPARC disassembly of lib/libpkphysics.so.
// See tools/physics-disasm.md for the derivation.

import { PHYSICS_SPEED_FUDGE, T } from './ids.js';

const HALF_SCREEN_X = 258; // .rodata 0x9500
const HALF_SCREEN_Y = 216; // .rodata 0x9510
const MAX_DEFLECT = 1.0471975333333334; // .rodata 0x9518, PI/3

export class Physics {
  constructor(clock) {
    this.clock = clock; // returns nanoseconds
  }

  // pos += vector * (now - timestamp) * 1e-8;  timestamp = now
  update(obj) {
    const now = this.clock();
    const dt = (now - obj.timestamp) * PHYSICS_SPEED_FUDGE;
    obj.pos.x += obj.vector.x * dt;
    obj.pos.y += obj.vector.y * dt;
    obj.timestamp = now;
  }

  // Strict axis-aligned box overlap. Half-extents are (size + adjust) / 2.
  intersect(a, b) {
    const aw = (a.width + a.widthAdjust) / 2;
    const bw = (b.width + b.widthAdjust) / 2;
    const ah = (a.height + a.heightAdjust) / 2;
    const bh = (b.height + b.heightAdjust) / 2;
    return (
      a.pos.x - aw < b.pos.x + bw &&
      a.pos.x + aw > b.pos.x - bw &&
      a.pos.y - ah < b.pos.y + bh &&
      a.pos.y + ah > b.pos.y - bh
    );
  }

  // Reflect the component of velocity that heads toward the wall. Vertical
  // walls flip x if the ball is moving away from the screen centre; otherwise
  // (horizontal walls, or a vertical wall that didn't flip) flip y likewise.
  bounceWithWall(ball, wall) {
    const v = ball.vector;
    const p = ball.pos;
    if (wall.typeID === T.WALL_VERTICAL &&
        ((p.x < HALF_SCREEN_X && v.x < 0) || (p.x > HALF_SCREEN_X && v.x > 0))) {
      v.x = -v.x;
    } else if ((p.y < HALF_SCREEN_Y && v.y < 0) || (p.y > HALF_SCREEN_Y && v.y > 0)) {
      v.y = -v.y;
    }
  }

  // Pong-style deflection: the angle depends on where the ball hit the paddle,
  // up to +/-60 degrees at the paddle's ends. Speed is preserved.
  bounceWithPlayer(ball, player) {
    const dx = ball.pos.x - player.pos.x;
    const dy = ball.pos.y - player.pos.y;
    const old = ball.vector;
    const angle = (dy * MAX_DEFLECT) / Math.trunc(player.height / 2);
    const speed = Math.hypot(old.x, old.y);
    let nx = speed * Math.cos(angle);
    const ny = speed * Math.sin(angle);
    if (old.x > 0 && nx > 0) nx = -nx;
    if (dx > 0 && nx < 0) nx = -nx;
    if (dx < 0 && nx > 0) nx = -nx;
    ball.vector = { x: nx, y: ny };
  }
}
