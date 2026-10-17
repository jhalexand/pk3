/*************************************************************************
 *    NAME: Elaine Chen
 *    USER: eyc
 *    FILE: GEContainer.cxx
 *    DATE: Fri Apr 25 13:44:38 US/Eastern 1997
 *************************************************************************/
#include "GEContainer.h"


	  
/*************************************************************************
 * Function Name: GEContainer::GEContainer
 * Parameters: 
 * Effects: 
 *************************************************************************/

GEContainer::GEContainer()
{
    _list = new RWTPtrDlist<GEGameObject>();
}


/*************************************************************************
 * Function Name: GEContainer::~GEContainer
 * Parameters: 
 * Effects: 
 *************************************************************************/

GEContainer::~GEContainer()
{
}


/*************************************************************************
 * Function Name: GEContainer::addObject
 * Parameters: GEGameObject* newobj
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEContainer::addObject(GEGameObject* newobj)
{
    _list->append(newobj);
}


/*************************************************************************
 * Function Name: GEContainer::findObject
 * Parameters: GEGameObject* keyobj
 * Returns: GEGameObject*
 * Effects: 
 *************************************************************************/
GEGameObject*
GEContainer::findObject(GEGameObject* keyobj)
{
    return _list->find(keyobj);
}


/*************************************************************************
 * Function Name: GEContainer::removeObject
 * Parameters: GEGameObject* goneobj
 * Returns: void
 * Effects: 
 *************************************************************************/
GEGameObject*
GEContainer::removeObject(GEGameObject* goneobj)
{
    return _list->remove(goneobj);
}



/*************************************************************************
 * Function Name: GEContainer::iterator
 * Parameters: 
 * Returns: RWTPtrDlistIterator<GEGameObject>
 * Effects: 
 *************************************************************************/
RWTPtrDlistIterator<GEGameObject>*
GEContainer::iterator()
{
    RWTPtrDlistIterator<GEGameObject>* itr = new
	   RWTPtrDlistIterator<GEGameObject>(*_list);
    return itr;
}



/*************************************************************************
 * Function Name: GEContainer::isEmpty
 * Parameters: 
 * Returns: int
 * Effects: 
 *************************************************************************/
int
GEContainer::isEmpty()
{
    return _list->isEmpty();
}



/*************************************************************************
 * Function Name: GEContainer::numElements
 * Parameters: none
 * Returns: int
 * Effects: 
 *************************************************************************/
int
GEContainer::numElements()
{
    return _list->entries();
}

