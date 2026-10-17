/*************************************************************************
 *    NAME: David Akers
 *    USER: dla
 *    FILE: GERepLeftPlayer.cxx
 *    DATE: Sun May  4 19:23:08 US/Eastern 1997
 *************************************************************************/
#include "GERepRightPlayer.h"
#include <PKGameEngine.h>
#include <PKDimensions.h>
#include "GEProjectile.h"
#include "GEExplosionProjectile.h"
#include <PKInjuries.h>
#include <PKids.h>
#include <iostream.h>
#include <GEPlayer.h>

/*************************************************************************
 * Function Name: GERepLeftPlayer::GERepLeftPlayer
 * Parameters: PKID id, PKTypeID type, int playerNum, int team, PKPoint* pos, GEContainer* cont, PKGameEngine* engine
 * Effects: 
 *************************************************************************/

GERepRightPlayer::GERepRightPlayer(PKID id,
							int playerNum,
							PKPoint* pos,
							GEContainer* cont,
							PKGameEngine* engine) :
  GEPlayer(id, PK_TYPE_REPTILE_2, playerNum, 2, pos, cont, engine)

{
  
}


/*************************************************************************
 * Function Name: GERepRightPlayer::~GERepRightPlayer
 * Parameters: 
 * Effects: 
 *************************************************************************/

GERepRightPlayer::~GERepRightPlayer()
{
}


/*************************************************************************
 * Function Name: GERepRightPlayer::specialMove1
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GERepRightPlayer::specialMove1()
{
  
GEProjectile *repprojectile = new GEProjectile
    (0,
     PK_TYPE_REPTILE_RIGHT_PROJECTILE,
	PK_INJURY_DEFAULT_PROJECTILE,
     _engine->getProjList(),
     PK_DIM_REPTILE_PROJ_WIDTH,
     PK_DIM_REPTILE_PROJ_HEIGHT,
     PKPoint (-_width/2 - PK_DIM_REPTILE_PROJ_WIDTH/2.0 - 4 + _pos[0] , _pos[1]),
     PKVector (-PK_DIM_REPTILE_PROJ_SPEED, 0),
     _engine);
  
  _engine->addObject (repprojectile);
 
}


/*************************************************************************
 * Function Name: GERepRightPlayer::specialMove2
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GERepRightPlayer::specialMove2()
{

   cout << "Turning invisible" << endl;
  _invisible = 1;
  _engine->broadcastAnimateObject (_ID, PK_ANIM_INVISIBLE);

  
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
    _engine->broadcastPlaySound (PK_SOUND_REPTILE_INVIS);
    
}


/*************************************************************************
 * Function Name: GERepRightPlayer::specialMove3
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GERepRightPlayer::specialMove3()
{
}


