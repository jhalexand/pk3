/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: dla                                                 */
/*    FILE: GESZLeftPlayer.h                                    */
/*    ASGN:                                                     */
/*    DATE: Sat May  3 01:50:20 1997                            */
/****************************************************************/


#ifndef GESZLEFTPLAYER_HEADER
#define GESZLEFTPLAYER_HEADER

#include "GEPlayer.h"

class GEPlayer;

class GESZLeftPlayer : public GEPlayer {
public:

  GESZLeftPlayer(PKID id,
			  int playerNum,
			  PKPoint* pos,
			  GEContainer* cont,
			  PKGameEngine* engine);
  virtual ~GESZLeftPlayer();

  virtual void specialMove1(); // Fire projectile
  virtual void specialMove2();  // Fire off top of screen..
  virtual void specialMove3(); // Leave trail on screen..

};

#endif
