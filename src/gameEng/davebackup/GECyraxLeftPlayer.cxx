/*************************************************************************
 *    NAME: Elaine Chen
 *    USER: eyc
 *    FILE: GECyraxLeftPlayer.cxx
 *    DATE: Sun May  4 16:19:15 US/Eastern 1997
 *************************************************************************/
#include "GECyraxLeftPlayer.h"
#include "PKGameEngine.h"
#include <PKInjuries.h>
#include <PKDimensions.h>
#include "GECyraxNet.h"
#include "GECyraxBomb.h"
#include "GECyraxHalfScreenBomb.h"

/*************************************************************************
 * Function Name: GECyraxLeftPlayer::GECyraxLeftPlayer
 * Parameters: 
 * Effects: 
 *************************************************************************/

GECyraxLeftPlayer::GECyraxLeftPlayer(PKID id,
							  int playerNum,
							  PKPoint* pos,
							  GEContainer* cont,
							  PKGameEngine* engine)
    : GEPlayer(id, PK_TYPE_CYRAX_1, playerNum, 1, pos, cont, engine)
{
}


/*************************************************************************
 * Function Name: GECyraxLeftPlayer::~GECyraxLeftPlayer
 * Parameters: 
 * Effects: 
 *************************************************************************/

GECyraxLeftPlayer::~GECyraxLeftPlayer()
{
}


/*************************************************************************
 * Function Name: GECyraxLeftPlayer::specialMove1
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GECyraxLeftPlayer::specialMove1()
{
    GEProjectile* cyraxProj = new GECyraxNet
	   (-1, //default unique id
	    PK_TYPE_CYRAX_LEFT_NET,
	    _engine->getProjList(),
	    PKPoint ((_width/2 + PK_DIM_CYRAX_NET_WIDTH/2.0 + 4 + _pos[0]),
			   _pos[1]),
	    PKVector (PK_DIM_CYRAX_NET_SPEED, 0),
	    _engine);
    _engine->addObject(cyraxProj);
}


/*************************************************************************
 * Function Name: GECyraxLeftPlayer::specialMove2
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GECyraxLeftPlayer::specialMove2()
{
    GEProjectile* cyraxProj = new GECyraxBomb
	   (-1, //default unique id
	    PK_TYPE_CYRAX_LEFT_BOMB,
	    _engine->getProjList(),
	    PKPoint ((_width/2 + PK_DIM_CYRAX_BOMB_WIDTH/2.0 + 4 +
			    _pos[0]), _pos[1]),
	    PKVector (PK_DIM_CYRAX_BOMB_SPEED, 0),
	    _engine,
	    PK_TYPE_CYRAX_LEFT_NUKE);
    _engine->addObject(cyraxProj);
    _engine->broadcastAnimateObject (cyraxProj->getUniqueID(), PK_ANIM_BOMB_ROTATE);
    
}


/*************************************************************************
 * Function Name: GECyraxLeftPlayer::specialMove3
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GECyraxLeftPlayer::specialMove3()
{
  /*
    GEProjectile* cyraxProj = new GECyraxHalfScreenBomb
	   (-1, //default unique id
	    PK_TYPE_CYRAX_LEFT_BOMB,
	    _engine->getProjList(),
	    PKPoint ((_width/2 + PK_DIM_CYRAX_BOMB_WIDTH/2.0 + 4 +
			    _pos[0]), _pos[1]),
	    PKVector (PK_DIM_CYRAX_BOMB_SPEED, 0),
	    _engine);
    _engine->addObject(cyraxProj);*/
    
}


