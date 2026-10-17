/*************************************************************************
 *    NAME: Elaine Chen
 *    USER: eyc
 *    FILE: GEPlayer.cxx
 *    DATE: Sat Apr 26 16:19:27 US/Eastern 1997
 *************************************************************************/
#include "GEPlayer.h"
#include "PKGameEngine.h"
#include "GEProjectile.h"
#include "GERemoveObjectEvent.h"
#include "GEExplosionProjectile.h"
#include <PKInjuries.h>
#include <PKDimensions.h>
#include <stdlib.h>
#include <iostream.h>

/*************************************************************************
 * Function Name: GEPlayer::GEPlayer
 * Parameters: PKTypeID type, int ID
 * Effects: 
 *************************************************************************/

GEPlayer::GEPlayer(PKID id,
			    PKTypeID type,
			    int playerNum,
			    int team,
			    PKPoint* pos,
			    GEContainer* cont,
			    PKGameEngine* engine)
    : GEGameObject(id, type, 0, cont, PK_DIM_PADDLE_WIDTH,
			    PK_DIM_PADDLE_HEIGHT, engine),
	 _playerNum(playerNum), _team(team), _life(100), _block(0), _frozen(0),
	 _caught(0), _invisible(0)
{
    setPosition(*pos);
}


/*************************************************************************
 * Function Name: GEPlayer::~GEPlayer
 * Parameters: 
 * Effects: 
 *************************************************************************/

GEPlayer::~GEPlayer()
{
}


/*=======================================================================*/
/*=======================================================================*/
/*==                        Intersects                                 ==*/
/*=======================================================================*/
/*=======================================================================*/


/*************************************************************************
 * Function Name: GEPlayer::intersect
 * Parameters: GEGameObject* obj
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEPlayer::intersect(GEGameObject* obj)
{
    obj->intersectWithPlayer(this);
}


/*************************************************************************
 * Function Name: GEPlayer::intersectWithBall
 * Parameters: GEGameObject* ball
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEPlayer::intersectWithBall(GEGameObject* ball)
{
    //nothing should happen to player when it intersects with a ball.
}


/*************************************************************************
 * Function Name: GEPlayer::intersectWithWall
 * Parameters: GEGameObject* wall
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEPlayer::intersectWithWall(GEGameObject* wall)
{
   stop();
   bounceBack(wall);
}


/*************************************************************************
 * Function Name: GEPlayer::intersectWithPlayer
 * Parameters: GEGameObject* player
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEPlayer::intersectWithPlayer(GEGameObject* player)
{
    stop();
    ((GEPlayer*) player)->injure(_injury);
}


/*************************************************************************
 * Function Name: GEPlayer::intersectWithProjectile
 * Parameters: GEGameObject* obj
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEPlayer::intersectWithProjectile(GEGameObject* obj)
{
    stop();
    injure(obj->getInjury());
    /*if (_frozen)
	   unfreeze();*/
}


/*=======================================================================*/
/*=======================================================================*/
/*==                           Move It!                                ==*/
/*=======================================================================*/
/*=======================================================================*/


