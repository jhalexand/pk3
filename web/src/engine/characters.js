// Ports of the GE<Char>{Left,Right}Player classes. The C++ had a separate,
// near-identical class per side; here one class per character uses
// this.dir (+1 for the left/team 1 player, -1 for the right) to mirror.

import { Player } from './Player.js';
import { Projectile, SZProjectile, CyraxNet, CyraxBomb } from './objects.js';
import { T, DIM, INJURY, SND, ANIM } from './ids.js';

// Picks the left or right variant of a type id.
const side = (p, leftType) => (p.team === 1 ? leftType : leftType + 1);

// Shared by Liu Kang and Kabal: a dash that locks out other actions.
class DashingPlayer extends Player {
  constructor(engine, opts) {
    super(engine, opts);
    this.dashing = false;
  }
  endDash() {
    if (this.dashing) this.engine.broadcastAnimateObject(this.id, ANIM.NOT);
    this.injury = 0;
    this.dashing = false;
  }
  dash(anim, speed, injury) {
    this.dashing = true;
    this.injury = injury;
    this.engine.broadcastAnimateObject(this.id, anim);
    this.setVector(this.dir * speed, 0);
    this.engine.broadcastUpdate(this);
  }
}
for (const m of ['moveUp', 'moveDown', 'moveLeft', 'moveRight', 'stopVertical', 'stopHorizontal',
  'punch', 'kick', 'uppercut', 'lowercut', 'sweep', 'block', 'unblock']) {
  DashingPlayer.prototype[m] = function (...args) {
    if (!this.dashing) Player.prototype[m].apply(this, args);
  };
}

export class LiuKang extends DashingPlayer {
  constructor(engine, opts) { super(engine, { ...opts, type: opts.team === 1 ? T.LIU_KANG_1 : T.LIU_KANG_2 }); }
  intersectWithWall(wall) {
    this.stop();
    this.endDash();
    this.bounceBack(wall);
  }
  // Fix: the original right-side Liu Kang reset his animation on every touch,
  // even when not kicking; both sides now behave like the left one.
  intersectWithPlayer(player) {
    super.intersectWithPlayer(player);
    this.endDash();
  }
  intersectWithProjectile(proj) {
    this.endDash();
    super.intersectWithProjectile(proj);
  }
  // Fireball
  specialMove1() {
    this.engine.addObject(new Projectile(this.engine, {
      type: side(this, T.LK_LEFT_PROJECTILE), injury: INJURY.DEFAULT_PROJECTILE,
      width: DIM.LK_PROJ_WIDTH, height: DIM.LK_PROJ_HEIGHT,
      pos: this.launchPoint(DIM.LK_PROJ_WIDTH), vector: { x: this.dir * DIM.LK_PROJ_SPEED, y: 0 },
    }));
  }
  // Bicycle (spin) kick
  specialMove2() { this.dash(ANIM.SPECIAL_1, DIM.LK_SPIN_SPEED, INJURY.LK_SPIN_KICK); }
  // Flying (flat) kick
  specialMove3() { this.dash(ANIM.SPECIAL_2, DIM.LK_FLAT_SPEED, INJURY.LK_FLAT_KICK); }
}

