// End-to-end check of the host <-> client protocol, with an in-memory link
// standing in for the PeerJS connection.
import { test } from 'node:test';
import assert from 'node:assert/strict';
import { Host } from '../web/src/net/Host.js';
import { localPair } from '../web/src/net/links.js';
import { A, T } from '../web/src/engine/ids.js';

const sleep = (ms) => new Promise((r) => setTimeout(r, ms));

function client(link, name) {
  const got = [];
  link.onMessage = (m) => got.push(m);
  link.send({ t: 'hello', name });
  return { got, send: (m) => link.send(m), last: (t) => got.filter((m) => m.t === t).at(-1) };
}

test('two players pair, pick fighters, chat, play and see the same game', async () => {
  const host = new Host({ name: 'Jeff', multiplayer: true });
  const me = client(host.localLink, 'Jeff');
  const [hostEnd, remoteEnd] = localPair();
  host.onJoin(hostEnd);
  const them = client(remoteEnd, 'Dave');
  await sleep(10);

  assert.equal(me.last('welcome').you, 0);
  assert.equal(them.last('welcome').you, 1);
  assert.deepEqual(them.last('lobby').slots.map((s) => s.name), ['Jeff', 'Dave']);

  them.send({ t: 'paddle', type: T.KABAL_1 });
  me.send({ t: 'chat', text: 'ready?' });
  await sleep(10);
  assert.equal(me.last('lobby').slots[1].type, T.KABAL_1);
  assert.equal(them.last('chat').text, 'ready?');

  them.send({ t: 'start' }); // only the host may start
  await sleep(10);
  assert.equal(them.last('start'), undefined);

  me.send({ t: 'start' });
  await sleep(10);
  const start = them.last('start');
  assert.deepEqual(start.players, [T.LIU_KANG_1, T.KABAL_2], 'host left, joiner on the right');

  await sleep(2500 + 1700); // VS screen + "round one ... fight"
  them.send({ t: 'action', a: A.UP });
  await sleep(100);
  const up = them.got.filter((m) => m.t === 'update' && m.id === 1 && m.vy === -10);
  assert.ok(up.length, 'joiner moved its own paddle');
  assert.ok(me.got.some((m) => m.t === 'update' && m.id === 1 && m.vy === -10), 'host saw it too');
  assert.ok(them.got.some((m) => m.t === 'sync'), 'periodic position sync');

  remoteEnd.close();
  await sleep(10);
  assert.ok(me.last('abort'), 'host is told the opponent left mid-game');
  assert.equal(me.last('lobby').slots[1].present, false);
  host.close();
});

test('a third player is turned away', async () => {
  const host = new Host({ name: 'Jeff', multiplayer: true });
  client(host.localLink, 'Jeff');
  const [h1, r1] = localPair(); host.onJoin(h1); client(r1, 'Dave');
  const [h2, r2] = localPair(); host.onJoin(h2); const third = client(r2, 'Elaine');
  await sleep(10);
  assert.match(third.last('error').text, /full/);
  host.close();
});
