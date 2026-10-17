/*************************************************************************
 *    NAME: David Akers
 *    USER: dla
 *    FILE: GELKLeftPlayer.cxx
 *    DATE: Fri May  2 21:31:20 US/Eastern 1997
 *************************************************************************/
#include "GELKLeftPlayer.h"
#include "PKGameEngine.h"
#include "GEProjectile.h"
#include <PKInjuries.h>
#include <PKDimensions.h>

/*************************************************************************
 * Function Name: GELKLeftPlayer::GELKLeftPlayer
 * Parameters: PKID id, PKTypeID type, int playerNum, int team, PKPoint* pos, GEContainer* cont, PKGameEngine* engine
 * Effects: 
 *************************************************************************/

GELKLeftPlayer::GELKLeftPlayer(PKID id,
						 int playerNum,
						 PKPoint* pos,
						 GEContainer* cont,
						 PKGameEngine* engine)
    : GEPlayer(id, PK_TYPE_LIU_KANG_1, playerNum, 1, pos, cont, engine),
	 _spin_kicking(0), _flat_kicking(0)
{
}


/*************************************************************************
 * Function Name: GELKLeftPlayer::~GELKLeftPlayer
 * Parameters: 
 * Effects: 
 *************************************************************************/

GELKLeftPlayer::~GELKLeftPlayer()
{
}