/*************************************************************************
 * Function Name: GEPlayer::bounceBack
 * Parameters: GEGameObject* wall
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEPlayer::bounceBack(GEGameObject* wall)
{
  //HACK!!
  //This should only be called from a player's intersectWithWall method
  PKTypeID wallType = wall->getTypeID();
  
  if (wallType == PK_TYPE_WALL_HORIZONTAL) {
    //check if top wall
    if ((wall->getPosition())[1] < _pos[1])
	 _pos.setCoord(1, _pos[1] + 2);
    //else it is the bottom wall
    else
	 _pos.setCoord(1, _pos[1] - 2);
  }
  else if (wallType == PK_TYPE_WALL_VERTICAL) {
    //check if left wall
    if ((wall->getPosition())[0] < _pos[0])
	 _pos.setCoord(0, _pos[0] + 2);
    //else it is the right wall
    else
	 _pos.setCoord(0, _pos[0] - 2);
  }

}

/*************************************************************************
 * Function Name: GEPlayer::stopVertical
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEPlayer::stopVertical()
{
    if ((!_block)&&(!_frozen)) {
	   _vector.setCoord (1, 0);
	   _engine->broadcastUpdate(this);
    }
}


/*************************************************************************
 * Function Name: GEPlayer::stopHorizontal
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEPlayer::stopHorizontal()
{
    if ((!_block) && (!_frozen)) {
	   _vector.setCoord (0, 0);
	   _engine->broadcastUpdate(this);
    }
}

/*************************************************************************
 * Function Name: GEPlayer::moveUp
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEPlayer::moveUp()
{
    if ((!_block) && (!_frozen)) {
	   _vector.setCoord(1, -10);
	   _engine->broadcastUpdate(this);
    }
}


/*************************************************************************
 * Function Name: GEPlayer::moveDown
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEPlayer::moveDown()
{
    if ((!_block) && (!_frozen)) {
	   _vector.setCoord(1, 10);
	   _engine->broadcastUpdate(this);
    }
}


/*************************************************************************
 * Function Name: GEPlayer::moveLeft
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEPlayer::moveLeft()
{
    if ((!_block) && (!_frozen)) {
	   _vector.setCoord(0, -10);
	   _engine->broadcastUpdate(this);
    }
}


/*************************************************************************
 * Function Name: GEPlayer::moveRight
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEPlayer::moveRight()
{
    if ((!_block) && (!_frozen)) {
	   _vector.setCoord(0, 10);
	   _engine->broadcastUpdate(this);
    }
}


/*************************************************************************
 * Function Name: GEPlayer::punch
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEPlayer::punch()
{
    attack(PK_ANIM_PUNCH, 5, PK_DIM_PADDLE_PUNCH_ADDED_WIDTH,
		 PK_DIM_PADDLE_PUNCH_ADDED_HEIGHT);
} 


/*************************************************************************
 * Function Name: GEPlayer::kick
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEPlayer::kick()
{
    attack(PK_ANIM_KICK, 5, PK_DIM_PADDLE_KICK_ADDED_WIDTH,
		 PK_DIM_PADDLE_KICK_ADDED_HEIGHT);
} 


/*************************************************************************
 * Function Name: GEPlayer::uppercut
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEPlayer::uppercut()
{
    attack(PK_ANIM_UPPERCUT, 10, PK_DIM_PADDLE_UPPERCUT_ADDED_WIDTH,
		 PK_DIM_PADDLE_UPPERCUT_ADDED_HEIGHT);
}


/*************************************************************************
 * Function Name: GEPlayer::lowercut
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEPlayer::lowercut()
{
    attack(PK_ANIM_UPPERCUT_DOWN, 10, PK_DIM_PADDLE_LOWERCUT_ADDED_WIDTH,
		 PK_DIM_PADDLE_LOWERCUT_ADDED_HEIGHT);
}

/*************************************************************************
 * Function Name: GEPlayer::sweep
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEPlayer::sweep()
{
     attack(PK_ANIM_SWEEP_KICK, 10, PK_DIM_PADDLE_SWEEP_ADDED_WIDTH,
		  PK_DIM_PADDLE_SWEEP_ADDED_HEIGHT);
}

/*************************************************************************
 * Function Name: GEPlayer::block
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEPlayer::block()
{
  
    if (!_frozen)
      {
	_engine->broadcastPlaySound (PK_SOUND_BLOCK);
    _block = 1;
    _engine->broadcastAnimateObject(_ID, PK_ANIM_PADDLE_BLOCK);
    stop();
      }
}

/*************************************************************************
 * Function Name: GEPlayer::unblock
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEPlayer::unblock()
{
  
 _block = 0;
    if (!_frozen)
      {
	_engine->broadcastPlaySound (PK_SOUND_UNBLOCK);
      _engine->broadcastAnimateObject(_ID, PK_ANIM_PADDLE_UNBLOCK);
      }
}


/*************************************************************************
 * Function Name: GEPlayer::stop
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEPlayer::stop()
{
    if (setVector(PKVector (0,0)))
    _engine->broadcastUpdate(this);
}

/*=======================================================================*/
/*=======================================================================*/
/*==                         Gettin' Busy                              ==*/
/*=======================================================================*/
/*=======================================================================*/


