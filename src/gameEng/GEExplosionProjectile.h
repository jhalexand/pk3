/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: dla                                                 */
/*    FILE: GEExplosionProjectile.h                             */
/*    ASGN:                                                     */
/*    DATE: Sun May  4 06:14:38 1997                            */
/****************************************************************/


#ifndef GEEXPLOSIONPROJECTILE_HEADER
#define GEEXPLOSIONPROJECTILE_HEADER

#include <PKids.h>
#include "GEProjectile.h"

class GEExplosionProjectile : public GEProjectile
{
public:
  GEExplosionProjectile (PKID id,
					  PKTypeID type,
					  int injury,
					  GEContainer* cont,
					  int width,
					  int height,
					  PKPoint& pos,
					  PKVector& vect,
					  PKGameEngine* engine,
			 hrtime_t time = 250000000);
  ~GEExplosionProjectile();

  virtual void update();
  virtual void intersectWithPlayer (GEGameObject *player) {}
  virtual void intersectWithWall (GEGameObject *wall) {}

protected:
  hrtime_t _time_to_explode;
  hrtime_t _timer;
};
    

#endif
