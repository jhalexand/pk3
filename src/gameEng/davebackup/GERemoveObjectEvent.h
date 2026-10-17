/*************************************************************************/
/*    NAME: Elaine Chen                                                  */
/*    ACCT: eyc                                                          */
/*    FILE: GERemoveObjectEvent.h                                        */
/*    DATE: Tue Apr 29 15:22:09 1997                                     */
/*************************************************************************/


#ifndef GEREMOVEOBJECTEVENT_HEADER
#define GEREMOVEOBJECTEVENT_HEADER

#include "GEEvent.h"

class GEGameObject;
class PKGameEngine;

class GERemoveObjectEvent : public GEEvent {
public:
    GERemoveObjectEvent(PKGameEngine* engine, GEGameObject* obj);
    virtual ~GERemoveObjectEvent();

    virtual void execute();

protected:
    GEGameObject* _obj;
};

#endif
