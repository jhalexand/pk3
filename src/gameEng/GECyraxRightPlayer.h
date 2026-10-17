/*************************************************************************/
/*    NAME: Elaine Chen                                                  */
/*    ACCT: eyc                                                          */
/*    FILE: GECyraxLeftPlayer.h                                          */
/*    DATE: Sun May  4 16:15:51 1997                                     */
/*************************************************************************/


#ifndef GECYRAXRIGHTPLAYER_HEADER
#define GECYRAXRIGHTPLAYER_HEADER

#include <PKids.h>
#include "GEPlayer.h"

class GEContainer;
class PKGameEngine;

class GECyraxRightPlayer : public GEPlayer {
public:
    GECyraxRightPlayer(PKID id,
				  int playerNum,
				  PKPoint* pos,
				  GEContainer* cont,
				  PKGameEngine* engine);
    virtual ~GECyraxRightPlayer();

    virtual void specialMove1();
    virtual void specialMove2();
    virtual void specialMove3();

protected:

};

#endif
