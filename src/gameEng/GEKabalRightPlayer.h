/*************************************************************************/
/*    NAME: Elaine Chen                                                  */
/*    ACCT: eyc                                                          */
/*    FILE: GEKabalRightPlayer.h                                         */
/*    DATE: Mon May  5 00:55:07 1997                                     */
/*************************************************************************/


#ifndef GEKABALRIGHTPLAYER_HEADER
#define GEKABALRIGHTPLAYER_HEADER

#include "GEPlayer.h"

class GEKabalRightPlayer : public GEPlayer {
public:
    GEKabalRightPlayer(PKID id,
				   int playerNum,
				   PKPoint* pos,
				   GEContainer* cont,
				   PKGameEngine* engine);
    virtual ~GEKabalRightPlayer();

    virtual void specialMove1();
    virtual void specialMove2();
    virtual void specialMove3();
    virtual void intersectWithWall(GEGameObject *);
    virtual void intersectWithPlayer(GEGameObject *);
    virtual void intersectWithProjectile (GEGameObject *);
  
  virtual void moveUp(); // Check to see if we can, then do it in superclass
  virtual void moveDown(); // ""
  virtual void moveLeft(); // ""
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

protected:

  int _flat_kicking;
};


#endif
