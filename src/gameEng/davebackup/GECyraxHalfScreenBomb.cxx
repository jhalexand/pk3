/*************************************************************************
 *    NAME: Elaine Chen
 *    USER: eyc
 *    FILE: GECyraxHalfScreenBomb.cxx
 *    DATE: Sun May  4 21:37:28 US/Eastern 1997
 *************************************************************************/
#include "GECyraxHalfScreenBomb.h"
#include "PKGameEngine.h"
#include "GERemoveObjectEvent.h"
#include <PKInjuries.h>
#include <PKDimensions.h>
#include <sys/time.h>

/*************************************************************************
 * Function Name: GECyraxHalfScreenBomb::GECyraxHalfScreenBomb
 * Parameters: PKID id, PKTypeID type, GEContainer* cont, PKPoint& pos, PKVector& vect, PKGameEngine* engine
 * Effects: 
 *************************************************************************/

GECyraxHalfScreenBomb::GECyraxHalfScreenBomb(PKID id,
									PKTypeID type,
									GEContainer* cont,
									PKPoint& pos,
									PKVector& vect,
									PKGameEngine* engine)
    : GEProjectile (id, type, PK_INJURY_DEFAULT_PROJECTILE, cont,
				PK_DIM_CYRAX_BOMB_WIDTH, PK_DIM_CYRAX_BOMB_HEIGHT,
				pos, vect, engine)

{
    _timer = gethrtime();
    _xleftbarrier = (PK_DIM_WALL_RIGHT_X - PK_DIM_WALL_LEFT_X) /2 +
	   PK_DIM_WALL_LEFT_X - 10;
    _xrightbarrier = (PK_DIM_WALL_RIGHT_X - PK_DIM_WALL_LEFT_X) /2 +
	   PK_DIM_WALL_LEFT_X + 10;
}


/*************************************************************************
 * Function Name: GECyraxHalfScreenBomb::~GECyraxHalfScreenBomb
 * Parameters: 
 * Effects: 
 *************************************************************************/

GECyraxHalfScreenBomb::~GECyraxHalfScreenBomb()
{
}



/*************************************************************************/
/* Function Name: GECyraxBomb::intersect                                 */
/* Parameters: GEGameObject* player                                      */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
GECyraxHalfScreenBomb::intersect(GEGameObject* obj)
{
    //bombs go through all objects and only stop at wall.
    //so we do not tell other object that they have intersected w/bomb
}

/*************************************************************************/
/* Function Name: GECyraxBomb::intersectWithPlayer                       */
/* Parameters: GEGameObject* player                                      */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
GECyraxHalfScreenBomb::intersectWithPlayer(GEGameObject* player)
{
    //do not do anything.  Just keep going until hits wall.
}


/*************************************************************************
 * Function Name: GECyraxHalfScreenBomb::update
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GECyraxHalfScreenBomb::update()
{
    if ((_pos[0] > _xleftbarrier) && (_pos[0] < _xrightbarrier)) {
	   _vector.setCoord(0,0);
	   _vector.setCoord(1,0);
	   if ((gethrtime() - _timer) > PK_INJURY_BOMB_WAIT_TIME) {
		  explode();
		  GERemoveObjectEvent* byebye = new GERemoveObjectEvent
			 (_engine, this);
		  _engine->addEvent(byebye);
	    }
	    
    }
}


