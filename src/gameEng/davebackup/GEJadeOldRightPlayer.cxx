/*************************************************************************
 *    NAME: Elaine Chen
 *    USER: eyc
 *    FILE: GEJadeRightPlayer.cxx
 *    DATE: Sat May  3 21:44:03 US/Eastern 1997
 *************************************************************************/
#include "GEJadeRightPlayer.h"
#include "PKGameEngine.h"
#include "GEProjectile.h"
#include <PKInjuries.h>
#include <PKDimensions.h>
#include <math.h>

/*************************************************************************
 * Function Name: GEJadeRightPlayer::GEJadeRightPlayer
 * Parameters: 
 * Effects: 
 *************************************************************************/

GEJadeRightPlayer::GEJadeRightPlayer(PKID id,
				   int playerNum,
				   PKPoint* pos,
				   GEContainer* cont,
				   PKGameEngine* engine)
    : GEPlayer(id, PK_TYPE_JADE_2, playerNum, 1, pos, cont, engine)
{
}


/*************************************************************************
 * Function Name: GEJadeRightPlayer::~GEJadeRightPlayer
 * Parameters: 
 * Effects: 
 *************************************************************************/

GEJadeRightPlayer::~GEJadeRightPlayer()
{
}


/*************************************************************************
 * Function Name: GEJadeRightPlayer::specialMove1
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEJadeRightPlayer::specialMove1()
{
    GEProjectile* jadeProj = new GEProjectile
	   (-1, //default unique id
	    PK_TYPE_JADE_RIGHT_PROJECTILE,
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
 * Function Name: GEJadeRightPlayer::specialMove2
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEJadeRightPlayer::specialMove2()
{
    GEProjectile* jadeProj = new GEProjectile
	   (-1, //default unique id
	    PK_TYPE_JADE_RIGHT_PROJECTILE,
	    PK_INJURY_DEFAULT_PROJECTILE,
	    _engine->getProjList(),
	    PK_DIM_JADE_PROJ_WIDTH,
	    PK_DIM_JADE_PROJ_HEIGHT,
	    PKPoint ((_width/2 + PK_DIM_JADE_PROJ_WIDTH/2.0 + 4 + _pos[0]),
			   _pos[1]),
	    PKVector ((-1)*(PK_DIM_JADE_PROJ_SPEED*cos(M_PI/6.0)),
			    (PK_DIM_JADE_PROJ_SPEED*sin(M_PI/6.0))),
	    _engine);
    _engine->addObject(jadeProj);
}


/*************************************************************************
 * Function Name: GEJadeRightPlayer::specialMove3
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEJadeRightPlayer::specialMove3()
{
    GEProjectile* jadeProj = new GEProjectile
	   (-1, //default unique id
	    PK_TYPE_JADE_RIGHT_PROJECTILE,
	    PK_INJURY_DEFAULT_PROJECTILE,
	    _engine->getProjList(),
	    PK_DIM_JADE_PROJ_WIDTH,
	    PK_DIM_JADE_PROJ_HEIGHT,
	    PKPoint ((_width/2 + PK_DIM_JADE_PROJ_WIDTH/2.0 + 4 + _pos[0]),
			   _pos[1]),
	    PKVector ((-1)*(PK_DIM_JADE_PROJ_SPEED*cos(M_PI/6.0)),
			    ((-1)*PK_DIM_JADE_PROJ_SPEED*sin(M_PI/6.0))),
	    _engine);
    _engine->addObject(jadeProj);
}