/*************************************************************************
 * Function Name: GEPlayer::update
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEPlayer::update()
{
 
    if (_frozen && ( (gethrtime() - _timer) > PK_INJURY_FREEZE_TIME))
	
      { 
       unfreeze();
      }
}
    
/*************************************************************************
 * Function Name: GEPlayer::getCaughtByNet
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEPlayer::getCaughtByNet()
{
   if (_block) return;
    cout << "Gotcha!" << endl;
    _frozen = 1;
    _timer = gethrtime();
    _engine->broadcastAnimateObject (_ID, PK_ANIM_PADDLE_CATCH);
   
}


/****************************************************************/
/*                                                              */
/* Function Name: GEPlayer::spin()                              */
/* Parameters:                                                  */
/* Returns:                                                     */
/* Effects:                                                     */
/*                                                              */
/****************************************************************/
void
GEPlayer::spin()

{

  if (_block) return;
  cout << "Spinning player!" << endl;
  _frozen = 1;
  _timer = gethrtime();
  _engine->broadcastAnimateObject (_ID, PK_ANIM_PADDLE_SPIN);

}


/*************************************************************************
 * Function Name: GEPlayer::injure
 * Parameters: int amount
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEPlayer::injure(int amount)
{
    // Check blocking and adjust amount appropriately.

    
    if (_block) 
	   subtractLife(amount/10);
    else
      {
	if (amount > 0)
	  {
	if (_typeID == PK_TYPE_JADE_1 || _typeID == PK_TYPE_JADE_2)
	  _engine->broadcastPlaySound (PK_SOUND_GIRL_HIT);
    else
      if (_typeID == PK_TYPE_LIU_KANG_1 || _typeID == PK_TYPE_LIU_KANG_2)
	_engine->broadcastPlaySound (PK_SOUND_KANG_HIT);
      else
	_engine->broadcastPlaySound (PK_SOUND_GUY_HIT);
	  }
	if (amount > 8)
	  {
	    GEExplosionProjectile *blood = new
	      GEExplosionProjectile (
				     1,
				    PK_TYPE_BLOOD,
				    0,
				    _engine->getProjList(),
				    0,
				    0,
				    _pos,
				    PKVector (0,0),
				    _engine,
				     800000000
				    );
	   _engine->addObject (blood);
	   _engine->broadcastAnimateObject (blood->getUniqueID(), PK_ANIM_EXPLODE);
	  }		     
	subtractLife(amount);
	   
      }
}

/*************************************************************************
 * Function Name: GEPlayer::subtractLife
 * Parameters: int amount
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEPlayer::subtractLife(int amount)
{
    // Don't bother checking blocking
    if (amount == 0) return;
    if (_frozen) unfreeze();
    if (_invisible) turnVisible();
    _life -= amount;
    if (_life < 0) _life = 0;
    cout<<"Player "<<_playerNum<<" injured.  Life now at "<<_life<<endl;
    _engine->changeGameStatus(_playerNum, _life);
    if (_life <=0) {
	   GERemoveObjectEvent* roevent = new
		  GERemoveObjectEvent(_engine, this);
	   _engine->addEvent(roevent);
	   if (_typeID == PK_TYPE_JADE_1 || _typeID == PK_TYPE_JADE_2)
	  _engine->broadcastPlaySound (PK_SOUND_GIRL_DEATH);
	   else
	     if (_typeID == PK_TYPE_LIU_KANG_1 || _typeID == PK_TYPE_LIU_KANG_2)
	       _engine->broadcastPlaySound (PK_SOUND_KANG_DEATH);
	     else
	       _engine->broadcastPlaySound (PK_SOUND_GUY_DEATH);
	   
    }
}

/*************************************************************************
 * Function Name: GEPlayer::attack
 * Parameters: PKAnimID animID, int addedWidth, int addedHeight
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEPlayer::attack(PKAnimID animID, int injury,
			  int addedWidth, int addedHeight)
{
    if ((!_block) && (!_frozen)) {
           _injury = injury;
	   _engine->broadcastAnimateObject(_ID, animID);
	   setWidthAdjust(addedWidth);
	   setHeightAdjust(addedHeight);
	   PKPhysicsInterface* physics = _engine->getPhysics();
	   GEContainer* oppteam = NULL;
	   if (_team == 1)
		  oppteam = _engine->getTeam2List();
	   else if (_team == 2)
		  oppteam = _engine->getTeam1List();
	   
	   RWTPtrDlistIterator<GEGameObject>* oppItr = (oppteam->iterator());
	   for (;(*oppItr)();) {
		  GEPlayer* opponent = (GEPlayer*) oppItr->key();
		  int intersected = physics->intersect(this, opponent);
		  if (intersected) {
			 opponent->injure(_injury);		 
		  } //end if intersected
	   } //end for loopcout<<"Player kicking"<<endl;
	   setWidthAdjust(0);
	   setHeightAdjust(0);
	   _injury = 0;
    } //end if !_block
} //end kick


/*************************************************************************
 * Function Name: GEPlayer::freeze
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEPlayer::freeze()
{
    if (_block) return;
    cout << "Player frozen!" << endl;
    _frozen = 1;
    _timer = gethrtime();
    _engine->broadcastAnimateObject (_ID, PK_ANIM_PADDLE_FREEZE);
    
}

/*************************************************************************
 * Function Name: GEPlayer::unfreeze
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEPlayer::unfreeze()
{
    _frozen = 0;
    cout << "Player unfrozen!" << endl;
    _engine->broadcastAnimateObject (_ID, PK_ANIM_NOT);
    //broadcast an unfreeze - check for invisibility
}

 
/****************************************************************/
/*                                                              */
/* Function Name:                                               */
/* Parameters:                                                  */
/* Returns:                                                     */
/* Effects:                                                     */
/*                                                              */
/****************************************************************/

