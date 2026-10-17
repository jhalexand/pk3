/*************************************************************************
 *    NAME: Elaine Chen
 *    USER: eyc
 *    FILE: GECyraxNet.C
 *    DATE: Sun May  4 16:44:18 US/Eastern 1997
 *************************************************************************/
#include "GECyraxNet.h"
#include <PKDimensions.h>
#include <PKInjuries.h>
#include "PKGameEngine.h"
#include "GEGameObject.h"
#include "GEPlayer.h"
#include "GERemoveObjectEvent.h"

/*************************************************************************
 * Function Name: GECyraxNet::GECyraxNet
 * Parameters: PKID id, PKTypeID type, GEContainer* cont, PKPoint& pos, PKVector& vect, PKGameEngine* engine
 * Effects: 
 *************************************************************************/

GECyraxNet::GECyraxNet(PKID id,
				   PKTypeID type,
				   GEContainer* cont,
				   PKPoint& pos,
				   PKVector& vect,
				   PKGameEngine* engine)
    :  GEProjectile (id, type, PK_INJURY_NONE, cont,
				 PK_DIM_CYRAX_NET_WIDTH, PK_DIM_CYRAX_NET_HEIGHT,
				 pos, vect, engine)
{
}


/*************************************************************************
 * Function Name: GECyraxNet::~GECyraxNet
 * Parameters: 
 * Effects: 
 *************************************************************************/

GECyraxNet::~GECyraxNet()
{
}


/*************************************************************************
 * Function Name: GECyraxNet::intersectWithPlayer
 * Parameters: GEGameObject* player
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GECyraxNet::intersectWithPlayer(GEGameObject* player)
{
    ((GEPlayer*) player)->getCaughtByNet();
    GERemoveObjectEvent* roevent = new GERemoveObjectEvent(_engine, this); 
    _engine->addEvent(roevent);
}


/*************************************************************************
 * Function Name: GECyraxNet::intersectWithWall
 * Parameters: GEGameObject* wall
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GECyraxNet::intersectWithWall(GEGameObject* wall)
{
    GERemoveObjectEvent* roevent = new GERemoveObjectEvent(_engine, this);
    _engine->addEvent(roevent);
}


