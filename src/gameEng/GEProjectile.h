/*************************************************************************/
/*    NAME: Elaine Chen                                                  */
/*    ACCT: eyc                                                          */
/*    FILE: GEProjectile.h                                               */
/*    DATE: Sun Apr 27 17:11:29 1997                                     */
/*************************************************************************/


#ifndef GEPROJECTILE_HEADER
#define GEPROJECTILE_HEADER

#include "GEGameObject.h"

class GEContainer;
class PKGameEngine;

class GEProjectile : public GEGameObject {
public:
    GEProjectile(PKID id,
			  PKTypeID type,
			  int injury,
			  GEContainer* cont,
			  int width,
			  int height,
			  PKPoint& pos,
			  PKVector& vect,
			  PKGameEngine* engine);
    virtual ~GEProjectile();

  virtual void update() {}
    virtual void explode();
    virtual void intersect(GEGameObject* obj);
    virtual void intersectWithBall(GEGameObject* ball);
    virtual void intersectWithWall(GEGameObject* wall);
    virtual void intersectWithPlayer(GEGameObject* player);
    virtual void intersectWithProjectile(GEGameObject* obj);

protected:
    
};

#endif
