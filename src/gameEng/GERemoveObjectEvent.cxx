/*************************************************************************
 *    NAME: Elaine Chen
 *    USER: eyc
 *    FILE: GERemoveObjectEvent.cxx
 *    DATE: Sat May  3 14:53:37 US/Eastern 1997
 *************************************************************************/
#include "GERemoveObjectEvent.h"
#include "PKGameEngine.h"
#include "GEGameObject.h"
#include "GEContainer.h"
#include <iostream.h>

/*************************************************************************
 * Function Name: GERemoveObjectEvent::GERemoveObjectEvent
 * Parameters: PKGameEngine* engine, GEGameObject* obj
 * Effects: 
 *************************************************************************/

GERemoveObjectEvent::GERemoveObjectEvent(PKGameEngine* engine,
								 GEGameObject* obj)
    : GEEvent(engine), _obj(obj)
{
}


/*************************************************************************
 * Function Name: GERemoveObjectEvent::~GERemoveObjectEvent
 * Parameters: 
 * Effects: 
 *************************************************************************/

GERemoveObjectEvent::~GERemoveObjectEvent()
{
}


/*************************************************************************
 * Function Name: GERemoveObjectEvent::execute
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GERemoveObjectEvent::execute()
{
    cout<<"executing GERemoveObjectEvent..."<<endl;
    _engine->removeObject(_obj->getUniqueID());
}


