// Port of src/gameEng/PKGameEngine.cxx: one round of play.
//
// The C++ engine ran its own loop and talked to clients through
// PKGameServerInterface's broadcast* calls. Here the caller drives tick() every
// 20 ms and engine output goes to an emit(msg) callback as plain objects:
//   {t:'add'|'update', id, type, x, y, vx, vy}   {t:'remove', id}
//   {t:'anim', id, anim}   {t:'sound', id}   {t:'status', life:[...]}

import { Physics } from './physics.js';
import { Ball, Wall, ExplosionProjectile } from './objects.js';
import { createPlayer } from './characters.js';
import { T, A, DIM, SND, ANIM } from './ids.js';

const MAX_OBJS = 100;

export class GameEngine {
  // players: array indexed by player number of paddle type ids (or T.INVALID)
  constructor({ players, emit = () => {}, clock }) {
    this.emit = emit;
    this.now = clock;
    this.physics = new Physics(clock);
    this.team1 = [];
    this.team2 = [];
    this.walls = [];
    this.projectiles = [];
    this.objArray = new Array(MAX_OBJS).fill(null);
    this.nextFree = 0;
    this.events = [];
    this.paused = false;
    this.life = players.map((p) => (p === T.INVALID ? -1 : 100));

    this.addPlayers(players);
    const ballPos = { x: Math.trunc(DIM.SCREEN_WIDTH / 3), y: (DIM.SCREEN_HEIGHT - DIM.WALL_TOP_Y) / 2 + DIM.WALL_TOP_Y };
    this.addObject(new Ball(this, ballPos, { x: 1 * DIM.BALL_SPEED, y: 0.33 * DIM.BALL_SPEED }));
    this.addWall('top');
    this.addWall('right');
    this.addWall('bottom');
    this.addWall('left');
  }

  // One pass of PKGameEngine::mainloop. Returns the winning team (1 or 2), or 0.
  tick() {
    if (this.paused) return 0;
    this.processEventList();
    this.updateObjects();
    this.checkIntersections();
    return this.checkEndRound();
  }

  handleAction(playerNum, action) {
    const p = this.findPlayer(playerNum);
    if (!p) return;
    switch (action) {
      case A.UP: p.moveUp(); break;
      case A.DOWN: p.moveDown(); break;
      case A.LEFT: p.moveLeft(); break;
      case A.RIGHT: p.moveRight(); break;
      case A.PUNCH: p.punch(); break;
      case A.KICK: p.kick(); break;
      case A.CUT_UP: p.uppercut(); break;
      case A.CUT_DOWN: p.lowercut(); break;
      case A.SWEEP: p.sweep(); break;
      case A.BLOCK: p.block(); break;
      case A.UNBLOCK: p.unblock(); break;
      case A.SPECIAL_1: if (p.canAct()) p.specialMove1(); break;
      case A.SPECIAL_2: if (p.canAct()) p.specialMove2(); break;
      case A.SPECIAL_3: if (p.canAct()) p.specialMove3(); break;
      case A.STOP: p.stop(); break;
      case A.STOP_VERTICAL: p.stopVertical(); break;
      case A.STOP_HORIZONTAL: p.stopHorizontal(); break;
      case A.PAUSE: this.setPaused(true); break;
      case A.UNPAUSE: this.setPaused(false); break;
    }
  }

  setPaused(paused) {
    if (paused === this.paused) return;
    // Fix: the original kept each object's timestamp across a pause, so on
    // unpause everything jumped forward by the paused time.
    if (!paused) {
      const now = this.now();
      for (const o of this.allObjects()) o.timestamp = now;
    }
    this.paused = paused;
    this.emit({ t: 'pause', paused });
  }

  allObjects() { return this.objArray.filter(Boolean); }

  // --- broadcasting -------------------------------------------------------
  objMsg(t, o) {
    return { t, id: o.id, type: o.typeID, x: o.pos.x, y: o.pos.y, vx: o.vector.x, vy: o.vector.y };
  }
  broadcastUpdate(o) { this.emit(this.objMsg('update', o)); }
  broadcastAddObject(o) { this.emit(this.objMsg('add', o)); }
  broadcastRemoveObject(id) { this.emit({ t: 'remove', id }); }
  broadcastAnimateObject(id, anim) { this.emit({ t: 'anim', id, anim }); }
  broadcastPlaySound(id) { this.emit({ t: 'sound', id }); }
  changeGameStatus(playerNum, life) {
    this.life[playerNum] = life;
    this.emit({ t: 'status', life: [...this.life] });
  }
  // Snapshot of every visible object, used to keep clients from drifting.
  snapshot() {
    return this.allObjects()
      .filter((o) => o.typeID !== T.WALL_HORIZONTAL && o.typeID !== T.WALL_VERTICAL)
      .map((o) => [o.id, o.pos.x, o.pos.y, o.vector.x, o.vector.y]);
  }

