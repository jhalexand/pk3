/*************************************************************************/
/*    NAME: Elaine Chen                                                  */
/*    ACCT: eyc                                                          */
/*    FILE: GECyraxLeftPlayer.h                                          */
/*    DATE: Sun May  4 16:15:51 1997                                     */
/*************************************************************************/


#ifndef GECYRAXLEFTPLAYER_HEADER
#define GECYRAXLEFTPLAYER_HEADER

#include <PKids.h>
#include "GEPlayer.h"

class GEContainer;
class PKGameEngine;

class GECyraxLeftPlayer : public GEPlayer {
public:
    GECyraxLeftPlayer(PKID id,
				  int playerNum,
				  PKPoint* pos,
				  GEContainer* cont,
				  PKGameEngine* engine);
    virtual ~GECyraxLeftPlayer();

    virtual void specialMove1();
    virtual void specialMove2();
    virtual void specialMove3();

protected:

};

#endif
