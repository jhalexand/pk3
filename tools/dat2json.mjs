#!/usr/bin/env node
// Convert src/dla/pkgraphics.dat (the graphics engine's sprite description) to JSON.
// Usage: node tools/dat2json.mjs [in] [out]
//
// Output:
// { files: { <fileNum>: { path: "paddles/new/paddle-lk-right.png", dependsOn: <typeId|-1> } },
//   types: { <typeId>: { file, defaultFrame: [x0,y0,x1,y1], frames: [[x0,y0,x1,y1], ...],
//                        sequences: { <animId>: [frameIdx..., terminator] } } } }
// Terminators follow GR_local.h: R (repeat last) = -1, D (revert to default) = -2,
// B (back to first frame) = -3.

import fs from 'node:fs';

export const REPEAT = -1, DEFAULT = -2, INITIAL = -3;

// GRGraphicManager computes rectangles with C integer division.
const rect = (cx, cy, w, h) => [
  cx - Math.trunc(w / 2), cy - Math.trunc(h / 2), cx + Math.trunc(w / 2), cy + Math.trunc(h / 2),
];

export function parseDat(text) {
  const toks = text
    .split('\n')
    .map((l) => l.replace(/(\/\/|#).*$/, ''))
    .join(' ')
    .split(/\s+/)
    .filter(Boolean);
  let i = 0;
  const next = () => toks[i++];
  const num = () => Number(next());
  const files = {};
  const types = {};
  let cur = null;
  while (i < toks.length) {
    const cmd = next().toUpperCase();
    switch (cmd) {
      case 'NUMXPMFILES': case 'NUMTYPEIDS': num(); break;
      case 'XPMFILE': {
        const p = next();
        const n = num();
        const dependsOn = num();
        files[n] = { path: p.replace(/^.*\/graphics\//, '').replace(/\.xpm$/, '.png'), dependsOn };
        break;
      }
      case 'TYPEID': {
        const id = num(); const file = num(); num(); num();
        cur = types[id] = { file, defaultFrame: null, frames: [], sequences: {} };
        break;
      }
      case 'DEFAULTFRAME': cur.defaultFrame = rect(num(), num(), num(), num()); break;
      case 'FRAME': { const n = num(); cur.frames[n] = rect(num(), num(), num(), num()); break; }
      case 'SEQUENCE': {
        const anim = num(); const count = num();
        const seq = [];
        for (let k = 0; k < count; k++) {
          const t = next();
          if (t === 'R') { seq.push(REPEAT); break; }
          if (t === 'D') { seq.push(DEFAULT); break; }
          if (t === 'B') { seq.push(INITIAL); break; }
          seq.push(Number(t));
        }
        cur.sequences[anim] = seq;
        break;
      }
      default:
        throw new Error(`unexpected token ${cmd} at ${i}`);
    }
  }
  return { files, types };
}

if (import.meta.url === `file://${process.argv[1]}`) {
  const src = process.argv[2] || 'src/dla/pkgraphics.dat';
  const out = process.argv[3] || 'web/assets/sprites.json';
  const data = parseDat(fs.readFileSync(src, 'utf8'));
  fs.writeFileSync(out, JSON.stringify(data));
  console.log(`${out}: ${Object.keys(data.files).length} files, ${Object.keys(data.types).length} types`);
}
