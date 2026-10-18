# Pong Kombat 3 — browser version

A port of the 1997 Solaris/X/Motif game to plain JavaScript. It uses the original graphics, sounds and game rules.

## Play locally

```
python3 -m http.server -d web 8000
# open http://localhost:8000
```

## How it fits together

| 1997 | Browser |
|---|---|
| `pkd` lobby server + `pkgameserver` | `src/net/Host.js`, which runs in the browser of whoever creates the game |
| TCP sockets (`src/netlib`) | PeerJS (WebRTC) data channel, paired with a 5-character code (`src/net/links.js`) |
| `src/gameEng` | `src/engine/` (characters mirrored left/right instead of duplicated) |
| `libpkphysics.so` (source lost) | `src/engine/physics.js`, recovered from the SPARC binary; see `tools/physics-disasm.md` |
| `src/dla` graphics engine | `src/client/GameView.js`, `Sprites.js`, `LetterWriter.js` |
| `src/gui` Motif screens | `index.html`, `src/ui/app.js` |
| `*Keys.h` combo detectors | `src/input/PaddleKeys.js` |
| `pkaiclient` | `src/ai/AIClient.js` |
| rplay audio | WebAudio (`src/client/Audio.js`) |

## Regenerating assets

```
node tools/xpm2png.mjs           # graphics/**/*.xpm -> web/assets/gfx/**/*.png
node tools/dat2json.mjs          # src/dla/pkgraphics.dat -> web/assets/sprites.json
sh tools/convert-audio.sh        # sounds/* (Sun .au) -> web/assets/sfx/*.mp3 (needs ffmpeg)
```

## Tests

```
node --test test/*.test.mjs
```

## Multiplayer networking

Pairing uses the free public PeerJS broker. After pairing, the game traffic goes directly between the two browsers. Some networks, such as strict corporate or carrier NATs, block direct connections. Those players would need a TURN relay server, which isn't configured.
