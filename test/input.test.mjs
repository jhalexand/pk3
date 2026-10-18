import { test } from 'node:test';
import assert from 'node:assert/strict';
import { PaddleKeys } from '../web/src/input/PaddleKeys.js';
import { A, T } from '../web/src/engine/ids.js';

function rig(type) {
  let t = 0;
  const sent = [];
  const keys = new PaddleKeys({ type, sendAction: (a) => sent.push(a), clock: () => t });
  const tap = (k, ms = 50) => { keys.keyPress(k); t += ms * 1e6; keys.keyRelease(k); t += ms * 1e6; };
  return { keys, sent, tap, wait: (ms) => { t += ms * 1e6; } };
}

test('Liu Kang left: forward forward punch throws a fireball', () => {
  const { sent, tap } = rig(T.LIU_KANG_1);
  tap('RIGHT'); tap('RIGHT'); tap('PUNCH');
  assert.equal(sent.at(-1), A.SPECIAL_1);
  assert.ok(sent.includes(A.PUNCH), 'punch also sent on press, as in the original');
});

test('right-side players mirror forward', () => {
  const { sent, tap } = rig(T.LIU_KANG_2);
  tap('LEFT'); tap('LEFT'); tap('PUNCH');
  assert.equal(sent.at(-1), A.SPECIAL_1);
});

test('combos time out', () => {
  const { sent, tap, wait } = rig(T.REPTILE_1);
  tap('RIGHT'); wait(600); tap('RIGHT'); tap('PUNCH');
  assert.notEqual(sent.at(-1), A.SPECIAL_1);
});

test('Liu Kang: holding kick 1.5s does the bicycle kick', () => {
  const { keys, sent, wait } = rig(T.LIU_KANG_1);
  keys.keyPress('KICK'); wait(1600); keys.keyRelease('KICK');
  assert.equal(sent.at(-1), A.SPECIAL_2);
});

test('Jade combos fire on press and replace the punch', () => {
  const { keys, sent, tap } = rig(T.JADE_1);
  tap('LEFT'); tap('LEFT'); tap('RIGHT'); tap('RIGHT');
  const before = sent.length;
  keys.keyPress('PUNCH');
  assert.deepEqual(sent.slice(before), [A.SPECIAL_2]);
});

test('Sub-Zero: forward, down, back, punch is the homing ice ball', () => {
  const { sent, tap } = rig(T.SUB_ZERO_1);
  tap('RIGHT'); tap('DOWN'); tap('LEFT'); tap('PUNCH');
  assert.equal(sent.at(-1), A.SPECIAL_2);
});

test('Cyrax: holding punch turns back, back, kick into the bomb', () => {
  const { keys, sent, tap } = rig(T.CYRAX_1);
  tap('LEFT'); tap('LEFT');
  keys.keyPress('PUNCH'); tap('KICK');
  assert.equal(sent.at(-1), A.SPECIAL_2);
  keys.keyRelease('PUNCH');
  tap('LEFT'); tap('LEFT'); tap('KICK');
  assert.equal(sent.at(-1), A.SPECIAL_1);
});

test('punch while holding down is a lowercut', () => {
  const { keys, sent, tap } = rig(T.KABAL_1);
  keys.keyPress('DOWN'); tap('PUNCH');
  assert.equal(sent.at(-1), A.CUT_DOWN);
});

test('releasing one direction while holding the other keeps moving', () => {
  const { keys, sent } = rig(T.KABAL_1);
  keys.keyPress('UP'); keys.keyPress('DOWN'); keys.keyRelease('DOWN');
  assert.equal(sent.at(-1), A.UP);
  keys.keyRelease('UP');
  assert.equal(sent.at(-1), A.STOP_VERTICAL);
});

test('move lists are in order with one entry per special', async () => {
  const { moveList } = await import('../web/src/input/PaddleKeys.js');
  for (const type of [T.CYRAX_1, T.JADE_1, T.KABAL_1, T.LIU_KANG_1, T.REPTILE_1, T.SUB_ZERO_1]) {
    const actions = moveList(type).map((m) => m.action);
    assert.deepEqual(actions, [...new Set(actions)].sort((a, b) => a - b), `type ${type}`);
  }
  assert.equal(moveList(T.CYRAX_1).length, 2);
});
