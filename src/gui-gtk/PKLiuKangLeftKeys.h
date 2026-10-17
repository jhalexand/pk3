/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: cs032082                                            */
/*    FILE: PKLiuKangKeys.h                                     */
/*    ASGN:                                                     */
/*    DATE: Thu May  1 02:43:07 1997                            */
/****************************************************************/


#ifndef PKLIUKANGLEFTKEYS_HEADER
#define PKLIUKANGLEFTKEYS_HEADER
#include "PKPaddleKeys.h"
#include "PKClient.h"
#include <PKClientNetworkInterface.h>

class PKLiuKangLeftKeys : public PKPaddleKeys {
public:
  PKLiuKangLeftKeys(PKClientNetworkInterface* net, PKClient* client) : PKPaddleKeys(net, client) {}
  virtual void keyRelease(PKKey key) {
    PKPaddleKeys::keyRelease(key);
    if ((key == PK_KEY_PUNCH)&&(keysdown[PK_KEY_DOWN])) network_->sendAction(PK_ACTION_PADDLE_CUT_DOWN);
    else if ((key == PK_KEY_PUNCH)&&(keysdown[PK_KEY_UP])) network_->sendAction(PK_ACTION_PADDLE_CUT_UP);
    else if ((key == PK_KEY_KICK)&&(keysdown[PK_KEY_LEFT])) network_->sendAction(PK_ACTION_PADDLE_SWEEP); 
    else if ((key == PK_KEY_PUNCH)&&
	     (lastkeys[1] == PK_KEY_RIGHT)&&
	     ((lasttime[0]-lasttime[1]) < 1000000000)&&
	     (lastkeys[2] == PK_KEY_RIGHT)&&
	     ((lasttime[0]-lasttime[2]) < 1000000000))
      network_->sendAction(PK_ACTION_PADDLE_SPECIAL_1);
    else if ((key == PK_KEY_KICK)&&
	     (lastkeys[1] == PK_KEY_RIGHT)&&
	     ((lasttime[0]-lasttime[1]) < 1000000000)&&
	     (lastkeys[2] == PK_KEY_RIGHT)&&
	     ((lasttime[0]-lasttime[2]) < 1000000000))
      network_->sendAction(PK_ACTION_PADDLE_SPECIAL_3);
    else if ((key == PK_KEY_KICK) &&
	     ((lasttime[0] - downtime[PK_KEY_KICK]) > 1500000000))
      network_->sendAction(PK_ACTION_PADDLE_SPECIAL_2);
    else doDefaults(key);
  }
};
#endif
