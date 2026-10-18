// Ported from src/gameEng: GEGameObject, GEWall, GEProjectile, GEBall,
// GEExplosionProjectile, GESZProjectile, GECyraxNet, GECyraxBomb, GE*Event.
//
// Collision uses the original double dispatch: when A and B overlap the engine
// calls A.intersect(B) and B.intersect(A), and X.intersect(Y) means
// Y.intersectWithX(X).

import { T, DIM, INJURY, SND, ANIM } from './ids.js';

export class GameObject {
  constructor(engine, { type, injury = 0, cont, width = 0, height = 0, pos = { x: 0, y: 0 }, vector = { x: 0, y: 0 } }) {
    this.engine = engine;
    this.id = -1;
    this.typeID = type;
    this.injury = injury;
    this.cont = cont;
    this.width = width;
    this.height = height;
    this.widthAdjust = 0;
    this.heightAdjust = 0;
    this.pos = { x: pos.x, y: pos.y };
    this.vector = { x: vector.x, y: vector.y };
    this.timestamp = engine.now();
  }

  // Returns true if the vector changed (PKObject::setVector).
  setVector(x, y) {
    if (this.vector.x === x && this.vector.y === y) return false;
    this.vector = { x, y };
    return true;
  }

  intersect(obj) {}
  intersectWithBall(ball) {}
  intersectWithWall(wall) {}
  intersectWithPlayer(player) {}
  intersectWithProjectile(obj) {}
  update() {}

  // GEGameObject::~GEGameObject
  destroy() {
    this.vector = { x: 0, y: 0 };
    this.engine.broadcastUpdate(this);
    if (this.typeID !== T.WALL_HORIZONTAL && this.typeID !== T.WALL_VERTICAL) {
      this.engine.broadcastRemoveObject(this.id);
    }
  }
}

export class Wall extends GameObject {
  // team: 0 = top/bottom, 1 = left wall (team 1's goal), 2 = right wall
  constructor(engine, { type, team, width, height, pos }) {
    super(engine, { type, cont: engine.walls, width, height, pos });
    this.team = team;
  }
  intersect(obj) { obj.intersectWithWall(this); }
}

export class Projectile extends GameObject {
  constructor(engine, opts) {
    super(engine, { cont: engine.projectiles, ...opts });
  }
  intersect(obj) { obj.intersectWithProjectile(this); }
  intersectWithWall(wall) {
    this.engine.removeLater(this);
    this.explode();
  }
  intersectWithPlayer(player) {
    this.engine.removeLater(this);
    this.explode();
  }
  explode() {
    const x = this.vector.x > 0 ? Math.trunc(this.width / 2) + this.pos.x : -Math.trunc(this.width / 2) + this.pos.x;
    this.engine.spawnEffect(T.EXPLOSION, { x, y: this.pos.y });
  }
}

export class Ball extends Projectile {
  constructor(engine, pos, vector) {
    super(engine, { type: T.BALL, width: DIM.BALL_WIDTH, height: DIM.BALL_HEIGHT, pos, vector });
  }
  intersect(obj) { obj.intersectWithBall(this); }
  intersectWithWall(wall) {
    // Fix: the original bounced and injured on every tick of overlap, so a slow
    // exit from a side wall could hurt the team twice and flip the y direction.
    // Only react to a side wall when the ball is heading into it.
    if (wall.team === 1 && this.vector.x >= 0) return;
    if (wall.team === 2 && this.vector.x <= 0) return;
    this.engine.physics.bounceWithWall(this, wall);
    this.engine.broadcastUpdate(this);
    if (wall.team !== 0) this.engine.injureTeamLater(wall.team, 10);
  }
  intersectWithPlayer(player) {
    this.engine.physics.bounceWithPlayer(this, player);
    this.engine.broadcastUpdate(this);
  }
  intersectWithProjectile(obj) {}
}

