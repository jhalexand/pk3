#ifndef PK_INJURIES_HEADER
#define PK_INJURIES_HEADER

#include <sys/time.h>

const int PK_INJURY_NONE = 0;
const int PK_INJURY_DEFAULT_PROJECTILE = 7;
const int PK_INJURY_LK_FLAT_KICK = 6;
const int PK_INJURY_LK_SPIN_KICK = 10;

//times
const hrtime_t PK_INJURY_FREEZE_TIME = 5000000000; //5 seconds
const hrtime_t PK_INJURY_BOMB_WAIT_TIME = 2000000000; //2 seconds from creation
const hrtime_t PK_INJURY_NUKE_TIME = 400000000;

#endif

