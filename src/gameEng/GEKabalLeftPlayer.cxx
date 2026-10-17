/*************************************************************************
 *    NAME: Elaine Chen
 *    USER: eyc
 *    FILE: GEKabalLeftPlayer.cxx
 *    DATE: Mon May  5  0:57:33 US/Eastern 1997
 *************************************************************************/
#include "GEKabalLeftPlayer.h"
#include "PKGameEngine.h"
#include "GEProjectile.h"
#include <PKDimensions.h>
#include <PKInjuries.h>

/*************************************************************************
 * Function Name: GEKabalLeftPlayer::GEKabalLeftPlayer
 * Parameters: PKID id, int playerNum, PKPoint* pos, GEContainer* cont, PKGameEngine* engine
 * Effects: 
 *************************************************************************/

GEKabalLeftPlayer::GEKabalLeftPlayer(PKID id,
							    int playerNum,
							    PKPoint* pos,
							    GEContainer* cont,
							    PKGameEngine* engine)
    : GEPlayer(id, PK_TYPE_KABAL_1, playerNum, 1, pos, cont, engine)
{
  _flat_kicking = 0;
}


/*************************************************************************
 * Function Name: GEKabalLeftPlayer::~GEKabalLeftPlayer
 * Parameters: 
 * Effects: 
 *************************************************************************/

GEKabalLeftPlayer::~GEKabalLeftPlayer()
{
}


