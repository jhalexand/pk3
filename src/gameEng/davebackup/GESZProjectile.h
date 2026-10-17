/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: dla                                                 */
/*    FILE: GESZProjectile.h                                    */
/*    ASGN:                                                     */
/*    DATE: Sat May  3 18:51:17 1997                            */
/****************************************************************/


#include "GEProjectile.h"

#ifndef GESZPROJECTILE_HEADER
#define GESZPROJECTILE_HEADER

class GESZProjectile : public GEProjectile {
public:
    GESZProjectile(PKID id,
			  PKTypeID type,
			  int injury,
			  GEContainer* cont,
			  int width,
			  int height,
			  PKPoint& pos,
			  PKVector& vect,
			  PKGameEngine* engine,
		   int seeking = 0,
		   int teamToAttack = 0);
    virtual ~GESZProjectile();
  
  virtual void intersectWithPlayer(GEGameObject* player);
  virtual void intersectWithWall (GEGameObject * wall);
  virtual void update();

protected:
  int _seeking;
  int _team_to_attack;
  hrtime_t _timer;

};
    

#endif
