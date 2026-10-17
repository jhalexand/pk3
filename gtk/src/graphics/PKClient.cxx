/*************************************************************************
 *    NAME: David Akers
 *    USER: dla
 *    FILE: PKClient.cxx
 *    DATE: Wed Apr 23  0:32:40 US/Eastern 1997
 *************************************************************************/
#include "PKClient.h"

/*************************************************************************
 * Function Name: PKClient::PKClient
 * Parameters: 
 * Effects: 
 *************************************************************************/

PKClient::PKClient()
{

  object_[0] = PKObject (100, 100);
  object_[1] = PKObject (200, 200);
  object_[2] = PKObject (300, 300);
  object_[3] = PKObject (350, 350);
  object_[1].velocity_ = PKVector (0.0, 1);
  object_[2].velocity_ = PKVector (0.5, 1.2);
  object_[3].velocity_ = PKVector (1.2, 0.5);
  
}


/*************************************************************************
 * Function Name: PKClient::~PKClient
 * Parameters: 
 * Effects: 
 *************************************************************************/

PKClient::~PKClient()
{
}

void PKClient::handleKeyPress (PKKey key)
{
  if (key == PK_KEY_BLOCK) object_[0].setAnimID (PK_ANIM_PADDLE_FREEZE);
  if (key == PK_KEY_DOWN) object_[0].velocity_ = PKVector (0.0, 6.5);
  if (key == PK_KEY_RIGHT) object_[0].velocity_ = PKVector (6.5, 0.0);
  if (key == PK_KEY_LEFT) object_[0].velocity_ = PKVector (-6.5, 0.0);
  if (key == PK_KEY_UP) object_[0].velocity_ = PKVector (0.0, -6.5);
  if (key == PK_KEY_KICK) object_[0].setAnimID (PK_ANIM_KICK);
  if (key == PK_KEY_PUNCH) object_[0].setAnimID (PK_ANIM_PUNCH);
  if (key == PK_KEY_UPPERCUT) object_[0].setAnimID (PK_ANIM_UPPERCUT);
  if (key == PK_KEY_SWEEP_KICK) 
    {object_[0].setAnimID (PK_ANIM_SWEEP_KICK);
     cout << "Hi" << endl; }
}

void PKClient::handleKeyRelease (PKKey key)
{
switch (key)
{
case PK_KEY_DOWN:
case PK_KEY_RIGHT:
case PK_KEY_LEFT:
case PK_KEY_UP:
object_[0].velocity_ = PKVector (0, 0);
break;
case PK_KEY_BLOCK:
object_[0].setAnimID (PK_ANIM_PADDLE_UNFREEZE);
}
}
/*************************************************************************
 * Function Name: PKClient::getStateOfObject
 * Parameters: PKID id
 * Returns: PKObject *
 * Effects: 
 *************************************************************************/
PKObject *
PKClient::getStateOfObject(PKID id)
{
  object_[id].p_ = PKPoint (object_[id].p_[0]+object_[id].velocity_[0],
object_[id].p_[1]+object_[id].velocity_[1]);
  //cout << "F is : " << object_.p_[0] << endl;
  return &object_[id];
}


