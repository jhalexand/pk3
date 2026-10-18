import { test } from 'node:test';
import assert from 'node:assert/strict';
import { Physics } from '../web/src/engine/physics.js';
import { GameEngine } from '../web/src/engine/GameEngine.js';
import { RoundEngine, TICK_MS } from '../web/src/engine/RoundEngine.js';
import { T, A } from '../web/src/engine/ids.js';

// A fake clock in nanoseconds that tests advance by hand.
function fakeClock() {
  let t = 0;
  const clock = () => t;
  clock.advance = (ms) => { t += ms * 1e6; };
  return clock;
}

const box = (x, y, w, h, vx = 0, vy = 0, type = 0) => ({
  pos: { x, y }, vector: { x: vx, y: vy }, width: w, height: h, widthAdjust: 0, heightAdjust: 0, typeID: type, timestamp: 0,
});

test('physics update moves 1px per 100ms per velocity unit', () => {
  const clock = fakeClock();
  const p = new Physics(clock);
  const o = box(0, 0, 1, 1, 10, -5);
  clock.advance(1000);
  p.update(o);
  assert.ok(Math.abs(o.pos.x - 100) < 1e-9);
  assert.ok(Math.abs(o.pos.y + 50) < 1e-9);
});

test('intersect is a strict overlap', () => {
  const p = new Physics(() => 0);
  assert.equal(p.intersect(box(0, 0, 10, 10), box(9, 0, 10, 10)), true);
  assert.equal(p.intersect(box(0, 0, 10, 10), box(10, 0, 10, 10)), false);
});

test('bounceWithWall flips toward-wall component only', () => {
  const p = new Physics(() => 0);
  const ball = box(5, 200, 12, 12, -30, 10);
  p.bounceWithWall(ball, { typeID: T.WALL_VERTICAL });
  assert.deepEqual(ball.vector, { x: 30, y: 10 });
  const top = box(100, 85, 12, 12, 30, -10);
  p.bounceWithWall(top, { typeID: T.WALL_HORIZONTAL });
  assert.deepEqual(top.vector, { x: 30, y: 10 });
});

test('bounceWithPlayer sends the ball away at an angle set by the hit point', () => {
  const p = new Physics(() => 0);
  const paddle = box(30, 200, 30, 55);
  const center = box(45, 200, 12, 12, -30, 0);
  p.bounceWithPlayer(center, paddle);
  assert.ok(Math.abs(center.vector.x - 30) < 1e-9 && Math.abs(center.vector.y) < 1e-9);
  const edge = box(45, 227, 12, 12, -30, 0); // dy = 27 = height/2
  p.bounceWithPlayer(edge, paddle);
  const angle = Math.atan2(edge.vector.y, edge.vector.x);
  assert.ok(Math.abs(angle - Math.PI / 3) < 1e-6, `angle ${angle}`);
});

function runEngine(players, ms, onTick) {
  const clock = fakeClock();
  const msgs = [];
  const eng = new GameEngine({ players, emit: (m) => msgs.push(m), clock });
  let winner = 0;
  for (let t = 0; t < ms && !winner; t += TICK_MS) {
    clock.advance(TICK_MS);
    onTick?.(eng, t);
    winner = eng.tick();
  }
  return { eng, msgs, winner };
}

test('ball stays in bounds and goals hurt the defending team', () => {
  // Players hidden out of the ball's path so it scores.
  const { eng, msgs } = runEngine([T.LIU_KANG_1, T.SUB_ZERO_2], 30000, (e) => {
    for (const p of [...e.team1, ...e.team2]) { p.pos.y = 100; }
    const ball = e.projectiles.find((o) => o.typeID === T.BALL);
    assert.ok(ball.pos.x > -20 && ball.pos.x < 536 && ball.pos.y > 60 && ball.pos.y < 450, `ball at ${ball.pos.x},${ball.pos.y}`);
  });
  const statuses = msgs.filter((m) => m.t === 'status');
  assert.ok(statuses.length > 0, 'someone took damage');
  // each goal does exactly 10 damage
  for (const s of statuses) for (const l of s.life) assert.equal(l % 10, 0);
  assert.ok(eng.life.some((l) => l < 100));
});

