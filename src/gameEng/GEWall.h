/*************************************************************************/
/*    NAME: Elaine Chen                                                  */
/*    ACCT: eyc                                                          */
/*    FILE: GEWall.h                                                     */
/*    DATE: Mon Apr 28 13:08:03 1997                                     */
/*************************************************************************/


#ifndef GEWALL_HEADER
#define GEWALL_HEADER


enum GEWallSide {
    GEWALL_TOP = 0,
    GEWALL_RIGHT = 1,
    GEWALL_BOTTOM = 2,
    GEWALL_LEFT = 3
};
 

#include "GEGameObject.h"

class PKGameEngine;

class GEWall : public GEGameObject {
public:
    GEWall(PKID id,
		 PKTypeID type,
		 int team,
		 GEContainer* cont,
		 int width,
		 int height,
		 PKPoint pos,
		 PKVector vect,
		 PKGameEngine* engine);
    virtual ~GEWall();
    
    virtual void intersect(GEGameObject* obj);

    int getTeam() {return _team;}
 
protected:
    int _team; //which team the wall will injure
};

#endif
