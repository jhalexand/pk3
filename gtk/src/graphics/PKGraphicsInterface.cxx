/*************************************************************************
 *    NAME: David Akers
 *    USER: dla
 *    FILE: GREngineInterface.cxx
 *    DATE: Sun Apr 20 21:00:20 US/Eastern 1997
 *************************************************************************/
#include "PKGraphicsInterface.h"
#include "GREngine.h"

/*************************************************************************
 * Function Name: PKGraphicsInterface::PKGraphicsInterface
 * Parameters: PKClient *client, Widget parent, PKBackgroundID id, XtAppContext *app
 * Effects: 
 *************************************************************************/

PKGraphicsInterface::PKGraphicsInterface(PKClientInterface *client, Widget parent, PKBackgroundID id, XtAppContext *app, int numplayers, PKTypeID *playertypes)
{

implementation_ = new GREngine (client, parent, id, app, numplayers, playertypes);

}


/*************************************************************************
 * Function Name: PKGraphicsInterface::~PKGraphicsInterface
 * Parameters: 
 * Effects: 
 *************************************************************************/

PKGraphicsInterface::~PKGraphicsInterface()
{

  cout << "GRAPHICS: Destructor for pkgraphics" << endl;
  delete implementation_;

}


/*************************************************************************
 * Function Name: PKGraphicsInterface::addObject
 * Parameters: PKID id, PKTypeID grId, PKPoint pos
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKGraphicsInterface::addObject(PKID id, PKTypeID grId, PKPoint pos)
{
  cout << "GRAPHICS: Adding object with ID: " << id << ", TypeID: " << grId << endl;
  implementation_->addObject (id, grId, pos);

}


/*************************************************************************
 * Function Name: PKGraphicsInterface::removeObject
 * Parameters: PKID id
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKGraphicsInterface::removeObject(PKID id)
{

  cout << "GRAPHICS: Removing object with ID: " << id << endl;

  implementation_->removeObject (id);

}


/*************************************************************************
 * Function Name: PKGraphicsInterface::defineKeyMap
 * Parameters: PKKey key, char value
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKGraphicsInterface::defineKeyMap(PKKey key, KeySym keysym)
{

  implementation_->defineKeyMap (key, keysym);
  
}

void
PKGraphicsInterface::updateGameStatus (PKGameStatus *gamestatus)

{

  implementation_->updateGameStatus (gamestatus);

}
