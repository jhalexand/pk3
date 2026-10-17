/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: dla                                                 */
/*    FILE: GELKRightPlayer.h                                   */
/*    ASGN:                                                     */
/*    DATE: Fri May  2 20:14:56 1997                            */
/****************************************************************/


#ifndef GELKRIGHTPLAYER_HEADER
#define GELKRIGHTPLAYER_HEADER

#include "GEPlayer.h"

class GEPlayer;

class GELKRightPlayer : public GEPlayer {
public:

  GELKRightPlayer(PKID id,
		   int playerNum,
		   PKPoint* pos,
		   GEContainer* cont,
		   PKGameEngine* engine);
  virtual ~GELKRightPlayer();
  
  virtual void intersectWithWall(GEGameObject* wall); // unset injury fields
  virtual void intersectWithPlayer (GEGameObject *player);
  virtual void intersectWithProjectile (GEGameObject *projectile);

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
  virtual void specialMove1(); // Fire projectile
  virtual void specialMove2();  // Spinning kick, set injury field!!
  virtual void specialMove3(); // Flat kick, set injury field!!
  

protected:

  int _spin_kicking;
  int _flat_kicking;
};

#endif
