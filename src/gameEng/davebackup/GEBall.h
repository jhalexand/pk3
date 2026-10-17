/*************************************************************************/
/*    NAME: Elaine Chen                                                  */
/*    ACCT: eyc                                                          */
/*    FILE: GEBall.h                                                     */
/*    DATE: Sun Apr 27 17:14:19 1997                                     */
/*************************************************************************/


#ifndef GEBALL_HEADER
#define GEBALL_HEADER

#include "GEProjectile.h"

class GEContainer;
class PKGameEngine;

class GEBall : public GEProjectile {
public:
    GEBall(PKID id,
		 PKTypeID type,
		 GEContainer* cont,
		 PKPoint& pos,
		 PKVector& vect,
		 PKGameEngine* engine);
    virtual ~GEBall();

    virtual void intersect(GEGameObject* obj);
    virtual void intersectWithBall(GEGameObject* ball);
    virtual void intersectWithWall(GEGameObject* wall);
    virtual void intersectWithPlayer(GEGameObject* player);
    virtual void intersectWithProjectile(GEGameObject* obj);

};


#endif
