/*************************************************************************/
/*    NAME: Elaine Chen                                                  */
/*    ACCT: eyc                                                          */
/*    FILE: GEPlayer.h                                                   */
/*    DATE: Fri Apr 25 19:47:40 1997                                     */
/*************************************************************************/


#ifndef GEPLAYER_HEADER
#define GEPLAYER_HEADER

#include "GEGameObject.h"

class PKGameEngine;

class GEPlayer : public GEGameObject {
public:
    GEPlayer(PKID id,
		   PKTypeID type,
		   int playerNum,
		   int team,
		   PKPoint* pos,
		   GEContainer* cont,
		   PKGameEngine* engine);
    virtual ~GEPlayer();

    virtual void intersect(GEGameObject* obj);
    virtual void intersectWithBall(GEGameObject* ball);
    virtual void intersectWithWall(GEGameObject* wall);
    virtual void intersectWithPlayer(GEGameObject* player);
    virtual void intersectWithProjectile(GEGameObject* obj);

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
    virtual void specialMove1() = 0;
    virtual void specialMove2() = 0;
    virtual void specialMove3() = 0;
    virtual void stop();
  
    virtual void update(); // Anything the object needs to do every frame.
    virtual void getCaughtByNet(); //should this be virtual? not sure.
    virtual void spin();
    
    void injure(int amount);
    void subtractLife (int amount); // Takes away life without checking block
    void attack(PKAnimID animID, int injury,
			 int addedWidth, int addedHeight);

    void freeze();
    void unfreeze();

    void turnVisible();
    void bounceBack(GEGameObject* wall);
    
    int getPlayerNum();
    int getTeam();
    int getLife();
    int getFrozen() { return _frozen;}
    int getBlock() { return _block;}
    
protected:
    int _playerNum;
    int _team;
    int _life;   //percentage
    int _block;  
    int _frozen; //frozen by sub-zero
    int _caught; //caught by net
    int _invisible; // invisible??
    hrtime_t _timer;  //time stamp?
    
};

#endif
