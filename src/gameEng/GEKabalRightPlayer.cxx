/*************************************************************************
 *    NAME: Elaine Chen
 *    USER: eyc
 *    FILE: GEKabalRightPlayer.cxx
 *    DATE: Mon May  5  0:57:33 US/Eastern 1997
 *************************************************************************/
#include "GEKabalRightPlayer.h"
#include "PKGameEngine.h"
#include "GEProjectile.h"
#include <PKDimensions.h>
#include <PKInjuries.h>

/*************************************************************************
 * Function Name: GEKabalRightPlayer::GEKabalRightPlayer
 * Parameters: PKID id, int playerNum, PKPoint* pos, GEContainer* cont, PKGameEngine* engine
 * Effects: 
 *************************************************************************/

GEKabalRightPlayer::GEKabalRightPlayer(PKID id,
							    int playerNum,
							    PKPoint* pos,
							    GEContainer* cont,
							    PKGameEngine* engine)
    : GEPlayer(id, PK_TYPE_KABAL_2, playerNum, 2, pos, cont, engine)
{
  _flat_kicking = 0;
}


/*************************************************************************
 * Function Name: GEKabalRightPlayer::~GEKabalRightPlayer
 * Parameters: 
 * Effects: 
 *************************************************************************/

GEKabalRightPlayer::~GEKabalRightPlayer()
{
}


