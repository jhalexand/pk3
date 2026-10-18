#!/bin/sh
# Convert the Sun .au (8-bit mu-law) sounds used by the game to MP3 for browsers.
# Usage: sh tools/convert-audio.sh   (run from the repo root; needs ffmpeg with libmp3lame)
set -e
OUT=web/assets/sfx
mkdir -p "$OUT"

# Sounds from PKClient::startSound (src/gui/PKClient.C), including round/one/two/three,
# which the original never loaded because of a count bug, plus the music and announcer
# clips listed in src/which.sounds.
SOUNDS="toasty fight skull freeze frozen donut morph bombexplode bomb
hitGuy hitGirl hitKang guyDeath girlDeath kangDeath
round one two three wins
cyrax kabal liukang subzero
introMusic selectmusic"

for s in $SOUNDS; do
  ffmpeg -hide_banner -loglevel error -y -f au -i "sounds/$s" -ac 1 -c:a libmp3lame -q:a 4 "$OUT/$s.mp3"
  echo "$OUT/$s.mp3"
done

# Character names recorded later as MP3 (src/which.sounds listed them as "need this").
for s in jade reptile; do
  cp "sounds/$s.mp3" "$OUT/$s.mp3"
  echo "$OUT/$s.mp3"
done
