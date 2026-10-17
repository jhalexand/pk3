/*************************************************************************
 *    NAME: Elaine Chen
 *    USER: eyc
 *    FILE: GEProjectile.C
 *    DATE: Sun Apr 27 17:50:04 US/Eastern 1997
 *************************************************************************/
#include "GEProjectile.h"
#include "GEExplosionProjectile.h"
#include "GEContainer.h"
#include "GERemoveObjectEvent.h"
#include "PKGameEngine.h"
#include <PKDimensions.h>

/*************************************************************************
 * Function Name: GEProjectile::GEProjectile
 * Parameters: PKID id, PKTypeID type, GEContainer* cont, PKPoint& pos, PKVector& vect
 * Effects: 
 *************************************************************************/

GEProjectile::GEProjectile(PKID id,
					  PKTypeID type,
					  int injury,
					  GEContainer* cont,
					  int width,
					  int height,
					  PKPoint& pos,
					  PKVector& vect,
					  PKGameEngine* engine)
    : GEGameObject(id, type, injury, cont, width, height, pos, vect, engine)
{
}


/*************************************************************************
 * Function Name: GEProjectile::~GEProjectile
 * Parameters: 
 * Effects: 
 *************************************************************************/

GEProjectile::~GEProjectile()
{
}


/*************************************************************************
 * Function Name: GEProjectile::intersect
 * Parameters: GEGameObject* obj
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEProjectile::intersect(GEGameObject* obj)
{
  obj->intersectWithProjectile(this);
}


/*************************************************************************
 * Function Name: GEProjectile::intersectWithBall
 * Parameters: GEGameObject* ball
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEProjectile::intersectWithBall(GEGameObject* ball)
{
  // Do nothing in this case
}


/*************************************************************************
 * Function Name: GEProjectile::intersectWithWall
 * Parameters: GEGameObject* wall
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEProjectile::intersectWithWall(GEGameObject* wall)
{
    GERemoveObjectEvent* roevent = new GERemoveObjectEvent(_engine, this);
    _engine->addEvent(roevent);
   explode();
}



/****************************************************************/
/*                                                              */
/* Function Name: GEProjectile::explode()                       */
/* Parameters:                                                  */
/* Returns:                                                     */
/* Effects:                                                     */
/*                                                              */
/****************************************************************/

void
GEProjectile::explode()
{
   PKPoint target;
    if (_vector[0] > 0) target = PKPoint ((_width/2 + _pos[0]), _pos[1]);
    else
      target = PKPoint ((-_width/2 + _pos[0]), _pos[1]);
    GEExplosionProjectile *explosion = new GEExplosionProjectile
	   (1, //default unique id
	    PK_TYPE_EXPLOSION,
	    0,
	    _engine->getProjList(),
	    PK_DIM_EXPLODE_WIDTH,
	    PK_DIM_EXPLODE_HEIGHT,
	    target,
	    PKVector (0, 0),
	    _engine);
  
    _engine->addObject (explosion);
    _engine->broadcastAnimateObject (explosion->getUniqueID(), PK_ANIM_EXPLODE);
}

/*************************************************************************
 * Function Name: GEProjectile::intersectWithPlayer
 * Parameters: GEGameObject* player
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEProjectile::intersectWithPlayer(GEGameObject* player)
{
  GERemoveObjectEvent* roevent = new GERemoveObjectEvent(_engine, this);
    _engine->addEvent(roevent);
    explode();
}


/*************************************************************************
 * Function Name: GEProjectile::intersectWithProjectile
 * Parameters: GEGameObject* obj
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEProjectile::intersectWithProjectile(GEGameObject* obj)
{
  // nothing, probably
}


