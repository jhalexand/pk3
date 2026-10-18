#!/usr/bin/env node
// Convert the game's XPM images to PNG (no dependencies; uses Node's zlib).
// Usage: node tools/xpm2png.mjs [srcRoot] [outDir]
//   defaults: graphics/  ->  web/assets/gfx/
// Output names keep the directory structure, e.g. graphics/paddles/new/paddle-lk-left.xpm
// -> web/assets/gfx/paddles/new/paddle-lk-left.png

import fs from 'node:fs';
import path from 'node:path';
import zlib from 'node:zlib';

const NAMED = {
  none: null, transparent: null,
  black: [0, 0, 0], white: [255, 255, 255], red: [255, 0, 0], green: [0, 255, 0],
  blue: [0, 0, 255], yellow: [255, 255, 0], cyan: [0, 255, 255], magenta: [255, 0, 255],
  gray: [190, 190, 190], grey: [190, 190, 190], orange: [255, 165, 0],
};

function parseColor(spec) {
  const s = spec.trim().toLowerCase();
  if (s in NAMED) return NAMED[s];
  if (s.startsWith('#')) {
    const hex = s.slice(1);
    const n = hex.length / 3; // 1, 2, 3 or 4 hex digits per channel
    const ch = (i) => {
      const v = parseInt(hex.slice(i * n, i * n + n), 16);
      return Math.round((v / (16 ** n - 1)) * 255);
    };
    return [ch(0), ch(1), ch(2)];
  }
  throw new Error(`unknown color "${spec}"`);
}

export function parseXpm(text) {
  // Collect all C string literals, in order.
  const strings = [];
  const re = /"((?:[^"\\]|\\.)*)"/g;
  // Strip comments first so quotes inside them don't confuse us.
  const body = text.replace(/\/\*[\s\S]*?\*\//g, '');
  let m;
  while ((m = re.exec(body))) strings.push(m[1]);
  const [w, h, ncolors, cpp] = strings[0].trim().split(/\s+/).map(Number);
  const colors = new Map();
  for (let i = 1; i <= ncolors; i++) {
    const line = strings[i];
    const key = line.slice(0, cpp);
    // Rest is "key value key value ..." where key in {c, m, g, g4, s}. Prefer c.
    const toks = line.slice(cpp).trim().split(/\s+/);
    const pairs = {};
    let k = null;
    for (const t of toks) {
      if (['c', 'm', 'g', 'g4', 's'].includes(t) && k === null) { k = t; pairs[k] = []; continue; }
      if (['c', 'm', 'g', 'g4', 's'].includes(t) && pairs[k]?.length) { k = t; pairs[k] = []; continue; }
      pairs[k].push(t);
    }
    const spec = (pairs.c || pairs.g || pairs.m || ['none']).join(' ');
    colors.set(key, parseColor(spec));
  }
  const rgba = Buffer.alloc(w * h * 4);
  for (let y = 0; y < h; y++) {
    const row = strings[1 + ncolors + y];
    for (let x = 0; x < w; x++) {
      const c = colors.get(row.slice(x * cpp, x * cpp + cpp));
      const o = (y * w + x) * 4;
      if (c === undefined) throw new Error(`bad pixel at ${x},${y}`);
      if (c) { rgba[o] = c[0]; rgba[o + 1] = c[1]; rgba[o + 2] = c[2]; rgba[o + 3] = 255; }
    }
  }
  return { width: w, height: h, rgba };
}

const CRC_TABLE = new Int32Array(256).map((_, n) => {
  let c = n;
  for (let k = 0; k < 8; k++) c = c & 1 ? 0xedb88320 ^ (c >>> 1) : c >>> 1;
  return c;
});
function crc32(buf) {
  let c = -1;
  for (const b of buf) c = CRC_TABLE[(c ^ b) & 0xff] ^ (c >>> 8);
  return (c ^ -1) >>> 0;
}
function chunk(type, data) {
  const len = Buffer.alloc(4); len.writeUInt32BE(data.length);
  const td = Buffer.concat([Buffer.from(type, 'ascii'), data]);
  const crc = Buffer.alloc(4); crc.writeUInt32BE(crc32(td));
  return Buffer.concat([len, td, crc]);
}

export function encodePng({ width, height, rgba }) {
  const ihdr = Buffer.alloc(13);
  ihdr.writeUInt32BE(width, 0); ihdr.writeUInt32BE(height, 4);
  ihdr[8] = 8; ihdr[9] = 6; // 8-bit RGBA
  const raw = Buffer.alloc((width * 4 + 1) * height);
  for (let y = 0; y < height; y++) {
    raw[y * (width * 4 + 1)] = 0;
    rgba.copy(raw, y * (width * 4 + 1) + 1, y * width * 4, (y + 1) * width * 4);
  }
  return Buffer.concat([
    Buffer.from([0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a]),
    chunk('IHDR', ihdr),
    chunk('IDAT', zlib.deflateSync(raw, { level: 9 })),
    chunk('IEND', Buffer.alloc(0)),
  ]);
}

function* walk(dir) {
  for (const e of fs.readdirSync(dir, { withFileTypes: true })) {
    const p = path.join(dir, e.name);
    if (e.isDirectory()) { if (e.name !== 'temp') yield* walk(p); }
    else if (e.name.endsWith('.xpm') && !/\.(old|date)\.xpm$/.test(e.name)) yield p;
  }
}

if (import.meta.url === `file://${process.argv[1]}`) {
  const src = process.argv[2] || 'graphics';
  const out = process.argv[3] || 'web/assets/gfx';
  for (const f of walk(src)) {
    const dest = path.join(out, path.relative(src, f)).replace(/\.xpm$/, '.png');
    fs.mkdirSync(path.dirname(dest), { recursive: true });
    fs.writeFileSync(dest, encodePng(parseXpm(fs.readFileSync(f, 'latin1'))));
    console.log(dest);
  }
}
