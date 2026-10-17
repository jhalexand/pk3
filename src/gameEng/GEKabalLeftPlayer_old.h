/*************************************************************************/
/*    NAME: Elaine Chen                                                  */
/*    ACCT: eyc                                                          */
/*    FILE: GEKabalLeftPlayer.h                                          */
/*    DATE: Sun May  4 23:56:12 1997                                     */
/*************************************************************************/


#ifndef GEKABALLEFTPLAYER_HEADER
#define GEKABALLEFTPLAYER_HEADER

#include "GEPlayer.h"

class GEKabalLeftPlayer : public GEPlayer {
public:
    GEKabalLeftPlayer(PKID id,
				 int playerNum,
				 PKPoint* pos,
				 GEContainer* cont,
				 PKGameEngine* engine);
    virtual ~GEKabalLeftPlayer();

    virtual void intersectWithWall(GEGameObject* wall);
    virtual void intersectWithPlayer(GEGameObject* player);
    virtual void intersectWithProjectile(GEGameObject* proj);

    virtual void moveUp();
    virtual void moveDown();
    virtual void moveLeft();
    virtual void moveRight();
    virtual void stopVertical();
    virtual void stopHorizontal();
    virtual void punch();
    virtual void kick();
    virtual void uppercut();
    virtual void lowercut();
    virtual void sweep();
    virtual void block();
    virtual void unblock();
    
    virtual void specialMove1();
    virtual void specialMove2();
    virtual void specialMove3();

protected:
    int _flat_kicking;
};

#endif
