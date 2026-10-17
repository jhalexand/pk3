/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: cs032082                                            */
/*    FILE: PKKabalRightKeys.h                                  */
/*    ASGN:                                                     */
/*    DATE: Sun May  4 20:17:27 1997                            */
/****************************************************************/


#ifndef PKKABALRIGHTKEYS_HEADER
#define PKKABALRIGHTKEYS_HEADER


#include "PKPaddleKeys.h"
#include <PKClientNetworkInterface.h>
#include <iostream.h>
#include "PKClient.h"

class PKKabalRightKeys : public PKPaddleKeys {
public:
  PKKabalRightKeys(PKClientNetworkInterface* net, PKClient* client) : PKPaddleKeys(net, client) {}
  virtual void keyPress(PKKey key) {
    keysdown[key] = 1;
    downtime[key] = gethrtime(); 

    if ((key == PK_KEY_BLOCK)&&
	(lastkeys[0] == PK_KEY_RIGHT)&&
	((downtime[key]-lasttime[0]) < 500000000)&&
	(lastkeys[1] == PK_KEY_RIGHT)&&
	((downtime[key]-lasttime[1]) < 500000000)&&
	(lastkeys[2] == PK_KEY_RIGHT)&&
	((downtime[key]-lasttime[2]) < 500000000)) {
      if (network_) network_->sendAction(PK_ACTION_PADDLE_SPECIAL_3);
      else client_->updateAnimation(1, PK_ANIM_SPECIAL_2);
      cout << "Special Move 3!" << endl;
    } 	   
    else if (key == PK_KEY_UP) {
    if (network_) network_->sendAction(PK_ACTION_PADDLE_UP);
    }
    else if (key == PK_KEY_DOWN) {
    if (network_)network_->sendAction(PK_ACTION_PADDLE_DOWN);
    }
    else if (key == PK_KEY_LEFT) {
      if (network_) network_->sendAction(PK_ACTION_PADDLE_LEFT);
    }	
    else if (key == PK_KEY_RIGHT) {
      if (network_) network_->sendAction(PK_ACTION_PADDLE_RIGHT);
    }
    else if (key == PK_KEY_BLOCK) {
      if (network_) network_->sendAction(PK_ACTION_PADDLE_BLOCK);
      else client_->updateAnimation(1, PK_ANIM_PADDLE_BLOCK); 
      cout << "Block!" << endl;
    }
    else if (key == PK_KEY_PUNCH) {
      if (network_) network_->sendAction(PK_ACTION_PADDLE_PUNCH);
      else client_->updateAnimation(1, PK_ANIM_PUNCH); 
      cout << "Punch!" << endl;
    }
    else if (key == PK_KEY_KICK) {
      if (network_) network_->sendAction(PK_ACTION_PADDLE_KICK);
      else client_->updateAnimation(1, PK_ANIM_KICK); 
      cout << "Kick!" << endl;
    }
  }

  virtual void keyRelease(PKKey key) {
    PKPaddleKeys::keyRelease(key);
    if ((key == PK_KEY_PUNCH)&&(keysdown[PK_KEY_DOWN])) {
      if (network_) network_->sendAction(PK_ACTION_PADDLE_CUT_DOWN);
      else client_->updateAnimation(1, PK_ANIM_UPPERCUT_DOWN);
      cout << "Uppercut Down!" << endl;
    }
    else if ((key == PK_KEY_PUNCH)&&(keysdown[PK_KEY_UP])) {
      if (network_) network_->sendAction(PK_ACTION_PADDLE_CUT_UP);
      else client_->updateAnimation(1, PK_ANIM_UPPERCUT);
      cout << "Uppercut up!" <<endl;
    }
    else if ((key == PK_KEY_KICK)&&(keysdown[PK_KEY_RIGHT])) {
      if (network_) network_->sendAction(PK_ACTION_PADDLE_SWEEP);
      else client_->updateAnimation(1, PK_ANIM_SWEEP_KICK);
      cout << "Sweep kick!" << endl;
    }
    else if ((key == PK_KEY_PUNCH)&&
	     (lastkeys[1] == PK_KEY_RIGHT)&&
	     ((lasttime[0]-lasttime[1]) < 500000000)&&
	     (lastkeys[2] == PK_KEY_RIGHT)&&
	     ((lasttime[0]-lasttime[2]) < 500000000)) {
      if (network_) network_->sendAction(PK_ACTION_PADDLE_SPECIAL_1);
      cout << "Special move 1!" << endl;
    }
    else if ((key == PK_KEY_KICK)&&
	     (lastkeys[1] == PK_KEY_LEFT)&&
	     ((lasttime[0]-lasttime[1]) < 500000000)&&
	     (lastkeys[2] == PK_KEY_RIGHT)&&
	     ((lasttime[0]-lasttime[2]) < 500000000)) {
      if (network_) network_->sendAction(PK_ACTION_PADDLE_SPECIAL_2);
      else client_->updateAnimation(1, PK_ANIM_SPECIAL_2);
      cout << "Special Move 2!" << endl;
    }
    else doDefaults(key);
  }
};

#endif
