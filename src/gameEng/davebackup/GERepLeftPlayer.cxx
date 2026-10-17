/*************************************************************************
 *    NAME: David Akers
 *    USER: dla
 *    FILE: GERepLeftPlayer.cxx
 *    DATE: Sun May  4 19:23:08 US/Eastern 1997
 *************************************************************************/
#include "GERepLeftPlayer.h"
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

GERepLeftPlayer::GERepLeftPlayer(PKID id,
							int playerNum,
							PKPoint* pos,
							GEContainer* cont,
							PKGameEngine* engine) :
  GEPlayer(id, PK_TYPE_REPTILE_1, playerNum, 1, pos, cont, engine)

{
  
}


/*************************************************************************
 * Function Name: GERepLeftPlayer::~GERepLeftPlayer
 * Parameters: 
 * Effects: 
 *************************************************************************/

GERepLeftPlayer::~GERepLeftPlayer()
{
}


/*************************************************************************
 * Function Name: GERepLeftPlayer::specialMove1
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GERepLeftPlayer::specialMove1()
{
  
GEProjectile *repprojectile = new GEProjectile
    (0,
     PK_TYPE_REPTILE_LEFT_PROJECTILE,
	PK_INJURY_DEFAULT_PROJECTILE,
     _engine->getProjList(),
     PK_DIM_REPTILE_PROJ_WIDTH,
     PK_DIM_REPTILE_PROJ_HEIGHT,
     PKPoint (_width/2 + PK_DIM_REPTILE_PROJ_WIDTH/2.0 + 4 + _pos[0] , _pos[1]),
     PKVector (PK_DIM_REPTILE_PROJ_SPEED, 0),
     _engine);
  
  _engine->addObject (repprojectile);
 
}


/*************************************************************************
 * Function Name: GERepLeftPlayer::specialMove2
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GERepLeftPlayer::specialMove2()
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
 * Function Name: GERepLeftPlayer::specialMove3
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GERepLeftPlayer::specialMove3()
{
}