/*************************************************************************
 * Function Name: GEKabalRightPlayer::intersectWithWall
 * Parameters: GEGameObject* Player
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEKabalRightPlayer::intersectWithWall(GEGameObject* wall)
{
    GEPlayer::intersectWithWall(wall);
    
    if (_flat_kicking) {
	   _engine->broadcastAnimateObject(_ID,PK_ANIM_NOT);
	   _injury = 0;
	   _flat_kicking = 0;
    }
    GEPlayer::bounceBack (wall);
}

/*************************************************************************
 * Function Name: GEKabalRightPlayer::intersectWithPlayer
 * Parameters: GEGameObject* Player
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEKabalRightPlayer::intersectWithPlayer(GEGameObject* player)
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
 * Function Name: GEKabalRightPlayer::intersectWithProjectile
 * Parameters: GEGameObject* proj
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEKabalRightPlayer::intersectWithProjectile(GEGameObject* proj)
{
    GEPlayer::intersectWithProjectile(proj);
    
    if (_flat_kicking) {
	   _engine->broadcastAnimateObject(_ID,PK_ANIM_NOT);
	   _injury = 0;
	   _flat_kicking = 0;
    }
}

/*************************************************************************
 * Function Name: GEKabalRightPlayer::specialMove1
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEKabalRightPlayer::specialMove1()
{
    GEProjectile* kabalProj = new GEProjectile
           (-1, //default unique id
            PK_TYPE_KABAL_RIGHT_PROJECTILE,
            PK_INJURY_DEFAULT_PROJECTILE,
            _engine->getProjList(),
            PK_DIM_KABAL_PROJ_WIDTH,
            PK_DIM_KABAL_PROJ_HEIGHT,
            PKPoint ((-_width/2 - PK_DIM_KABAL_PROJ_WIDTH/2.0 - 4 + _pos[0]),
                           _pos[1]),
            PKVector (-PK_DIM_KABAL_PROJ_SPEED, 0),
            _engine);
  
    _engine->addObject (kabalProj);
}


/*************************************************************************
 * Function Name: GEKabalRightPlayer::specialMove2
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEKabalRightPlayer::specialMove2()
{
  _flat_kicking = 1;
    _injury = PK_INJURY_LK_FLAT_KICK; // Set the damage done by a flat kick.
    _engine->broadcastAnimateObject (_ID, PK_ANIM_SPECIAL_1);
    PKVector new_velocity = PKVector (-PK_DIM_LK_FLAT_SPEED, 0);
    setVector (new_velocity);
    _engine->broadcastUpdate (this);
}


/*************************************************************************
 * Function Name: GEKabalRightPlayer::specialMove3
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEKabalRightPlayer::specialMove3()
{
    //spikey wheel along opponents wall.
    GEProjectile* wheel = new GEProjectile
	   (-1, //default unique id
	    PK_TYPE_KABAL_RIGHT_WHEEL_PROJECTILE,
	    PK_INJURY_DEFAULT_PROJECTILE,
	    _engine->getProjList(),
	    PK_DIM_KABAL_WHEEL_WIDTH,
	    PK_DIM_KABAL_WHEEL_HEIGHT,
	    PKPoint((PK_DIM_WALL_LEFT_X + PK_DIM_KABAL_WHEEL_WIDTH/2 + 5),
			  (PK_DIM_WALL_BOTTOM_Y - PK_DIM_KABAL_WHEEL_HEIGHT/2 - 5)),
	    PKVector (0, (-1)*PK_DIM_KABAL_WHEEL_SPEED),
            _engine);

    cout <<"Engine adding object wheel" << endl;
    _engine->addObject (wheel);
    _engine->broadcastAnimateObject (wheel->getUniqueID(), PK_ANIM_SPECIAL_1);
}



/*************************************************************************
 * Function Name: GEKabalRightPlayer::moveUp
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEKabalRightPlayer::moveUp()
{
  if (!_flat_kicking)
    {
      GEPlayer::moveUp();
    }
}


/*************************************************************************
 * Function Name: GEKabalRightPlayer::moveDown
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEKabalRightPlayer::moveDown()
{
   if (!_flat_kicking)
    {
      GEPlayer::moveDown();
    }
}


/*************************************************************************
 * Function Name: GEKabalRightPlayer::moveLeft
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEKabalRightPlayer::moveLeft()
{
   if (!_flat_kicking)
    {
      GEPlayer::moveLeft();
    }
}


/*************************************************************************
 * Function Name: GEKabalRightPlayer::moveRight
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEKabalRightPlayer::moveRight()
{
   if ( !_flat_kicking)
    {
      GEPlayer::moveRight();
    }
}


/*************************************************************************
 * Function Name: GEKabalRightPlayer::stopVertical
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEKabalRightPlayer::stopVertical()
{
   if (!_flat_kicking)
    {
      GEPlayer::stopVertical();
    }
}


/*************************************************************************
 * Function Name: GEKabalRightPlayer::stopHorizontal
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEKabalRightPlayer::stopHorizontal()
{
   if (!_flat_kicking)
    {
      GEPlayer::stopHorizontal();
    }
}


/*************************************************************************
 * Function Name: GEKabalRightPlayer::punch
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEKabalRightPlayer::punch()
{
   if (!_flat_kicking)
    {
      GEPlayer::punch();
    }
}


/*************************************************************************
 * Function Name: GEKabalRightPlayer::kick
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEKabalRightPlayer::kick()
{
  if (!_flat_kicking)
    {
      GEPlayer::kick();
    }
}


/*************************************************************************
 * Function Name: GEKabalRightPlayer::uppercut
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEKabalRightPlayer::uppercut()
{
  if (!_flat_kicking)
    {
      GEPlayer::uppercut();
    }
}


/*************************************************************************
 * Function Name: GEKabalRightPlayer::lowercut
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEKabalRightPlayer::lowercut()
{
  if ( !_flat_kicking)
    {
      GEPlayer::lowercut();
    }
}


/*************************************************************************
 * Function Name: GEKabalRightPlayer::sweep
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEKabalRightPlayer::sweep()
{
  if (!_flat_kicking)
    {
      GEPlayer::sweep();
    }
}


/*************************************************************************
 * Function Name: GEKabalRightPlayer::block
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEKabalRightPlayer::block()
{
  if (!_flat_kicking)
    {
      GEPlayer::block();
    }
}


/*************************************************************************
 * Function Name: GEKabalRightPlayer::unblock
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEKabalRightPlayer::unblock()
{
  if ( !_flat_kicking)
    {
      GEPlayer::unblock();
    }
}