/*************************************************************************
 * Function Name: GELKLeftPlayer::intersectWithWall
 * Parameters: GEGameObject* wall
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GELKLeftPlayer::intersectWithWall(GEGameObject* wall)
{

    stop();
    _injury = 0;
    if (_spin_kicking || _flat_kicking) _engine->broadcastAnimateObject (_ID, PK_ANIM_NOT);
    _spin_kicking = _flat_kicking = 0;
    GEPlayer::bounceBack(wall);
  
}

/*************************************************************************
 * Function Name: GELKLeftPlayer::intersectWithWall
 * Parameters: GEGameObject* wall
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GELKLeftPlayer::intersectWithPlayer(GEGameObject* player)
{

    GEPlayer::intersectWithPlayer (player);
    _injury = 0;
    if (_spin_kicking || _flat_kicking) _engine->broadcastAnimateObject (_ID, PK_ANIM_NOT);
    _spin_kicking = _flat_kicking = 0;
    // Maybe set other player's velocity here.
  
}

/*************************************************************************
 * Function Name: GELKLeftPlayer::intersectWithWall
 * Parameters: GEGameObject* wall
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GELKLeftPlayer::intersectWithProjectile(GEGameObject* projectile)
{

    _injury = 0;
    if (_spin_kicking || _flat_kicking) _engine->broadcastAnimateObject (_ID, PK_ANIM_NOT);
    _spin_kicking = _flat_kicking = 0;
    GEPlayer::intersectWithProjectile (projectile);
  
}


/*************************************************************************
 * Function Name: GELKLeftPlayer::moveUp
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GELKLeftPlayer::moveUp()
{
  cout << "Player moving up!" << endl;
    if (!_spin_kicking && !_flat_kicking)
	   {
		  GEPlayer::moveUp();
	   }
}


/*************************************************************************
 * Function Name: GELKLeftPlayer::moveDown
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GELKLeftPlayer::moveDown()
{
    if (!_spin_kicking && !_flat_kicking)
	   {
		  GEPlayer::moveDown();
	   }
}


/*************************************************************************
 * Function Name: GELKLeftPlayer::moveLeft
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GELKLeftPlayer::moveLeft()
{
    if (!_spin_kicking && !_flat_kicking)
	   {
		  GEPlayer::moveLeft();
	   }
}


/*************************************************************************
 * Function Name: GELKLeftPlayer::moveRight
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GELKLeftPlayer::moveRight()
{
    if (!_spin_kicking && !_flat_kicking)
	   {
		  GEPlayer::moveRight();
	   }
}


/*************************************************************************
 * Function Name: GELKLeftPlayer::stopVertical
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GELKLeftPlayer::stopVertical()
{
    if (!_spin_kicking && !_flat_kicking)
	   {
		  GEPlayer::stopVertical();
	   }
}


/*************************************************************************
 * Function Name: GELKLeftPlayer::stopHorizontal
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GELKLeftPlayer::stopHorizontal()
{
    if (!_spin_kicking && !_flat_kicking)
	   {
		  GEPlayer::stopHorizontal();
	   }
}


/*************************************************************************
 * Function Name: GELKLeftPlayer::punch
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GELKLeftPlayer::punch()
{
    if (!_spin_kicking && !_flat_kicking)
	   {
		  GEPlayer::punch();
	   }
}


/*************************************************************************
 * Function Name: GELKLeftPlayer::kick
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GELKLeftPlayer::kick()
{
    if ((!_spin_kicking) && (!_flat_kicking))
	   {
		  GEPlayer::kick();
	   }
}


/*************************************************************************
 * Function Name: GELKLeftPlayer::uppercut
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GELKLeftPlayer::uppercut()
{
    if (!_spin_kicking && !_flat_kicking)
	   {
		  GEPlayer::uppercut();
	   }
}


/*************************************************************************
 * Function Name: GELKLeftPlayer::lowercut
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GELKLeftPlayer::lowercut()
{
    if (!_spin_kicking && !_flat_kicking)
	   {
		  GEPlayer::lowercut();
	   }
}


/*************************************************************************
 * Function Name: GELKLeftPlayer::sweep
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GELKLeftPlayer::sweep()
{
    if (!_spin_kicking && !_flat_kicking)
	   {
		  GEPlayer::sweep();
	   }
}


/*************************************************************************
 * Function Name: GELKLeftPlayer::block
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GELKLeftPlayer::block()
{
    if ((!_spin_kicking) && (!_flat_kicking))
	   {
		  GEPlayer::block();
	   }
}


/*************************************************************************
 * Function Name: GELKLeftPlayer::unblock
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GELKLeftPlayer::unblock()
{
    if ((!_spin_kicking) && (!_flat_kicking))
	   {
		  GEPlayer::unblock();
	   }
}


/*************************************************************************
 * Function Name: GELKLeftPlayer::specialMove1
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GELKLeftPlayer::specialMove1()
{

    GEProjectile *lkprojectile = new GEProjectile
	   (1, //default unique id
	    PK_TYPE_LK_LEFT_PROJECTILE,
	    PK_INJURY_DEFAULT_PROJECTILE,
	    _engine->getProjList(),
	    PK_DIM_LK_PROJ_WIDTH,
	    PK_DIM_LK_PROJ_HEIGHT,
	    PKPoint ((_width/2 + PK_DIM_LK_PROJ_WIDTH/2.0 + 4 + _pos[0]),
			   _pos[1]),
	    PKVector (PK_DIM_LK_PROJ_SPEED, 0),
	    _engine);
  
    _engine->addObject (lkprojectile);
    
}


/*************************************************************************
 * Function Name: GELKLeftPlayer::specialMove2
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GELKLeftPlayer::specialMove2()
{
    // Spinning kick.
     
    _spin_kicking = 1;
    _injury = PK_INJURY_LK_SPIN_KICK; // Set the damage done by a spin kick.
    _engine->broadcastAnimateObject (_ID, PK_ANIM_SPECIAL_1);
    PKVector new_velocity = PKVector (PK_DIM_LK_SPIN_SPEED, 0);
    setVector (new_velocity);
    _engine->broadcastUpdate(this);
  
}


/*************************************************************************
 * Function Name: GELKLeftPlayer::specialMove3
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GELKLeftPlayer::specialMove3()
{
    // Flat kick.

    _flat_kicking = 1;
    _injury = PK_INJURY_LK_FLAT_KICK; // Set the damage done by a flat kick.
    _engine->broadcastAnimateObject (_ID, PK_ANIM_SPECIAL_2);
    PKVector new_velocity = PKVector (PK_DIM_LK_FLAT_SPEED, 0);
    setVector (new_velocity);
    _engine->broadcastUpdate (this);
  
}


