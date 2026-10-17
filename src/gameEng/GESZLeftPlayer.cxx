/*************************************************************************
 *    NAME: David Akers
 *    USER: dla
 *    FILE: GESZLeftPlayer.cxx
 *    DATE: Sat May  3  2:10:09 US/Eastern 1997
 *************************************************************************/
#include "GESZLeftPlayer.h"
#include "GESZProjectile.h"
#include <PKDimensions.h>
#include "PKGameEngine.h"

/*************************************************************************
 * Function Name: GESZLeftPlayer::GESZLeftPlayer
 * Parameters: PKID id, PKTypeID type, int playerNum, int team, PKPoint* pos, GEContainer* cont, PKGameEngine* engine
 * Effects: 
 *************************************************************************/

GESZLeftPlayer::GESZLeftPlayer(PKID id,
						 int playerNum,
						 PKPoint* pos,
						 GEContainer* cont,
						 PKGameEngine* engine)
    : GEPlayer(id, PK_TYPE_SUB_ZERO_1, playerNum, 1, pos, cont, engine)
{
  
}


/*************************************************************************
 * Function Name: GESZLeftPlayer::~GESZLeftPlayer
 * Parameters: 
 * Effects: 
 *************************************************************************/

GESZLeftPlayer::~GESZLeftPlayer()
{
}


/*************************************************************************
 * Function Name: GESZLeftPlayer::specialMove1
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GESZLeftPlayer::specialMove1()
{
  
    GESZProjectile *szprojectile = new GESZProjectile
	   (1, //default unique id
	    PK_TYPE_SZ_LEFT_PROJECTILE,
	    1,  // Do a LITTLE damage
	    _engine->getProjList(),
	    PK_DIM_SZ_PROJ_WIDTH,
	    PK_DIM_SZ_PROJ_HEIGHT,
	    PKPoint ((_width/2 + PK_DIM_SZ_PROJ_WIDTH/2.0 + 4 + _pos[0]),
			   _pos[1]),
	    PKVector (PK_DIM_SZ_PROJ_SPEED, 0),
	    _engine);
  
    _engine->addObject (szprojectile);
}
  // Make sub zero projectile here


/*************************************************************************
 * Function Name: GESZLeftPlayer::specialMove2
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GESZLeftPlayer::specialMove2()
{
  // Make strange moving sub-zero projectile here
  GESZProjectile *seekingprojectile = new GESZProjectile
    (
     1,
     PK_TYPE_SZ_LEFT_PROJECTILE,
     1,
     _engine->getProjList(),
     PK_DIM_SZ_PROJ_WIDTH,
     PK_DIM_SZ_PROJ_HEIGHT,
     PKPoint ((_width/2 + PK_DIM_SZ_PROJ_WIDTH/2.0 + 4 + _pos[0]),
	      _pos[1]),
     PKVector (PK_DIM_SZ_PROJ_SPEED/2, 0),
     _engine, 1, 3-_team); // Seek!!
  _engine->addObject (seekingprojectile);
  
}


/*************************************************************************
 * Function Name: GESZLeftPlayer::specialMove3
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GESZLeftPlayer::specialMove3()
{
  // Make shadow image of self here.
}


