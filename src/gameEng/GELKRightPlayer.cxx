/*************************************************************************
 *    NAME: David Akers
 *    USER: dla
 *    FILE: GELKRightPlayer.cxx
 *    DATE: Fri May  2 21:31:20 US/Eastern 1997
 *************************************************************************/
#include "GELKRightPlayer.h"
#include "PKGameEngine.h"
#include "GEProjectile.h"
#include <PKInjuries.h>
#include <PKDimensions.h>

/*************************************************************************
 * Function Name: GELKRightPlayer::GELKRightPlayer
 * Parameters: PKID id, PKTypeID type, int playerNum, int team, PKPoint* pos, GEContainer* cont, PKGameEngine* engine
 * Effects: 
 *************************************************************************/

GELKRightPlayer::GELKRightPlayer(PKID id,
						   int playerNum,
						   PKPoint* pos,
						   GEContainer* cont,
						   PKGameEngine* engine)
  : GEPlayer(id, PK_TYPE_LIU_KANG_2, playerNum, 2, pos, cont, engine)
{
  _spin_kicking = 0;
  _flat_kicking = 0;
}


/*************************************************************************
 * Function Name: GELKRightPlayer::~GELKRightPlayer
 * Parameters: 
 * Effects: 
 *************************************************************************/

GELKRightPlayer::~GELKRightPlayer()
{
}


