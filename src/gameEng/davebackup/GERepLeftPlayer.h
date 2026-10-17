/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: dla                                                 */
/*    FILE: GERepLeftPlayer.h                                   */
/*    ASGN:                                                     */
/*    DATE: Sun May  4 18:57:47 1997                            */
/****************************************************************/


#ifndef GEREPLEFTPLAYER_HEADER
#define GEREPLEFTPLAYER_HEADER

#include "GEPlayer.h"

class GERepLeftPlayer : public GEPlayer {

public:

  GERepLeftPlayer(PKID id,
			    int playerNum,
			    PKPoint* pos,
			    GEContainer* cont,
			    PKGameEngine* engine);
  ~GERepLeftPlayer();
  
  virtual void specialMove1(); // Makes himself invisible 
  virtual void specialMove2();  
  virtual void specialMove3(); 

};

#endif
