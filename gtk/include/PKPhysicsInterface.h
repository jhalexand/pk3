/*************************************************************************/
/*    NAME: Benoit Hudson                                                */
/*    ACCT: bh                                                           */
/*    FILE: PKPhysicsinterface.h                                         */
/*    DATE: Thu May  1 17:15:50 1997                                     */
/*************************************************************************/


#ifndef PKPHYSICSINTERFACE_HEADER
#define PKPHYSICSINTERFACE_HEADER

// Forward declarations:

class GEGameObject ;
class GEBall ;
class GEPlayer ;
class GEWall ;

class PKPhysicsInterface {
public:
    PKPhysicsInterface();
    virtual ~PKPhysicsInterface();

    virtual void update(GEGameObject* obj);
    virtual int  intersect(GEGameObject* obj1, GEGameObject* obj2);
    virtual void bounceWithWall(GEGameObject* ball, GEGameObject* wall);
    virtual void bounceWithPlayer (GEGameObject* ball, GEGameObject * player);

protected:

};

#endif
