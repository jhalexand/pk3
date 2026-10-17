/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: dla                                                 */
/*    FILE: PKDimensions.h                                      */
/*    ASGN:                                                     */
/*    DATE: Thu May  1 11:40:44 1997                            */
/****************************************************************/


#ifndef PKDIMENSIONS_HEADER
#define PKDIMENSIONS_HEADER

// Screen coordinates are such that (0,0) == upper left corner
// (516, 432) is the lower right.

const int PK_DIM_SCREEN_WIDTH = 516;
const int PK_DIM_SCREEN_HEIGHT = 432;

// info for positioning walls and other positions correctly
const int PK_DIM_WALL_TOP_Y = 84; //furthest upwards a player can move.
const int PK_DIM_WALL_BOTTOM_Y = PK_DIM_SCREEN_HEIGHT;
const int PK_DIM_WALL_LEFT_X = 0;
const int PK_DIM_WALL_RIGHT_X = PK_DIM_SCREEN_WIDTH;

// Dimensions for graphics below

// Dim for ball
const int PK_DIM_BALL_WIDTH = 12;
const int PK_DIM_BALL_HEIGHT = 12;
const double PK_DIM_BALL_SPEED = 30;

// Dims for Paddles
const int PK_DIM_PADDLE_WIDTH = 30;
const int PK_DIM_PADDLE_HEIGHT = 55;
const int PK_DIM_PADDLE_KICK_ADDED_WIDTH = 20;
const int PK_DIM_PADDLE_KICK_ADDED_HEIGHT = 0;
const int PK_DIM_PADDLE_PUNCH_ADDED_WIDTH = 20;
const int PK_DIM_PADDLE_PUNCH_ADDED_HEIGHT = 0;
const int PK_DIM_PADDLE_UPPERCUT_ADDED_WIDTH = 40;
const int PK_DIM_PADDLE_UPPERCUT_ADDED_HEIGHT = 20;
const int PK_DIM_PADDLE_LOWERCUT_ADDED_WIDTH = 40;
const int PK_DIM_PADDLE_LOWERCUT_ADDED_HEIGHT = 20;
const int PK_DIM_PADDLE_SWEEP_ADDED_WIDTH = 40;
const int PK_DIM_PADDLE_SWEEP_ADDED_HEIGHT = 0;

// Dims for projectiles and speeds

// Liu Kang
const int PK_DIM_LK_PROJ_WIDTH = 68;
const int PK_DIM_LK_PROJ_HEIGHT = 15;
const double PK_DIM_LK_PROJ_SPEED = 30;
const double PK_DIM_LK_SPIN_SPEED = 55;
const double PK_DIM_LK_FLAT_SPEED = 65;

// Reptile

const int PK_DIM_REPTILE_PROJ_WIDTH = 70;
const int PK_DIM_REPTILE_PROJ_HEIGHT = 15;
const double PK_DIM_REPTILE_PROJ_SPEED = 35;

// Jade
const int PK_DIM_JADE_PROJ_WIDTH = 40;
const int PK_DIM_JADE_PROJ_HEIGHT = 40;
const double PK_DIM_JADE_PROJ_SPEED = 35;

// Explode:
const int PK_DIM_EXPLODE_WIDTH = 0;
const int PK_DIM_EXPLODE_HEIGHT = 0;

// Sub zero:
const int PK_DIM_SZ_PROJ_WIDTH = 60;
const int PK_DIM_SZ_PROJ_HEIGHT = 20;
const double PK_DIM_SZ_PROJ_SPEED = 30;

// Cyrax
const int PK_DIM_CYRAX_NET_WIDTH = 55;
const int PK_DIM_CYRAX_NET_HEIGHT = 55;
const double PK_DIM_CYRAX_NET_SPEED = 40;
const int PK_DIM_CYRAX_BOMB_WIDTH = 16;
const int PK_DIM_CYRAX_BOMB_HEIGHT = 16;
const double PK_DIM_CYRAX_BOMB_SPEED = 35;
const int PK_DIM_CYRAX_LEFT_NUKE_HEIGHT = 100;
const int PK_DIM_CYRAX_LEFT_NUKE_WIDTH = 200;

// Kabal
const int PK_DIM_KABAL_PROJ_WIDTH = 40;
const int PK_DIM_KABAL_PROJ_HEIGHT = 40;
const double PK_DIM_KABAL_PROJ_SPEED = 50;
const int PK_DIM_KABAL_WHEEL_WIDTH = 60;
const int PK_DIM_KABAL_WHEEL_HEIGHT = 100;
const double PK_DIM_KABAL_WHEEL_SPEED = 25;

#endif
