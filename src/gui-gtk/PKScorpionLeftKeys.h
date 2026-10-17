/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: cs032082                                            */
/*    FILE: PKScorpionLeftKeys.h                                */
/*    ASGN:                                                     */
/*    DATE: Sun May  4 23:51:54 1997                            */
/****************************************************************/


#ifndef PKSCORPIONLEFTKEYS_HEADER
#define PKSCORPIONLEFTKEYS_HEADER

#include "PKPaddleKeys.h"
#include <PKClientNetworkInterface.h>
#include <iostream.h>
#include "PKClient.h"

class PKScorpionLeftKeys : public PKPaddleKeys {
public:
  PKScorpionLeftKeys(PKClientNetworkInterface* net, PKClient* client) : PKPaddleKeys(net, client) {}
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
    else if ((key == PK_KEY_KICK)&&(keysdown[PK_KEY_LEFT])) {
      if (network_) network_->sendAction(PK_ACTION_PADDLE_SWEEP);
      else client_->updateAnimation(1, PK_ANIM_SWEEP_KICK);
      cout << "Sweep kick!" << endl;
    }
    else if ((key == PK_KEY_PUNCH)&&
	     (lastkeys[1] == PK_KEY_LEFT)&&
	     ((lasttime[0]-lasttime[1]) < 500000000)&&
	     (lastkeys[2] == PK_KEY_LEFT)&&
	     ((lasttime[0]-lasttime[2]) < 500000000)) {
      if (network_) network_->sendAction(PK_ACTION_PADDLE_SPECIAL_1);
      cout << "Special move 1!" << endl;
    }
    else if ((key == PK_KEY_PUNCH)&&
	     (lastkeys[1] == PK_KEY_LEFT)&&
	     ((lasttime[0]-lasttime[1]) < 500000000)&&
	     (lastkeys[2] == PK_KEY_DOWN)&&
	     ((lasttime[0]-lasttime[2]) < 500000000)) {
      if (network_) network_->sendAction(PK_ACTION_PADDLE_SPECIAL_2);
      else client_->updateAnimation(1, PK_ANIM_SPECIAL_2);
      cout << "Special Move 3!" << endl;
    }
    else doDefaults(key);
  }
};


#endif
