// Replaces src/audio/PKAudioPlayer (which used the rplay daemon) with WebAudio.
// Sound ids map to the files from PKClient::startSound.

import { SND } from '../engine/ids.js';

const FILES = {
  [SND.TOASTY]: 'toasty',
  [SND.FIGHT]: 'fight',
  [SND.REPTILE_INVIS]: 'skull',
  [SND.SUB_PROJ_THROW]: 'freeze',
  [SND.SUB_PROJ_HIT]: 'frozen',
  [SND.BLOCK]: 'donut',
  [SND.UNBLOCK]: 'morph',
  [SND.CYRAX_BOMB_EXPLODE]: 'bombexplode',
  [SND.CYRAX_BOMB_DROP]: 'bomb',
  [SND.GUY_HIT]: 'hitGuy',
  [SND.GIRL_HIT]: 'hitGirl',
  [SND.KANG_HIT]: 'hitKang',
  [SND.GUY_DEATH]: 'guyDeath',
  [SND.GIRL_DEATH]: 'girlDeath',
  [SND.KANG_DEATH]: 'kangDeath',
  [SND.ROUND]: 'round',
  [SND.ONE]: 'one',
  [SND.TWO]: 'two',
  [SND.THREE]: 'three',
};

// Announcer clips that exist for some characters (from src/which.sounds).
const NAMES = {
  'Cyrax': 'cyrax', 'Jade': 'jade', 'Kabal': 'kabal', 'Liu Kang': 'liukang', 'Reptile': 'reptile', 'Sub Zero': 'subzero',
};

export class Audio {
  constructor(base = 'assets/sfx/') {
    this.base = base;
    this.ctx = null;
    this.buffers = new Map();
    this.music = null;
    this.musicName = null;
    this.muted = false;
    try { this.muted = localStorage.getItem('pk3.muted') === '1'; } catch {}
  }

  // Browsers only allow audio after a user gesture; call from a click/keydown.
  unlock() {
    if (!this.ctx) {
      const Ctx = window.AudioContext || window.webkitAudioContext;
      if (!Ctx) return;
      this.ctx = new Ctx();
      this.gain = this.ctx.createGain();
      this.gain.gain.value = this.muted ? 0 : 1;
      this.gain.connect(this.ctx.destination);
      const names = [...Object.values(FILES), ...Object.values(NAMES), 'wins', 'introMusic', 'selectmusic'];
      for (const n of names) this.fetch(n);
      if (this.musicName) this.playMusic(this.musicName);
    }
    if (this.ctx.state === 'suspended') this.ctx.resume();
  }

  fetch(name) {
    if (!this.buffers.has(name)) {
      this.buffers.set(name, fetch(`${this.base}${name}.mp3`)
        .then((r) => r.arrayBuffer())
        .then((b) => this.ctx.decodeAudioData(b))
        .catch(() => null));
    }
    return this.buffers.get(name);
  }

  async playFile(name, { loop = false } = {}) {
    if (!this.ctx) return null;
    const buf = await this.fetch(name);
    if (!buf) return null;
    const src = this.ctx.createBufferSource();
    src.buffer = buf;
    src.loop = loop;
    src.connect(this.gain);
    src.start();
    return src;
  }

  play(soundId) {
    const f = FILES[soundId];
    if (f) this.playFile(f);
  }

  // "<name> wins", where we have a recording of the name.
  async announceWinner(characterName) {
    const n = NAMES[characterName];
    if (n) {
      const src = await this.playFile(n);
      if (src) await new Promise((r) => { src.onended = r; });
    }
    this.playFile('wins');
  }

  // Background music: introMusic on the menus, selectmusic while choosing
  // fighters, as planned in src/which.sounds.
  async playMusic(name) {
    if (this.musicName === name && this.music) return;
    this.stopMusic();
    this.musicName = name;
    if (!name || !this.ctx) return;
    const src = await this.playFile(name, { loop: true });
    if (this.musicName === name) this.music = src;
    else src?.stop();
  }

  stopMusic() {
    try { this.music?.stop(); } catch {}
    this.music = null;
    this.musicName = null;
  }

  setMuted(m) {
    this.muted = m;
    if (this.gain) this.gain.gain.value = m ? 0 : 1;
    try { localStorage.setItem('pk3.muted', m ? '1' : '0'); } catch {}
  }
}
