/*************************************************************************/
/*    NAME: Elaine Chen                                                  */
/*    ACCT: eyc                                                          */
/*    FILE: GECyraxHalfScreenBomb.h                                      */
/*    DATE: Sun May  4 21:35:27 1997                                     */
/*************************************************************************/


#ifndef GECYRAXHALFSCREENBOMB_HEADER
#define GECYRAXHALFSCREENBOMB_HEADER

#include "GEProjectile.h"
#include <PKids.h>

class GEContainer;
class PKGameEngine;

class GECyraxHalfScreenBomb : public GEProjectile {
public:
    GECyraxHalfScreenBomb(PKID id,
			PKTypeID type,
			GEContainer* cont,
			PKPoint& pos,
			PKVector& vect,
			PKGameEngine* engine);
    virtual ~GECyraxHalfScreenBomb();

    virtual void intersect(GEGameObject* obj);
    virtual void intersectWithPlayer(GEGameObject* player);
    virtual void update();

protected:
    hrtime_t _timer;
    double _xleftbarrier;
    double _xrightbarrier;
    
};

#endif