// Explosions, blood and the Cyrax nuke. Times are in nanoseconds.
export class ExplosionProjectile extends Projectile {
  constructor(engine, opts, time = 250e6) {
    super(engine, opts);
    this.timer = engine.now();
    this.timeToExplode = time;
    this.hit = new Set();
  }
  update() {
    if (this.engine.now() - this.timer > this.timeToExplode) this.engine.removeLater(this);
  }
  // Fix: in the original, pure effects (zero damage) still stopped any player
  // they touched, and touching a wall made them explode again, forever. Now
  // only damaging ones (the nuke) affect players, once each for their lifetime.
  intersect(obj) {
    if (this.injury > 0 && !this.hit.has(obj)) {
      this.hit.add(obj);
      obj.intersectWithProjectile(this);
    }
  }
  intersectWithWall(wall) {}
  intersectWithPlayer(player) {}
}

export class SZProjectile extends Projectile {
  constructor(engine, opts, seeking = false, teamToAttack = 0) {
    super(engine, opts);
    this.seeking = seeking;
    this.teamToAttack = teamToAttack;
    this.timer = engine.now();
    engine.broadcastPlaySound(SND.SUB_PROJ_THROW);
  }
  intersectWithPlayer(player) {
    player.freeze();
    this.engine.removeLater(this);
    this.engine.broadcastPlaySound(SND.SUB_PROJ_HIT);
  }
  intersectWithWall(wall) {
    this.engine.removeLater(this);
  }
  update() {
    if (!this.seeking) return;
    if (this.engine.now() - this.timer > 250e6) {
      const player = this.engine.choosePlayer(this.teamToAttack);
      if (!player) return;
      const len = Math.hypot(this.vector.x, this.vector.y);
      const dx = player.pos.x - this.pos.x;
      const dy = player.pos.y - this.pos.y;
      const d = Math.hypot(dx, dy) || 1;
      this.vector = { x: (dx / d) * len, y: (dy / d) * len };
      this.engine.broadcastUpdate(this);
      this.timer = this.engine.now();
    }
  }
}

export class CyraxNet extends Projectile {
  constructor(engine, opts) {
    super(engine, { injury: INJURY.NONE, width: DIM.CYRAX_NET_WIDTH, height: DIM.CYRAX_NET_HEIGHT, ...opts });
  }
  intersectWithPlayer(player) {
    player.getCaughtByNet();
    this.engine.removeLater(this);
  }
  intersectWithWall(wall) {
    this.engine.removeLater(this);
  }
}

export class CyraxBomb extends Projectile {
  constructor(engine, opts, idToCreate) {
    super(engine, { injury: INJURY.DEFAULT_PROJECTILE, width: DIM.CYRAX_BOMB_WIDTH, height: DIM.CYRAX_BOMB_HEIGHT, ...opts });
    this.bombWaiting = false;
    this.idToCreate = idToCreate;
    this.exploded = false;
  }
  // Bombs pass through everything and only stop at a wall.
  intersect(obj) {}
  intersectWithPlayer(player) {}
  intersectWithWall(wall) {
    if (!this.bombWaiting) {
      this.vector = { x: 0, y: 0 };
      this.engine.broadcastUpdate(this);
      this.engine.broadcastPlaySound(SND.CYRAX_BOMB_DROP);
      this.bombWaiting = true;
      this.timer = this.engine.now();
    }
  }
  update() {
    if (this.bombWaiting && !this.exploded && this.engine.now() - this.timer > INJURY.BOMB_WAIT_TIME) {
      this.exploded = true;
      const nuke = new ExplosionProjectile(this.engine, {
        type: this.idToCreate, injury: 3,
        width: DIM.CYRAX_NUKE_WIDTH, height: DIM.CYRAX_NUKE_HEIGHT, pos: this.pos,
      }, INJURY.NUKE_TIME);
      this.engine.broadcastPlaySound(SND.CYRAX_BOMB_EXPLODE);
      this.engine.addObject(nuke);
      this.engine.broadcastAnimateObject(nuke.id, ANIM.EXPLODE);
      this.engine.removeLater(this);
    }
  }
}
