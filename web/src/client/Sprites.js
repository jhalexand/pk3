// Port of src/dla GRGraphicManager / GRGraphicType / GROnscreenGraphic:
// sprite sheets, frames and animation sequences from assets/sprites.json
// (generated from pkgraphics.dat by tools/dat2json.mjs).

import { ANIM } from '../engine/ids.js';

export const REPEAT = -1, DEFAULT = -2, INITIAL = -3;

export function loadImage(src) {
  return new Promise((resolve, reject) => {
    const img = new Image();
    img.onload = () => resolve(img);
    img.onerror = () => reject(new Error(`could not load ${src}`));
    img.src = src;
  });
}

export class SpriteSet {
  static async load(base = 'assets/') {
    const data = await (await fetch(`${base}sprites.json`)).json();
    const set = new SpriteSet(data);
    await Promise.all(Object.entries(data.files).map(async ([n, f]) => {
      set.images[n] = await loadImage(`${base}gfx/${f.path}`);
    }));
    return set;
  }

  constructor(data) {
    this.types = data.types;
    this.images = {};
  }

  // GRGraphicType::getFrame
  frameRect(type, anim, frameNumber) {
    const t = this.types[type];
    if (!t) return null;
    const seq = t.sequences[anim];
    if (anim === ANIM.NOT || !seq || frameNumber < 0) return t.defaultFrame;
    const idx = seq[frameNumber];
    if (idx === REPEAT) return t.frames[seq[frameNumber - 1]] || t.defaultFrame;
    if (idx === DEFAULT || idx === undefined) return t.defaultFrame;
    return t.frames[idx] || t.defaultFrame;
  }

  // GRGraphicType::animate: next frame number for this sequence.
  nextFrame(type, anim, frameNumber) {
    const seq = this.types[type]?.sequences[anim];
    if (anim === ANIM.NOT || !seq || frameNumber < 0) return DEFAULT;
    const next = seq[frameNumber + 1];
    if (next === REPEAT) return frameNumber;
    if (next === DEFAULT || next === undefined) return DEFAULT;
    if (next === INITIAL) return 0;
    return frameNumber + 1;
  }

  // Draw centred on (x, y) as GRGraphicType::draw does.
  draw(ctx, type, anim, frameNumber, x, y) {
    const t = this.types[type];
    const img = t && this.images[t.file];
    const r = this.frameRect(type, anim, frameNumber);
    if (!img || !r) return;
    const w = r[2] - r[0], h = r[3] - r[1];
    if (w <= 0 || h <= 0) return;
    ctx.drawImage(img, r[0], r[1], w, h, Math.trunc(x) - Math.trunc(w / 2), Math.trunc(y) - Math.trunc(h / 2), w, h);
  }
}

// Per-object animation state (GROnscreenGraphic).
export class OnscreenGraphic {
  constructor(sprites, type) {
    this.sprites = sprites;
    this.type = type;
    this.anim = ANIM.NOT;
    this.frame = DEFAULT;
  }

  // Called every 30 ms with the object's current client-side state.
  // Mirrors handleGraphicsCallback: animate, then updateStatus.
  step(obj) {
    const next = this.sprites.nextFrame(this.type, this.anim, this.frame);
    const changed = next !== this.frame;
    this.frame = next;
    if (this.frame === DEFAULT && changed && this.anim === obj.anim) obj.anim = ANIM.NOT;
    if (obj.anim !== this.anim) this.frame = 0;
    this.anim = obj.anim;
    if (this.anim === ANIM.NOT) this.frame = DEFAULT;
  }

  draw(ctx, x, y) {
    this.sprites.draw(ctx, this.type, this.anim, this.frame, x, y);
  }
}
