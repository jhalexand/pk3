/*************************************************************************
 *    NAME: Elaine Chen
 *    USER: eyc
 *    FILE: GECyraxBomb.cxx
 *    DATE: Sun May  4 17:04:58 US/Eastern 1997
 *************************************************************************/
#include "GECyraxBomb.h"
#include "GERemoveObjectEvent.h"
#include <PKDimensions.h>
#include <PKInjuries.h>
#include "PKGameEngine.h"
#include <sys/time.h>

/*************************************************************************/
/* Function Name: GECyraxBomb::GECyraxBomb                               */
/* Parameters: PKID id,                                                  */
/*             PKTypeID type,                                            */
/*             GEContainer* cont,                                        */
/*             PKPoint& pos,                                             */
/*             PKVector& vect,                                           */
/*             PKGameEngine* engine                                      */
/* Effects:                                                              */
/*************************************************************************/

GECyraxBomb::GECyraxBomb(PKID id,
					PKTypeID type,
					GEContainer* cont,
					PKPoint& pos,
					PKVector& vect,
					PKGameEngine* engine)
    : GEProjectile (id, type, PK_INJURY_DEFAULT_PROJECTILE, cont,
				PK_DIM_CYRAX_BOMB_WIDTH, PK_DIM_CYRAX_BOMB_HEIGHT,
				pos, vect, engine)
{
   _bomb_waiting = 0;
}


/*************************************************************************/
/* Function Name: GECyraxBomb::~GECyraxBomb                              */
/* Parameters:                                                           */
/* Effects:                                                              */
/*************************************************************************/

GECyraxBomb::~GECyraxBomb()
{
}



/*************************************************************************/
/* Function Name: GECyraxBomb::intersect                                 */
/* Parameters: GEGameObject* player                                      */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
GECyraxBomb::intersect(GEGameObject* obj)
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
GECyraxBomb::intersectWithPlayer(GEGameObject* player)
{
    //do not do anything.  Just keep going until hits wall.
}


/*************************************************************************/
/* Function Name: GECyraxBomb::intersectWithWall                         */
/* Parameters: GEGameObject* wall                                        */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
GECyraxBomb::intersectWithWall(GEGameObject* wall)
{
   if (!_bomb_waiting)
     {
    _vector.setCoord(0,0);
    _vector.setCoord(1,0);
    _engine->broadcastUpdate (this);
    _bomb_waiting = 1;
    _timer = gethrtime();
     }
   
}

void
GECyraxBomb::update()
{

  if (_bomb_waiting)
    {
 if ((gethrtime() - _timer) > PK_INJURY_BOMB_WAIT_TIME) {

   // Make the nuke! (left nuke)
	   GERemoveObjectEvent* byebye = new GERemoveObjectEvent(_engine, this);
	   _engine->addEvent(byebye);
    }
    }
}
