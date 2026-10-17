/*************************************************************************
 *    NAME: Elaine Chen
 *    USER: eyc
 *    FILE: GEJadeLeftPlayer.cxx
 *    DATE: Sat May  3 21:44:03 US/Eastern 1997
 *************************************************************************/
#include "GEJadeLeftPlayer.h"
#include "PKGameEngine.h"
#include "GEProjectile.h"
#include <PKInjuries.h>
#include <PKDimensions.h>
#include <math.h>

/*************************************************************************
 * Function Name: GEJadeLeftPlayer::GEJadeLeftPlayer
 * Parameters: 
 * Effects: 
 *************************************************************************/

GEJadeLeftPlayer::GEJadeLeftPlayer(
				   PKID id,
				   int playerNum,
				   PKPoint* pos,
				   GEContainer* cont,
				   PKGameEngine* engine)
    : GEPlayer(id, PK_TYPE_JADE_1, playerNum, 1, pos, cont, engine)
{
  _projectile_invulnerability = 0;
}


/*************************************************************************
 * Function Name: GEJadeLeftPlayer::~GEJadeLeftPlayer
 * Parameters: 
 * Effects: 
 *************************************************************************/

GEJadeLeftPlayer::~GEJadeLeftPlayer()
{
}


/****************************************************************/
/*                                                              */
/* Function Name: GEJadeLeftPlayer::intersectWithProjectile     */
/* Parameters:                                                  */
/* Returns:                                                     */
/* Effects:                                                     */
/*                                                              */
/****************************************************************/

void
GEJadeLeftPlayer::intersectWithProjectile (GEGameObject *proj)
{
  
  if (_projectile_invulnerability) return;
  else
    GEPlayer::intersectWithProjectile (proj);
  
}

void
GEJadeLeftPlayer::update()
{
  if (_projectile_invulnerability && (_timer - gethrtime()) > 4000000000)
    {
      _projectile_invulnerability = 0;
      _engine->broadcastAnimateObject (_ID, PK_ANIM_NOT);
    }
  GEPlayer::update();
}
          


/*************************************************************************
 * Function Name: GEJadeLeftPlayer::specialMove1
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEJadeLeftPlayer::specialMove1()
{
    GEProjectile* jadeProj = new GEProjectile
	   (-1, //default unique id
	    PK_TYPE_JADE_LEFT_PROJECTILE,
	    PK_INJURY_DEFAULT_PROJECTILE,
	    _engine->getProjList(),
	    PK_DIM_JADE_PROJ_WIDTH,
	    PK_DIM_JADE_PROJ_HEIGHT,
	    PKPoint ((_width/2 + PK_DIM_JADE_PROJ_WIDTH/2.0 + 4 + _pos[0]),
			   _pos[1]),
	    PKVector (PK_DIM_JADE_PROJ_SPEED, 0),
	    _engine);
    _engine->addObject(jadeProj);
}


/*************************************************************************
 * Function Name: GEJadeLeftPlayer::specialMove2
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEJadeLeftPlayer::specialMove2()
{
  for (double theta = M_PI/6.0; theta > (-M_PI/6.0-0.2); theta -= M_PI/6.0)
    {
    GEProjectile* jadeProj = new GEProjectile
	   (-1, //default unique id
	    PK_TYPE_JADE_LEFT_PROJECTILE,
	    PK_INJURY_DEFAULT_PROJECTILE/3, // Do 1/3 the damage
	    _engine->getProjList(),
	    PK_DIM_JADE_PROJ_WIDTH,
	    PK_DIM_JADE_PROJ_HEIGHT,
	    PKPoint ((_width/2 + PK_DIM_JADE_PROJ_WIDTH/2.0 + 4 + _pos[0]),
			   _pos[1]),
	    PKVector ((PK_DIM_JADE_PROJ_SPEED*cos(theta)),
			    (PK_DIM_JADE_PROJ_SPEED*sin(theta))),
	    _engine);
    _engine->addObject(jadeProj);
    }
}


/*************************************************************************
 * Function Name: GEJadeLeftPlayer::specialMove3
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEJadeLeftPlayer::specialMove3()
{

  _projectile_invulnerability = 1;
  _invulnerability_timer = gethrtime();
  _engine->broadcastAnimateObject (_ID, PK_ANIM_SPECIAL_1);
  
}

void
GEJadeLeftPlayer::attack(PKAnimID animID, int injury,
			  int addedWidth, int addedHeight)
{

  _projectile_invulnerability = 0;
  GEPlayer::attack(animID, injury, addedWidth, addedHeight);
  
}

