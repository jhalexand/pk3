#ifndef PK_KEY_INCLUDED
#define PK_KEY_INCLUDED

enum PKKey {
PK_KEY_UNDEFINED = 0,
PK_KEY_PUNCH = 1,
PK_KEY_KICK = 2,
PK_KEY_UP = 3,
PK_KEY_DOWN = 4,
PK_KEY_LEFT = 5,
PK_KEY_RIGHT = 6,
PK_KEY_BLOCK = 7,
PK_KEY_PAUSE = 8,
// These added temporarily, for the graphicDemo: (they are actually combos)
PK_KEY_SWEEP_KICK = 9,
PK_KEY_UPPERCUT = 10,
PK_KEY_UPPERCUT_DOWN = 11,
PK_KEY_SPIN = 12,
PK_KEY_FLAT_KICK = 13,
PK_KEY_UNPAUSE = 14 //added to prevent weirdness - mip
};

#endif
