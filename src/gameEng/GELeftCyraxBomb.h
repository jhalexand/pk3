/*************************************************************************/
/*    NAME: Elaine Chen                                                  */
/*    ACCT: eyc                                                          */
/*    FILE: GECyraxBomb.h                                                */
/*    DATE: Sun May  4 17:04:11 1997                                     */
/*************************************************************************/


#ifndef GELEFTCYRAXBOMB_HEADER
#define GELEFTCYRAXBOMB_HEADER

#include <PKids.h>
#include "GEProjectile.h"
#include <VectorMath.h>

class GEContainer;
class PKGameEngine;
class GEGameObject;

class GECyraxBomb : public GEProjectile {
public:
    GECyraxBomb(PKID id,
			PKTypeID type,
			GEContainer* cont,
			PKPoint& pos,
			PKVector& vect,
			PKGameEngine* engine,
		        PKTypeID idToCreate
		);
    virtual ~GECyraxBomb();

    virtual void intersect(GEGameObject* obj);
    virtual void intersectWithPlayer(GEGameObject* player);
    virtual void intersectWithWall(GEGameObject* wall);
    virtual void update();
    
protected:
    hrtime_t _timer;
    int _bomb_waiting;
    
};



#endif