/*************************************************************************
 * Function Name: GELKRightPlayer::intersectWithWall
 * Parameters: GEGameObject* wall
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GELKRightPlayer::intersectWithWall(GEGameObject* wall)
{

  stop();
  _injury = 0;
  if (_spin_kicking || _flat_kicking) _engine->broadcastAnimateObject (_ID, PK_ANIM_NOT);
  _spin_kicking = _flat_kicking = 0;
  GEPlayer::bounceBack(wall);
  
}

/*************************************************************************
 * Function Name: GELKRightPlayer::intersectWithWall
 * Parameters: GEGameObject* wall
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GELKRightPlayer::intersectWithPlayer(GEGameObject* player)
{

  GEPlayer::intersectWithPlayer (player);
  _injury = 0;
  _engine->broadcastAnimateObject (_ID, PK_ANIM_NOT);
  _spin_kicking = _flat_kicking = 0;
  // Maybe set other player's velocity here.
  
}

/*************************************************************************
 * Function Name: GELKRightPlayer::intersectWithWall
 * Parameters: GEGameObject* wall
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GELKRightPlayer::intersectWithProjectile(GEGameObject* projectile)
{

  _injury = 0;
  if (_spin_kicking || _flat_kicking) _engine->broadcastAnimateObject (_ID, PK_ANIM_NOT);
  _spin_kicking = _flat_kicking = 0;
  GEPlayer::intersectWithProjectile (projectile);
  
}


/*************************************************************************
 * Function Name: GELKRightPlayer::moveUp
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GELKRightPlayer::moveUp()
{
  if (!_spin_kicking && !_flat_kicking)
    {
      GEPlayer::moveUp();
    }
}


/*************************************************************************
 * Function Name: GELKRightPlayer::moveDown
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GELKRightPlayer::moveDown()
{
   if (!_spin_kicking && !_flat_kicking)
    {
      GEPlayer::moveDown();
    }
}


/*************************************************************************
 * Function Name: GELKRightPlayer::moveLeft
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GELKRightPlayer::moveLeft()
{
   if (!_spin_kicking && !_flat_kicking)
    {
      GEPlayer::moveLeft();
    }
}


/*************************************************************************
 * Function Name: GELKRightPlayer::moveRight
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GELKRightPlayer::moveRight()
{
   if (!_spin_kicking && !_flat_kicking)
    {
      GEPlayer::moveRight();
    }
}


/*************************************************************************
 * Function Name: GELKRightPlayer::stopVertical
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GELKRightPlayer::stopVertical()
{
   if (!_spin_kicking && !_flat_kicking)
    {
      GEPlayer::stopVertical();
    }
}


/*************************************************************************
 * Function Name: GELKRightPlayer::stopHorizontal
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GELKRightPlayer::stopHorizontal()
{
   if (!_spin_kicking && !_flat_kicking)
    {
      GEPlayer::stopHorizontal();
    }
}


/*************************************************************************
 * Function Name: GELKRightPlayer::punch
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GELKRightPlayer::punch()
{
   if (!_spin_kicking && !_flat_kicking)
    {
      GEPlayer::punch();
    }
}


/*************************************************************************
 * Function Name: GELKRightPlayer::kick
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GELKRightPlayer::kick()
{
  if (!_spin_kicking && !_flat_kicking)
    {
      GEPlayer::kick();
    }
}


/*************************************************************************
 * Function Name: GELKRightPlayer::uppercut
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GELKRightPlayer::uppercut()
{
  if (!_spin_kicking && !_flat_kicking)
    {
      GEPlayer::uppercut();
    }
}


/*************************************************************************
 * Function Name: GELKRightPlayer::lowercut
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GELKRightPlayer::lowercut()
{
  if (!_spin_kicking && !_flat_kicking)
    {
      GEPlayer::lowercut();
    }
}


/*************************************************************************
 * Function Name: GELKRightPlayer::sweep
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GELKRightPlayer::sweep()
{
  if (!_spin_kicking && !_flat_kicking)
    {
      GEPlayer::sweep();
    }
}


/*************************************************************************
 * Function Name: GELKRightPlayer::block
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GELKRightPlayer::block()
{
  if (!_spin_kicking && !_flat_kicking)
    {
      GEPlayer::block();
    }
}


/*************************************************************************
 * Function Name: GELKRightPlayer::unblock
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GELKRightPlayer::unblock()
{
  if (!_spin_kicking && !_flat_kicking)
    {
      GEPlayer::unblock();
    }
}


/*************************************************************************
 * Function Name: GELKRightPlayer::specialMove1
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GELKRightPlayer::specialMove1()
{
  GEProjectile *lkprojectile = new GEProjectile
    (0,
     PK_TYPE_LK_RIGHT_PROJECTILE,
	PK_INJURY_DEFAULT_PROJECTILE,
     _engine->getProjList(),
     PK_DIM_LK_PROJ_WIDTH,
     PK_DIM_LK_PROJ_HEIGHT,
     PKPoint (-_width/2 - PK_DIM_LK_PROJ_WIDTH/2.0 - 4 + _pos[0] , _pos[1]),
     PKVector (-PK_DIM_LK_PROJ_SPEED, 0),
     _engine);
  
  _engine->addObject (lkprojectile);
}


/*************************************************************************
 * Function Name: GELKRightPlayer::specialMove2
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GELKRightPlayer::specialMove2()
{
  // Spinning kick.

  _spin_kicking = 1;
  _injury = PK_INJURY_LK_SPIN_KICK; // Set the damage done by a spin kick.
  _engine->broadcastAnimateObject (_ID, PK_ANIM_SPECIAL_1);
  PKVector new_velocity = PKVector (-PK_DIM_LK_SPIN_SPEED, 0);
  setVector (new_velocity);
  _engine->broadcastUpdate(this);

 
  
}


/*************************************************************************
 * Function Name: GELKRightPlayer::specialMove3
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GELKRightPlayer::specialMove3()
{
  // Flat kick.

  _flat_kicking = 1;
  _injury = PK_INJURY_LK_FLAT_KICK; // Set the damage done by a flat kick.
  _engine->broadcastAnimateObject (_ID, PK_ANIM_SPECIAL_2);
  PKVector new_velocity = PKVector (-PK_DIM_LK_FLAT_SPEED, 0);
  setVector (new_velocity);
  _engine->broadcastUpdate (this);
  
}


