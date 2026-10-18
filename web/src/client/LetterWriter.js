// Port of src/dla/GRLetterWriter: a bitmap font cut from phrases2.xpm.
// Uppercase A-Z only; anything else that isn't a space is skipped.

const X = [1, 11, 20, 30, 40, 48, 56, 67, 77, 81, 88, 98, 106, 119, 128, 139, 147,
  158, 1, 10, 19, 29, 39, 53, 64, 74, 82];
const Y = [176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176,
  176, 186, 186, 186, 186, 186, 186, 186, 186];
const HEIGHT = 9;

export class LetterWriter {
  constructor(image) {
    this.image = image; // phrases2.png
  }

  glyphWidth(c) {
    const w = X[c + 1] - X[c] - 2;
    return w < 0 ? 7 : w;
  }

  advance(c) {
    const w = X[c + 1] - X[c] + 1;
    return (w < 0 ? 10 : w) + 2;
  }

  measure(str) {
    let w = 0;
    for (const ch of str.toUpperCase()) {
      const c = ch.charCodeAt(0) - 65;
      if (ch === ' ') w += 5;
      else if (c >= 0 && c < 26) w += this.advance(c);
    }
    return w;
  }

  print(ctx, x, y, str, scale = 1) {
    let cx = x;
    for (const ch of str.toUpperCase()) {
      const c = ch.charCodeAt(0) - 65;
      if (ch === ' ') { cx += 5 * scale; continue; }
      if (c < 0 || c >= 26) continue;
      const w = this.glyphWidth(c);
      ctx.drawImage(this.image, X[c], Y[c], w, HEIGHT, cx, y, w * scale, HEIGHT * scale);
      cx += this.advance(c) * scale;
    }
  }

  printCentered(ctx, cx, y, str, scale = 1) {
    this.print(ctx, Math.round(cx - (this.measure(str) * scale) / 2), y, str, scale);
  }
}