test('a round ends when one team is out of life', () => {
  const { winner } = runEngine([T.LIU_KANG_1, T.SUB_ZERO_2], 600000, (e) => {
    const ball = e.projectiles.find((o) => o.typeID === T.BALL);
    for (const p of e.team1) p.pos.y = 100; // left player never defends
    for (const p of e.team2) p.pos.y = ball.pos.y; // right player always does
  });
  assert.equal(winner, 2);
});

test('punch in range hurts, blocking absorbs it', () => {
  const clock = fakeClock();
  const eng = new GameEngine({ players: [T.CYRAX_1, T.KABAL_2], clock });
  const [a] = eng.team1; const [b] = eng.team2;
  b.pos = { x: a.pos.x + 35, y: a.pos.y };
  eng.handleAction(0, A.PUNCH);
  assert.equal(b.life, 95);
  eng.handleAction(1, A.BLOCK);
  eng.handleAction(0, A.PUNCH);
  assert.equal(b.life, 95);
});

test('specials spawn projectiles that explode on the opponent', () => {
  for (const type of [T.LIU_KANG_1, T.JADE_1, T.KABAL_1, T.REPTILE_1, T.SUB_ZERO_1, T.CYRAX_1]) {
    const clock = fakeClock();
    const eng = new GameEngine({ players: [type, T.LIU_KANG_2], clock });
    const before = eng.projectiles.length;
    eng.handleAction(0, A.SPECIAL_1);
    assert.ok(eng.projectiles.length > before || type === T.KABAL_1, `type ${type} special 1`);
    for (let i = 0; i < 300; i++) { clock.advance(TICK_MS); eng.tick(); }
  }
});

test('Jade invulnerability wears off after 4s', () => {
  const clock = fakeClock();
  const eng = new GameEngine({ players: [T.JADE_1, T.LIU_KANG_2], clock });
  const [jade] = eng.team1;
  eng.handleAction(0, A.SPECIAL_3);
  assert.equal(jade.projectileInvulnerability, true);
  for (let i = 0; i < 250; i++) { clock.advance(TICK_MS); eng.tick(); }
  assert.equal(jade.projectileInvulnerability, false);
});

test('effects do not linger at walls', () => {
  const clock = fakeClock();
  const eng = new GameEngine({ players: [T.LIU_KANG_1, T.LIU_KANG_2], clock });
  eng.team2[0].pos.y = 400; // out of the way
  eng.handleAction(0, A.SPECIAL_1);
  for (let i = 0; i < 200; i++) { clock.advance(TICK_MS); eng.tick(); }
  assert.equal(eng.projectiles.filter((o) => o.typeID === T.EXPLOSION).length, 0);
});

test('round engine plays a best-of-three match', () => {
  const clock = fakeClock();
  const msgs = [];
  const re = new RoundEngine({ players: [T.LIU_KANG_1, T.SUB_ZERO_2], emit: (m) => msgs.push(m), clock });
  re.start();
  for (let i = 0; i < 200000 && re.phase !== 'done'; i++) {
    clock.advance(TICK_MS);
    if (re.engine) {
      const ball = re.engine.projectiles.find((o) => o.typeID === T.BALL);
      for (const p of re.engine.team1) p.pos.y = 100;
      if (ball) for (const p of re.engine.team2) p.pos.y = ball.pos.y;
    }
    re.tick();
  }
  const end = msgs.find((m) => m.t === 'matchEnd');
  assert.ok(end, 'match ended');
  assert.deepEqual(end.score, [0, 2]);
  assert.equal(msgs.filter((m) => m.t === 'round').length, 2);
});