  // --- events (run at the start of the next tick) --------------------------
  removeLater(obj) { this.events.push(() => this.removeObject(obj)); }
  injureTeamLater(team, amount) {
    this.events.push(() => {
      for (const p of [...(team === 1 ? this.team1 : this.team2)]) p.subtractLife(amount);
    });
  }
  processEventList() {
    while (this.events.length) this.events.shift()();
  }

  // --- objects -------------------------------------------------------------
  addObject(o) {
    o.id = this.nextFree;
    this.objArray[this.nextFree] = o;
    o.cont.push(o);
    this.findNextFree();
    if (o.typeID !== T.WALL_HORIZONTAL && o.typeID !== T.WALL_VERTICAL) this.broadcastAddObject(o);
  }

  findNextFree() {
    const start = this.nextFree;
    while (this.objArray[this.nextFree] !== null) {
      this.nextFree = (this.nextFree + 1) % MAX_OBJS;
      if (this.nextFree === start) return;
    }
  }

  // Fix: takes the object, not its id. The original removed by id, so a stale
  // removal could delete a newer object that had reused the slot.
  removeObject(o) {
    if (this.objArray[o.id] !== o) return;
    const i = o.cont.indexOf(o);
    if (i >= 0) o.cont.splice(i, 1);
    this.objArray[o.id] = null;
    o.destroy();
  }

  spawnEffect(type, pos, time) {
    const fx = new ExplosionProjectile(this, { type, injury: 0, width: DIM.EXPLODE_WIDTH, height: DIM.EXPLODE_HEIGHT, pos }, time);
    this.addObject(fx);
    this.broadcastAnimateObject(fx.id, ANIM.EXPLODE);
  }

  addPlayers(players) {
    const team1pos = { x: DIM.WALL_LEFT_X + 30, y: DIM.WALL_TOP_Y + 100 };
    const team2pos = { x: DIM.WALL_RIGHT_X - 30, y: DIM.WALL_TOP_Y + 100 };
    players.forEach((type, j) => {
      if (type === T.INVALID) return;
      const pos = type % 2 === 1 ? team1pos : team2pos;
      this.addObject(createPlayer(this, type, j, pos));
      pos.y += 100;
    });
  }

  addWall(side) {
    const midY = (DIM.SCREEN_HEIGHT - DIM.WALL_TOP_Y) / 2 + DIM.WALL_TOP_Y;
    const walls = {
      top: { type: T.WALL_HORIZONTAL, team: 0, width: DIM.SCREEN_WIDTH, height: 10, pos: { x: DIM.SCREEN_WIDTH / 2, y: DIM.WALL_TOP_Y - 5 } },
      bottom: { type: T.WALL_HORIZONTAL, team: 0, width: DIM.SCREEN_WIDTH, height: 10, pos: { x: DIM.SCREEN_WIDTH / 2, y: DIM.WALL_BOTTOM_Y + 5 } },
      left: { type: T.WALL_VERTICAL, team: 1, width: 10, height: DIM.SCREEN_HEIGHT, pos: { x: DIM.WALL_LEFT_X - 5, y: midY } },
      right: { type: T.WALL_VERTICAL, team: 2, width: 10, height: DIM.SCREEN_HEIGHT, pos: { x: DIM.WALL_RIGHT_X + 5, y: midY } },
    };
    this.addObject(new Wall(this, walls[side]));
  }

  findPlayer(playerNum) {
    return [...this.team1, ...this.team2].find((p) => p.playerNum === playerNum) || null;
  }

  choosePlayer(team) {
    const list = team === 1 ? this.team1 : this.team2;
    return list[0] || null;
  }

  // --- the loop ------------------------------------------------------------
  updateObjects() {
    for (const list of [this.team1, this.team2, this.projectiles]) {
      for (const o of [...list]) {
        this.physics.update(o);
        o.update();
      }
    }
  }

  checkIntersections() {
    const pair = (a, b) => {
      if (this.physics.intersect(a, b)) {
        a.intersect(b);
        b.intersect(a);
      }
    };
    const t1 = [...this.team1], t2 = [...this.team2], pr = [...this.projectiles], w = this.walls;
    for (const a of t1) {
      for (const b of t2) pair(a, b);
      for (const p of pr) pair(p, a);
      for (const wall of w) pair(a, wall);
    }
    for (const a of t2) {
      for (const p of pr) pair(p, a);
      for (const wall of w) pair(a, wall);
    }
    for (const p of pr) for (const wall of w) pair(p, wall);
  }

  checkEndRound() {
    if (this.team1.length === 0) return 2;
    if (this.team2.length === 0) return 1;
    return 0;
  }

  // Remove everything (the engine's destructor), telling clients.
  destroy() {
    for (const o of this.allObjects()) {
      this.objArray[o.id] = null;
      o.destroy();
    }
  }
}