export class Kabal extends DashingPlayer {
  constructor(engine, opts) { super(engine, { ...opts, type: opts.team === 1 ? T.KABAL_1 : T.KABAL_2 }); }
  // Fix: the original pushed Kabal back from the wall twice.
  intersectWithWall(wall) {
    super.intersectWithWall(wall);
    if (this.dashing) this.endDash();
  }
  // The dash spins the opponent instead of hurting them, and keeps going.
  intersectWithPlayer(player) {
    if (this.dashing) {
      player.spin();
      this.injury = 0;
    }
  }
  intersectWithProjectile(proj) {
    super.intersectWithProjectile(proj);
    if (this.dashing) this.endDash();
  }
  specialMove1() {
    this.engine.addObject(new Projectile(this.engine, {
      type: side(this, T.KABAL_LEFT_PROJECTILE), injury: INJURY.DEFAULT_PROJECTILE,
      width: DIM.KABAL_PROJ_WIDTH, height: DIM.KABAL_PROJ_HEIGHT,
      pos: this.launchPoint(DIM.KABAL_PROJ_WIDTH), vector: { x: this.dir * DIM.KABAL_PROJ_SPEED, y: 0 },
    }));
  }
  // Spin dash
  specialMove2() { this.dash(ANIM.SPECIAL_1, DIM.LK_FLAT_SPEED, INJURY.LK_FLAT_KICK); }
  // Buzzsaw wheel that rises up the opponent's side of the screen.
  specialMove3() {
    const x = this.team === 1
      ? DIM.WALL_RIGHT_X - DIM.KABAL_WHEEL_WIDTH / 2 - 5
      : DIM.WALL_LEFT_X + DIM.KABAL_WHEEL_WIDTH / 2 + 5;
    const wheel = new Projectile(this.engine, {
      type: this.team === 1 ? T.KABAL_LEFT_WHEEL_PROJECTILE : T.KABAL_RIGHT_WHEEL_PROJECTILE,
      injury: INJURY.DEFAULT_PROJECTILE,
      width: DIM.KABAL_WHEEL_WIDTH, height: DIM.KABAL_WHEEL_HEIGHT,
      pos: { x, y: DIM.WALL_BOTTOM_Y - DIM.KABAL_WHEEL_HEIGHT / 2 - 5 },
      vector: { x: 0, y: -DIM.KABAL_WHEEL_SPEED },
    });
    this.engine.addObject(wheel);
    this.engine.broadcastAnimateObject(wheel.id, ANIM.SPECIAL_1);
  }
}

export class Jade extends Player {
  constructor(engine, opts) {
    super(engine, { ...opts, type: opts.team === 1 ? T.JADE_1 : T.JADE_2 });
    this.projectileInvulnerability = false;
    this.invulnerabilityTimer = 0;
  }
  intersectWithProjectile(proj) {
    if (!this.projectileInvulnerability) super.intersectWithProjectile(proj);
  }
  // Fix: the original compared the wrong timer with the wrong sign, so the
  // invulnerability never wore off. It now lasts 4 seconds as intended.
  update() {
    if (this.projectileInvulnerability && this.engine.now() - this.invulnerabilityTimer > 4e9) {
      this.projectileInvulnerability = false;
      this.engine.broadcastAnimateObject(this.id, ANIM.NOT);
    }
    super.update();
  }
  jadeProjectile(injury, theta) {
    return new Projectile(this.engine, {
      type: side(this, T.JADE_LEFT_PROJECTILE), injury,
      width: DIM.JADE_PROJ_WIDTH, height: DIM.JADE_PROJ_HEIGHT,
      pos: this.launchPoint(DIM.JADE_PROJ_WIDTH),
      vector: { x: this.dir * DIM.JADE_PROJ_SPEED * Math.cos(theta), y: DIM.JADE_PROJ_SPEED * Math.sin(theta) },
    });
  }
  specialMove1() { this.engine.addObject(this.jadeProjectile(INJURY.DEFAULT_PROJECTILE, 0)); }
  // Three-way spread doing 1/3 damage each.
  specialMove2() {
    for (let theta = Math.PI / 6; theta > -Math.PI / 6 - 0.2; theta -= Math.PI / 6) {
      this.engine.addObject(this.jadeProjectile(Math.trunc(INJURY.DEFAULT_PROJECTILE / 3), theta));
    }
  }
  specialMove3() {
    this.projectileInvulnerability = true;
    this.invulnerabilityTimer = this.engine.now();
    this.engine.broadcastAnimateObject(this.id, ANIM.SPECIAL_1);
  }
  // Attacking drops the shield. (In C++ this override was never called
  // because GEPlayer::attack wasn't virtual.)
  attack(anim, injury, w, h) {
    this.projectileInvulnerability = false;
    super.attack(anim, injury, w, h);
  }
}