void
GEPlayer::turnVisible()
{
  _invisible = 0;
  _engine->broadcastAnimateObject (_ID, PK_ANIM_VISIBLE);
  cout << "Player visible again" << endl;

   GEExplosionProjectile *explosion = new GEExplosionProjectile
	   (1, //default unique id
	    PK_TYPE_EXPLOSION,
	    0,
	    _engine->getProjList(),
	    PK_DIM_EXPLODE_WIDTH,
	    PK_DIM_EXPLODE_HEIGHT,
	    _pos,
	    PKVector (0, 0),
	    _engine);
  
    _engine->addObject (explosion);
    _engine->broadcastAnimateObject (explosion->getUniqueID(), PK_ANIM_EXPLODE);
}


/*=======================================================================*/
/*=======================================================================*/
/*==                        Accessors                                  ==*/
/*=======================================================================*/
/*=======================================================================*/


/*************************************************************************
 * Function Name: GEPlayer::getPlayerNum
 * Parameters: 
 * Returns: int
 * Effects: 
 *************************************************************************/
int
GEPlayer::getPlayerNum()
{
    return _playerNum;
}


/*************************************************************************
 * Function Name: GEPlayer::getTeam
 * Parameters: 
 * Returns: int
 * Effects: 
 *************************************************************************/
int
GEPlayer::getTeam()
{
    return _team;
}


/*************************************************************************
 * Function Name: GEPlayer::getLife
 * Parameters: 
 * Returns: int
 * Effects: 
 *************************************************************************/
int
GEPlayer::getLife()
{
    return _life;
}


