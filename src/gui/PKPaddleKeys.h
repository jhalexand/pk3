/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: cs032082                                            */
/*    FILE: PKPaddleKeys.h                                      */
/*    ASGN:                                                     */
/*    DATE: Thu May  1 02:26:08 1997                            */
/****************************************************************/


#ifndef PKPADDLEKEYS_HEADER
#define PKPADDLEKEYS_HEADER
#include <PKKey.h>
#include <PKids.h>
#include <sys/time.h>
#include "PKClient.h"
class PKClientNetworkInterface;
class PKClientGraphicsInterface;

class PKPaddleKeys {
public:
  PKPaddleKeys(PKClientNetworkInterface* network, PKClient* client);
  ~PKPaddleKeys();
  virtual void keyPress(PKKey key);
  virtual void keyRelease(PKKey key);
  virtual void doDefaults(PKKey key);
protected:
  int keysdown[8];
  hrtime_t downtime[8];
  PKKey lastkeys[5];
  hrtime_t lasttime[5];
  PKClientNetworkInterface* network_;
  PKClient* client_;
};


//Keys Down:
//0 Down
//1 Up
//2 Right
//3 Left
//4 Punch
//5 Kick
//6 Block
#endif
