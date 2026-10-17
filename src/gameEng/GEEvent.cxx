/*************************************************************************
 *    NAME: Elaine Chen
 *    USER: eyc
 *    FILE: GEEvent.C
 *    DATE: Sun Apr 27 15:08:22 US/Eastern 1997
 *************************************************************************/
#include "GEEvent.h"
#include "PKGameEngine.h"
#include <iostream.h>

/*************************************************************************
 * Function Name: GEEvent::GEEvent
 * Parameters: 
 * Effects: 
 *************************************************************************/

GEEvent::GEEvent(PKGameEngine* engine)
    : _engine(engine)
{
}


/*************************************************************************
 * Function Name: GEEvent::~GEEvent
 * Parameters: 
 * Effects: 
 *************************************************************************/

GEEvent::~GEEvent()
{
}


/*************************************************************************
 * Function Name: GEEvent::execute
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEEvent::execute()
{
    cout<<"GEEvent.execute() should NOT EVER be called."<<endl;
}


