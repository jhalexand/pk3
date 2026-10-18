// Transports between the host (which runs the engine, like pkgameserver did)
// and the clients. Both kinds of link expose the same tiny interface:
//   link.send(msg)          deliver a JSON-able object to the other side
//   link.onMessage = fn     called with each received object
//   link.onClose = fn       called once when the link goes away
//   link.close()

// An in-page pair of links (the host's own view, and the AI).
export function localPair() {
  const mk = () => ({ onMessage: null, onClose: null, peer: null, closed: false });
  const a = mk(), b = mk();
  a.peer = b; b.peer = a;
  for (const end of [a, b]) {
    // Deliver asynchronously, like a network would, so handlers never re-enter.
    end.send = (msg) => { if (!end.closed) queueMicrotask(() => end.peer.onMessage?.(msg)); };
    end.close = () => {
      if (end.closed) return;
      end.closed = end.peer.closed = true;
      end.onClose?.(); end.peer.onClose?.();
    };
  }
  return [a, b];
}

// Pairing codes avoid look-alike characters (0/O, 1/I/L).
const CODE_ALPHABET = 'ABCDEFGHJKMNPQRSTUVWXYZ23456789';
export const CODE_LENGTH = 5;
const PEER_PREFIX = 'pk3-game-';

export function makeCode() {
  const r = crypto.getRandomValues(new Uint32Array(CODE_LENGTH));
  return [...r].map((n) => CODE_ALPHABET[n % CODE_ALPHABET.length]).join('');
}

export const normalizeCode = (s) => s.toUpperCase().replace(/[^A-Z0-9]/g, '');

function wrapConnection(conn) {
  const link = { onMessage: null, onClose: null, closed: false };
  link.send = (msg) => { if (conn.open) conn.send(msg); };
  link.close = () => conn.close();
  conn.on('data', (msg) => link.onMessage?.(msg));
  const closed = () => {
    if (link.closed) return;
    link.closed = true;
    link.onClose?.();
  };
  conn.on('close', closed);
  conn.on('error', closed);
  return link;
}

function peerError(err) {
  const msgs = {
    'peer-unavailable': 'No game with that code. Check the code and make sure the host is still waiting.',
    'unavailable-id': 'That game code is already in use. Try creating the game again.',
    'network': 'Lost contact with the pairing server. Check your internet connection.',
    'server-error': 'The pairing server had a problem. Try again in a minute.',
    'browser-incompatible': 'This browser does not support WebRTC.',
  };
  return new Error(msgs[err?.type] || err?.message || String(err));
}

// Host: register under a pairing code and accept connections.
// Resolves once registered; onConnection(link) is called for each joiner.
export function hostPeer(code, onConnection) {
  return new Promise((resolve, reject) => {
    const peer = new window.Peer(PEER_PREFIX + code);
    let opened = false;
    peer.on('open', () => { opened = true; resolve(peer); });
    peer.on('connection', (conn) => {
      conn.on('open', () => onConnection(wrapConnection(conn)));
    });
    peer.on('error', (err) => { if (!opened) reject(peerError(err)); });
    // Re-register with the broker if the signalling socket drops; existing
    // game connections are peer-to-peer and survive this.
    peer.on('disconnected', () => { if (!peer.destroyed) peer.reconnect(); });
  });
}

// Joiner: connect to a host by pairing code.
export function joinPeer(code) {
  return new Promise((resolve, reject) => {
    const peer = new window.Peer();
    const fail = (err) => { peer.destroy(); reject(peerError(err)); };
    const timer = setTimeout(() => fail(new Error('Timed out connecting to the host. One of you may be behind a strict firewall.')), 15000);
    peer.on('error', (err) => { clearTimeout(timer); fail(err); });
    peer.on('open', () => {
      const conn = peer.connect(PEER_PREFIX + code, { reliable: true, serialization: 'json' });
      conn.on('open', () => {
        clearTimeout(timer);
        const link = wrapConnection(conn);
        link.peer = peer;
        const close = link.close;
        link.close = () => { close(); peer.destroy(); };
        resolve(link);
      });
    });
  });
}
