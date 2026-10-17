/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: dla                                                 */
/*    FILE: GESZRightPlayer.h                                    */
/*    ASGN:                                                     */
/*    DATE: Sat May  3 01:50:20 1997                            */
/****************************************************************/


#ifndef GESZRIGHTPLAYER_HEADER
#define GESZRIGHTPLAYER_HEADER

#include "GEPlayer.h"

class GEPlayer;

class GESZRightPlayer : public GEPlayer {
public:

  GESZRightPlayer(PKID id,
			  int playerNum,
			  PKPoint* pos,
			  GEContainer* cont,
			  PKGameEngine* engine);
  virtual ~GESZRightPlayer();

  virtual void specialMove1(); // Fire projectile
  virtual void specialMove2();  // Fire off top of screen..
  virtual void specialMove3(); // Leave trail on screen..

};

#endif
