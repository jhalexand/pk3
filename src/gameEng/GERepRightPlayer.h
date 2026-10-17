/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: dla                                                 */
/*    FILE: GERepLeftPlayer.h                                   */
/*    ASGN:                                                     */
/*    DATE: Sun May  4 18:57:47 1997                            */
/****************************************************************/


#ifndef GEREPRIGHTLAYER_HEADER
#define GEREPRIGHTPLAYER_HEADER

#include "GEPlayer.h"

class GERepRightPlayer : public GEPlayer {

public:

  GERepRightPlayer(PKID id,
			    int playerNum,
			    PKPoint* pos,
			    GEContainer* cont,
			    PKGameEngine* engine);
  ~GERepRightPlayer();
  
  virtual void specialMove1(); // Makes himself invisible 
  virtual void specialMove2();  
  virtual void specialMove3(); 

};

#endif
