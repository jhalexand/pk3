/*************************************************************************
 *    NAME: Elaine Chen
 *    USER: eyc
 *    FILE: GECyraxRightPlayer.cxx
 *    DATE: Sun May  4 23:41:17 US/Eastern 1997
 *************************************************************************/
#include "GECyraxRightPlayer.h"
#include "GEProjectile.h"
#include "GECyraxNet.h"
#include "GECyraxBomb.h"
#include "GECyraxHalfScreenBomb.h"
#include "PKGameEngine.h"
#include <PKDimensions.h>

/*************************************************************************
 * Function Name: GECyraxRightPlayer::GECyraxRightPlayer
 * Parameters: PKID id, int playerNum, PKPoint* pos, GEContainer* cont, PKGameEngine* engine
 * Effects: 
 *************************************************************************/

GECyraxRightPlayer::GECyraxRightPlayer(PKID id,
							    int playerNum,
							    PKPoint* pos,
							    GEContainer* cont,
							    PKGameEngine* engine)
    : GEPlayer(id, PK_TYPE_CYRAX_2, playerNum, 2, pos, cont, engine)
{
}


/*************************************************************************
 * Function Name: GECyraxRightPlayer::~GECyraxRightPlayer
 * Parameters: 
 * Effects: 
 *************************************************************************/

GECyraxRightPlayer::~GECyraxRightPlayer()
{
}


/*************************************************************************
 * Function Name: GECyraxRightPlayer::specialMove1
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GECyraxRightPlayer::specialMove1()
{
    GEProjectile* cyraxProj = new GECyraxNet
	   (-1, //default unique id
	    PK_TYPE_CYRAX_RIGHT_NET,
	    _engine->getProjList(),
	    PKPoint ((_width/2 + PK_DIM_CYRAX_NET_WIDTH/2.0 + 4 + _pos[0]),
			   _pos[1]),
	    PKVector (PK_DIM_CYRAX_NET_SPEED, 0),
	    _engine);
    _engine->addObject(cyraxProj);
}


/*************************************************************************
 * Function Name: GECyraxRightPlayer::specialMove2
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GECyraxRightPlayer::specialMove2()
{
    GEProjectile* cyraxProj = new GECyraxBomb
	   (-1, //default unique id
	    PK_TYPE_CYRAX_RIGHT_BOMB,
	    _engine->getProjList(),
	    PKPoint ((_width/2 + PK_DIM_CYRAX_BOMB_WIDTH/2.0 + 4 +
			    _pos[0]), _pos[1]),
	    PKVector (PK_DIM_CYRAX_BOMB_SPEED, 0),
	    _engine);
    _engine->addObject(cyraxProj);
}


/*************************************************************************
 * Function Name: GECyraxRightPlayer::specialMove3
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GECyraxRightPlayer::specialMove3()
{
    GEProjectile* cyraxProj = new GECyraxHalfScreenBomb
	   (-1, //default unique id
	    PK_TYPE_CYRAX_RIGHT_BOMB,
	    _engine->getProjList(),
	    PKPoint ((_width/2 + PK_DIM_CYRAX_BOMB_WIDTH/2.0 + 4 +
			    _pos[0]), _pos[1]),
	    PKVector (PK_DIM_CYRAX_BOMB_SPEED, 0),
	    _engine);
    _engine->addObject(cyraxProj);
}


