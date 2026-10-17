/*************************************************************************/
/*    NAME: Benoit Hudson                                                */
/*    ACCT: bh                                                           */
/*    FILE: PKPhysicsinterface.h                                         */
/*    DATE: Thu May  1 17:15:50 1997                                     */
/*************************************************************************/


#ifndef PKPHYSICSINTERFACE_HEADER
#define PKPHYSICSINTERFACE_HEADER

class GEGameObject ;

class PKPhysicsInterface {
public:
    PKPhysicsInterface();
    virtual ~PKPhysicsInterface();

    virtual void update(GEGameObject* obj);
    virtual int  intersect(GEGameObject* obj1, GEGameObject* obj2);
    virtual void bounce(GEGameObject* obj);

protected:

};

#endif
