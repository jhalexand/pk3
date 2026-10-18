// Port of src/gameEng/GEPlayer.cxx: the base paddle/fighter.

import { GameObject } from './objects.js';
import { T, DIM, INJURY, SND, ANIM } from './ids.js';

export class Player extends GameObject {
  constructor(engine, { type, playerNum, team, pos }) {
    super(engine, {
      type, injury: 0, cont: team === 1 ? engine.team1 : engine.team2,
      width: DIM.PADDLE_WIDTH, height: DIM.PADDLE_HEIGHT, pos,
    });
    this.playerNum = playerNum;
    this.team = team;
    this.dir = team === 1 ? 1 : -1; // direction toward the opponent
    this.life = 100;
    this.blocking = false;
    this.frozen = false;   // frozen by Sub-Zero, netted by Cyrax or spun by Kabal
    this.caught = false;
    this.invisible = false;
    this.timer = 0;
  }

  isJade() { return this.typeID === T.JADE_1 || this.typeID === T.JADE_2; }
  isKang() { return this.typeID === T.LIU_KANG_1 || this.typeID === T.LIU_KANG_2; }

  intersect(obj) { obj.intersectWithPlayer(this); }
  intersectWithBall(ball) {}
  intersectWithWall(wall) {
    this.stop();
    this.bounceBack(wall);
  }
  intersectWithPlayer(player) {
    this.stop();
    player.injure(this.injury);
  }
  intersectWithProjectile(obj) {
    this.stop();
    this.injure(obj.injury);
  }

  // Nudge 2px away from a wall. The client is never told about this, so the
  // host's periodic position sync is what keeps clients honest.
  bounceBack(wall) {
    if (wall.typeID === T.WALL_HORIZONTAL) {
      this.pos.y += wall.pos.y < this.pos.y ? 2 : -2;
    } else if (wall.typeID === T.WALL_VERTICAL) {
      this.pos.x += wall.pos.x < this.pos.x ? 2 : -2;
    }
  }

  canAct() { return !this.blocking && !this.frozen; }
  setVel(axis, v) {
    if (!this.canAct()) return;
    this.vector = { ...this.vector, [axis]: v };
    this.engine.broadcastUpdate(this);
  }
  stopVertical() { this.setVel('y', 0); }
  stopHorizontal() { this.setVel('x', 0); }
  moveUp() { this.setVel('y', -10); }
  moveDown() { this.setVel('y', 10); }
  moveLeft() { this.setVel('x', -10); }
  moveRight() { this.setVel('x', 10); }

  punch() { this.attack(ANIM.PUNCH, 5, DIM.PADDLE_PUNCH_ADDED_WIDTH, DIM.PADDLE_PUNCH_ADDED_HEIGHT); }
  kick() { this.attack(ANIM.KICK, 5, DIM.PADDLE_KICK_ADDED_WIDTH, DIM.PADDLE_KICK_ADDED_HEIGHT); }
  uppercut() { this.attack(ANIM.UPPERCUT, 10, DIM.PADDLE_UPPERCUT_ADDED_WIDTH, DIM.PADDLE_UPPERCUT_ADDED_HEIGHT); }
  lowercut() { this.attack(ANIM.UPPERCUT_DOWN, 10, DIM.PADDLE_LOWERCUT_ADDED_WIDTH, DIM.PADDLE_LOWERCUT_ADDED_HEIGHT); }
  sweep() { this.attack(ANIM.SWEEP_KICK, 10, DIM.PADDLE_SWEEP_ADDED_WIDTH, DIM.PADDLE_SWEEP_ADDED_HEIGHT); }

  block() {
    if (this.frozen) return;
    this.engine.broadcastPlaySound(SND.BLOCK);
    this.blocking = true;
    this.engine.broadcastAnimateObject(this.id, ANIM.BLOCK);
    this.stop();
  }
  unblock() {
    this.blocking = false;
    if (!this.frozen) {
      this.engine.broadcastPlaySound(SND.UNBLOCK);
      this.engine.broadcastAnimateObject(this.id, ANIM.UNBLOCK);
    }
  }

  specialMove1() {}
  specialMove2() {}
  specialMove3() {}

  stop() {
    if (this.setVector(0, 0)) this.engine.broadcastUpdate(this);
  }

  update() {
    if (this.frozen && this.engine.now() - this.timer > INJURY.FREEZE_TIME) this.unfreeze();
  }

  immobilize(anim) {
    if (this.blocking) return;
    this.frozen = true;
    this.timer = this.engine.now();
    this.engine.broadcastAnimateObject(this.id, anim);
  }
  getCaughtByNet() { this.immobilize(ANIM.CATCH); }
  spin() { this.immobilize(ANIM.SPIN); }
  freeze() { this.immobilize(ANIM.FREEZE); }

  unfreeze() {
    this.frozen = false;
    this.engine.broadcastAnimateObject(this.id, ANIM.NOT);
  }

  injure(amount) {
    if (this.blocking) {
      this.subtractLife(Math.trunc(amount / 10));
      return;
    }
    if (amount > 0) {
      this.engine.broadcastPlaySound(this.isJade() ? SND.GIRL_HIT : this.isKang() ? SND.KANG_HIT : SND.GUY_HIT);
    }
    if (amount > 8) this.engine.spawnEffect(T.BLOOD, this.pos, 800e6);
    this.subtractLife(amount);
  }

  // Takes away life without checking block.
  subtractLife(amount) {
    if (amount === 0 || this.life <= 0) return;
    if (this.frozen) this.unfreeze();
    if (this.invisible) this.turnVisible();
    this.life = Math.max(0, this.life - amount);
    this.engine.changeGameStatus(this.playerNum, this.life);
    if (this.life <= 0) {
      this.engine.removeLater(this);
      this.engine.broadcastPlaySound(this.isJade() ? SND.GIRL_DEATH : this.isKang() ? SND.KANG_DEATH : SND.GUY_DEATH);
    }
  }

  // Melee: grow the hit box for an instant and hurt any opponent inside it.
  attack(anim, injury, addedWidth, addedHeight) {
    if (!this.canAct()) return;
    this.injury = injury;
    this.engine.broadcastAnimateObject(this.id, anim);
    this.widthAdjust = addedWidth;
    this.heightAdjust = addedHeight;
    const opp = this.team === 1 ? this.engine.team2 : this.engine.team1;
    for (const opponent of [...opp]) {
      if (this.engine.physics.intersect(this, opponent)) opponent.injure(this.injury);
    }
    this.widthAdjust = 0;
    this.heightAdjust = 0;
    this.injury = 0;
  }

  turnVisible() {
    this.invisible = false;
    this.engine.broadcastAnimateObject(this.id, ANIM.VISIBLE);
    this.engine.spawnEffect(T.EXPLOSION, this.pos);
  }

  // Where a projectile of the given width spawns: just in front of the paddle.
  launchPoint(projWidth) {
    return { x: this.pos.x + this.dir * (Math.trunc(this.width / 2) + projWidth / 2 + 4), y: this.pos.y };
  }
}
