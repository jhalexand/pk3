/*************************************************************************/
/*    NAME: Elaine Chen                                                  */
/*    ACCT: eyc                                                          */
/*    FILE: GEContainer.h                                                */
/*    DATE: Fri Apr 25 13:27:47 1997                                     */
/*************************************************************************/


#ifndef GECONTAINER_HEADER
#define GECONTAINER_HEADER

#include <rw/tpdlist.h> 
#include "GEGameObject.h"

class GEContainer {
public:
    GEContainer();
    virtual ~GEContainer();

    virtual void addObject(GEGameObject* newobj);
    virtual GEGameObject* findObject(GEGameObject* keyobj);
    virtual GEGameObject* removeObject(GEGameObject* goneobj);
    virtual RWTPtrDlistIterator<GEGameObject>* iterator();
    GEGameObject *first () { return _list->first(); }
    int isEmpty();
    int numElements();
    
protected:
    RWTPtrDlist<GEGameObject>* _list;
    
};

#endif
