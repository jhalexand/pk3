// Port of src/gameEng/PKRoundEngine.cxx: best two out of three rounds.
//
// The original slept between rounds. This version is a state machine that the
// host steps every TICK_MS, so it never blocks the page. It also emits
// round/score messages the original never sent, so clients can show and
// announce them:
//   {t:'round', n, score}  {t:'roundEnd', winner, score}  {t:'matchEnd', winner, score}
//   {t:'sync', objs:[[id,x,y,vx,vy]...]}
//   {t:'pause', paused, quiet}  (quiet: freeze without showing the pause screen)

import { GameEngine } from './GameEngine.js';
import { SND, A } from './ids.js';

export const TICK_MS = 20;
const NS = 1e6; // ns per ms
const SYNC_MS = 250;
const ROUND_SOUNDS = [SND.ONE, SND.TWO, SND.THREE];

export class RoundEngine {
  constructor({ players, emit = () => {}, clock }) {
    this.players = players;
    this.emit = emit;
    this.clock = clock;
    this.score = [0, 0];
    this.round = 0;
    this.engine = null;
    this.phase = 'idle';
    this.phaseStart = 0;
    this.cues = [];
    this.lastSync = 0;
    this.winner = 0;
    this.pauseAtPlay = false; // a pause asked for before play began
  }

  ms() { return this.clock() / NS; }

  start() { this.startRound(); }

  startRound() {
    this.round += 1;
    this.engine?.destroy();
    // 'round' first: clients clear the field on it, before the new objects arrive.
    this.emit({ t: 'round', n: this.round, score: [...this.score] });
    this.engine = new GameEngine({ players: this.players, emit: this.emit, clock: this.clock, serve: false });
    this.emit({ t: 'status', life: [...this.engine.life] });
    this.setPhase('intro');
    // "Round" ... "One" ... "Fight!" The original only played FIGHT.
    this.cue(0, () => this.emit({ t: 'sound', id: SND.ROUND }));
    this.cue(700, () => this.emit({ t: 'sound', id: ROUND_SOUNDS[Math.min(this.round, 3) - 1] }));
    this.cue(1500, () => {
      this.emit({ t: 'sound', id: SND.FIGHT });
      // Objects were created during the intro; don't let them jump forward.
      const now = this.clock();
      for (const o of this.engine.allObjects()) o.timestamp = now;
      // The ball only appears now, so it doesn't fly around during the intro.
      this.engine.serveBall();
      this.setPhase('play');
      if (this.pauseAtPlay) {
        this.pauseAtPlay = false;
        this.engine.setPaused(true);
      }
    });
  }

  setPhase(p) {
    this.phase = p;
    this.phaseStart = this.ms();
  }

  cue(afterMs, fn) { this.cues.push({ at: this.ms() + afterMs, fn }); }

  tick() {
    const now = this.ms();
    const due = this.cues.filter((c) => c.at <= now);
    this.cues = this.cues.filter((c) => c.at > now);
    for (const c of due) c.fn();

    if (this.phase !== 'play') return;
    const winner = this.engine.tick();
    if (!this.engine.paused && now - this.lastSync >= SYNC_MS) {
      this.lastSync = now;
      this.emit({ t: 'sync', objs: this.engine.snapshot() });
    }
    if (winner) this.endRound(winner);
  }

  endRound(winner) {
    this.engine.processEventList();
    this.score[winner - 1] += 1;
    this.winner = winner;
    this.setPhase('roundOver');
    this.emit({ t: 'pause', paused: true, quiet: true }); // freeze clients' extrapolation
    const matchOver = this.score[0] === 2 || this.score[1] === 2;
    this.cue(1000, () => this.emit({ t: 'roundEnd', winner, score: [...this.score] }));
    this.cue(4000, () => {
      if (matchOver) {
        this.setPhase('done');
        this.emit({ t: 'matchEnd', winner, score: [...this.score] });
      } else {
        this.startRound();
      }
    });
  }

  handleAction(playerNum, action) {
    if (this.phase === 'play') this.engine.handleAction(playerNum, action);
    // A pause during the round intro or between rounds takes effect on "Fight!".
    else if (action === A.PAUSE || action === A.UNPAUSE) this.pauseAtPlay = action === A.PAUSE;
  }

  stop() {
    this.cues = [];
    this.phase = 'done';
  }
}
