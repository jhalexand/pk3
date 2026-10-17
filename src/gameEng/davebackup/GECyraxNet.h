/*************************************************************************/
/*    NAME: Elaine Chen                                                  */
/*    ACCT: eyc                                                          */
/*    FILE: GECyraxNet.h                                                 */
/*    DATE: Sun May  4 16:38:06 1997                                     */
/*************************************************************************/


#ifndef GECYRAXNET_HEADER
#define GECYRAXNET_HEADER

#include <PKids.h>
#include "GEProjectile.h"

class PKGameEngine;
class GEGameObject;

class GECyraxNet : public GEProjectile {
public:
    GECyraxNet(PKID id,
			PKTypeID type,
			GEContainer* cont,
			PKPoint& pos,
			PKVector& vect,
			PKGameEngine* engine);
    virtual ~GECyraxNet();
  
    virtual void intersectWithPlayer(GEGameObject* player);
    virtual void intersectWithWall(GEGameObject* wall);
    
protected:
 
};


#endif