export class SubZero extends Player {
  constructor(engine, opts) { super(engine, { ...opts, type: opts.team === 1 ? T.SUB_ZERO_1 : T.SUB_ZERO_2 }); }
  iceBall(speed, seeking) {
    return new SZProjectile(this.engine, {
      type: side(this, T.SZ_LEFT_PROJECTILE), injury: 1,
      width: DIM.SZ_PROJ_WIDTH, height: DIM.SZ_PROJ_HEIGHT,
      pos: this.launchPoint(DIM.SZ_PROJ_WIDTH), vector: { x: this.dir * speed, y: 0 },
    }, seeking, 3 - this.team);
  }
  specialMove1() { this.engine.addObject(this.iceBall(DIM.SZ_PROJ_SPEED, false)); }
  // Slow homing ice ball
  specialMove2() { this.engine.addObject(this.iceBall(DIM.SZ_PROJ_SPEED / 2, true)); }
}

export class Reptile extends Player {
  constructor(engine, opts) { super(engine, { ...opts, type: opts.team === 1 ? T.REPTILE_1 : T.REPTILE_2 }); }
  specialMove1() {
    this.engine.addObject(new Projectile(this.engine, {
      type: side(this, T.REPTILE_LEFT_PROJECTILE), injury: INJURY.DEFAULT_PROJECTILE,
      width: DIM.REPTILE_PROJ_WIDTH, height: DIM.REPTILE_PROJ_HEIGHT,
      pos: this.launchPoint(DIM.REPTILE_PROJ_WIDTH), vector: { x: this.dir * DIM.REPTILE_PROJ_SPEED, y: 0 },
    }));
  }
  // Invisibility, until hit.
  specialMove2() {
    this.invisible = true;
    this.engine.broadcastAnimateObject(this.id, ANIM.INVISIBLE);
    this.engine.spawnEffect(T.EXPLOSION, this.pos);
    this.engine.broadcastPlaySound(SND.REPTILE_INVIS);
  }
}

export class Cyrax extends Player {
  constructor(engine, opts) { super(engine, { ...opts, type: opts.team === 1 ? T.CYRAX_1 : T.CYRAX_2 }); }
  specialMove1() {
    this.engine.addObject(new CyraxNet(this.engine, {
      type: side(this, T.CYRAX_LEFT_NET),
      pos: this.launchPoint(DIM.CYRAX_NET_WIDTH), vector: { x: this.dir * DIM.CYRAX_NET_SPEED, y: 0 },
    }));
  }
  // Bomb that rolls to the far wall, waits, then goes off.
  specialMove2() {
    const bomb = new CyraxBomb(this.engine, {
      type: side(this, T.CYRAX_LEFT_BOMB),
      pos: this.launchPoint(DIM.CYRAX_BOMB_WIDTH), vector: { x: this.dir * DIM.CYRAX_BOMB_SPEED, y: 0 },
    }, side(this, T.CYRAX_LEFT_NUKE));
    this.engine.addObject(bomb);
    this.engine.broadcastAnimateObject(bomb.id, ANIM.BOMB_ROTATE);
  }
}

// Scorpion, Smoke and Sonya were never finished; the original engine
// substituted Liu Kang, and so do we.
export function createPlayer(engine, type, playerNum, pos) {
  const team = type % 2 === 1 ? 1 : 2;
  const base = team === 1 ? type : type - 1;
  const opts = { playerNum, team, pos };
  switch (base) {
    case T.CYRAX_1: return new Cyrax(engine, opts);
    case T.JADE_1: return new Jade(engine, opts);
    case T.KABAL_1: return new Kabal(engine, opts);
    case T.REPTILE_1: return new Reptile(engine, opts);
    case T.SUB_ZERO_1: return new SubZero(engine, opts);
    default: return new LiuKang(engine, opts);
  }
}