/*************************************************************************
 * Function Name: GEKabalLeftPlayer::intersectWithWall
 * Parameters: GEGameObject* Player
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEKabalLeftPlayer::intersectWithWall(GEGameObject* wall)
{
    GEPlayer::intersectWithWall(wall);
    
    if (_flat_kicking) {
	   _engine->broadcastAnimateObject(_ID,PK_ANIM_NOT);
	   _injury = 0;
	   _flat_kicking = 0;
    }
    GEPlayer::bounceBack(wall);
}

/*************************************************************************
 * Function Name: GEKabalLeftPlayer::intersectWithPlayer
 * Parameters: GEGameObject* Player
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEKabalLeftPlayer::intersectWithPlayer(GEGameObject* player)
{
    if (_flat_kicking) {
      //_engine->broadcastAnimateObject((player->getUniqueID), PK_ANIM_PADDLE_SPIN);
      //((GEPlayer*) player)->injure(_injury);
	   ((GEPlayer*) player)->spin();
	   // Supposed to spin him AND injure him???
	   _injury = 0;
    }
}

/*************************************************************************
 * Function Name: GEKabalLeftPlayer::intersectWithProjectile
 * Parameters: GEGameObject* proj
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEKabalLeftPlayer::intersectWithProjectile(GEGameObject* proj)
{
    GEPlayer::intersectWithProjectile(proj);
    
    if (_flat_kicking) {
	   _engine->broadcastAnimateObject(_ID,PK_ANIM_NOT);
	   _injury = 0;
	   _flat_kicking = 0;
    }
}

/*************************************************************************
 * Function Name: GEKabalLeftPlayer::specialMove1
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEKabalLeftPlayer::specialMove1()
{
    GEProjectile* kabalProj = new GEProjectile
           (-1, //default unique id
            PK_TYPE_KABAL_LEFT_PROJECTILE,
            PK_INJURY_DEFAULT_PROJECTILE,
            _engine->getProjList(),
            PK_DIM_KABAL_PROJ_WIDTH,
            PK_DIM_KABAL_PROJ_HEIGHT,
            PKPoint ((+_width/2 + PK_DIM_KABAL_PROJ_WIDTH/2.0 + 4 + _pos[0]),
                           _pos[1]),
            PKVector (PK_DIM_KABAL_PROJ_SPEED, 0),
            _engine);
  
    _engine->addObject (kabalProj);
}


/*************************************************************************
 * Function Name: GEKabalLeftPlayer::specialMove2
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEKabalLeftPlayer::specialMove2()
{
  _flat_kicking = 1;
    _injury = PK_INJURY_LK_FLAT_KICK; // Set the damage done by a flat kick.
    _engine->broadcastAnimateObject (_ID, PK_ANIM_SPECIAL_1);
    PKVector new_velocity = PKVector (PK_DIM_LK_FLAT_SPEED, 0);
    setVector (new_velocity);
    _engine->broadcastUpdate (this);
}


/*************************************************************************
 * Function Name: GEKabalLeftPlayer::specialMove3
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEKabalLeftPlayer::specialMove3()
{
    //spikey wheel along opponents wall.
    GEProjectile* wheel = new GEProjectile
	   (-1, //default unique id
	    PK_TYPE_KABAL_LEFT_WHEEL_PROJECTILE,
	    PK_INJURY_DEFAULT_PROJECTILE,
	    _engine->getProjList(),
	    PK_DIM_KABAL_WHEEL_WIDTH,
	    PK_DIM_KABAL_WHEEL_HEIGHT,
	    PKPoint((PK_DIM_WALL_RIGHT_X - PK_DIM_KABAL_WHEEL_WIDTH/2 -5),
			  (PK_DIM_WALL_BOTTOM_Y - PK_DIM_KABAL_WHEEL_HEIGHT/2 - 5)),
	    PKVector (0, (-1)*PK_DIM_KABAL_WHEEL_SPEED),
            _engine);

    cout <<"Engine adding object wheel" << endl;
    _engine->addObject (wheel);
    _engine->broadcastAnimateObject (wheel->getUniqueID(), PK_ANIM_SPECIAL_1);
}



/*************************************************************************
 * Function Name: GEKabalLeftPlayer::moveUp
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEKabalLeftPlayer::moveUp()
{
  if (!_flat_kicking)
    {
      GEPlayer::moveUp();
    }
}


/*************************************************************************
 * Function Name: GEKabalLeftPlayer::moveDown
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEKabalLeftPlayer::moveDown()
{
   if (!_flat_kicking)
    {
      GEPlayer::moveDown();
    }
}


/*************************************************************************
 * Function Name: GEKabalLeftPlayer::moveLeft
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEKabalLeftPlayer::moveLeft()
{
   if (!_flat_kicking)
    {
      GEPlayer::moveLeft();
    }
}


/*************************************************************************
 * Function Name: GEKabalLeftPlayer::moveRight
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEKabalLeftPlayer::moveRight()
{
   if ( !_flat_kicking)
    {
      GEPlayer::moveRight();
    }
}


/*************************************************************************
 * Function Name: GEKabalLeftPlayer::stopVertical
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEKabalLeftPlayer::stopVertical()
{
   if (!_flat_kicking)
    {
      GEPlayer::stopVertical();
    }
}


/*************************************************************************
 * Function Name: GEKabalLeftPlayer::stopHorizontal
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEKabalLeftPlayer::stopHorizontal()
{
   if (!_flat_kicking)
    {
      GEPlayer::stopHorizontal();
    }
}


/*************************************************************************
 * Function Name: GEKabalLeftPlayer::punch
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEKabalLeftPlayer::punch()
{
   if (!_flat_kicking)
    {
      GEPlayer::punch();
    }
}


/*************************************************************************
 * Function Name: GEKabalLeftPlayer::kick
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEKabalLeftPlayer::kick()
{
  if (!_flat_kicking)
    {
      GEPlayer::kick();
    }
}


/*************************************************************************
 * Function Name: GEKabalLeftPlayer::uppercut
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEKabalLeftPlayer::uppercut()
{
  if (!_flat_kicking)
    {
      GEPlayer::uppercut();
    }
}


/*************************************************************************
 * Function Name: GEKabalLeftPlayer::lowercut
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEKabalLeftPlayer::lowercut()
{
  if ( !_flat_kicking)
    {
      GEPlayer::lowercut();
    }
}


/*************************************************************************
 * Function Name: GEKabalLeftPlayer::sweep
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEKabalLeftPlayer::sweep()
{
  if (!_flat_kicking)
    {
      GEPlayer::sweep();
    }
}


/*************************************************************************
 * Function Name: GEKabalLeftPlayer::block
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEKabalLeftPlayer::block()
{
  if (!_flat_kicking)
    {
      GEPlayer::block();
    }
}


/*************************************************************************
 * Function Name: GEKabalLeftPlayer::unblock
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEKabalLeftPlayer::unblock()
{
  if ( !_flat_kicking)
    {
      GEPlayer::unblock();
    }
}
