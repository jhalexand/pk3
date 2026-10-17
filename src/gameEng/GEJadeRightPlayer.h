/*************************************************************************/
/*    NAME: Elaine Chen                                                  */
/*    ACCT: eyc                                                          */
/*    FILE: GEJadeRightPlayer.h                                           */
/*    DATE: Sat May  3 21:40:55 1997                                     */
/*************************************************************************/


#ifndef GEJADERIGHTPLAYER_HEADER
#define GEJADERIGHTPLAYER_HEADER

#include "GEPlayer.h"

class GEJadeRightPlayer : public GEPlayer {

public:
    GEJadeRightPlayer(PKID id,
				 int playerNum,
				 PKPoint* pos,
				 GEContainer* cont,
				 PKGameEngine* engine);
    virtual ~GEJadeRightPlayer();

    virtual void intersectWithProjectile (GEGameObject *proj);
    virtual void update();
    virtual void specialMove1();
    virtual void specialMove2();
    virtual void specialMove3();
    virtual void attack(PKAnimID animID, int injury,
			  int addedWidth, int addedHeight);
 
protected:

  hrtime_t _invulnerability_timer;
  int _projectile_invulnerability;
};

#endif
