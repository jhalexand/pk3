/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: cs032082                                            */
/*    FILE: PKPaddleKeys.cxx                                    */
/*    ASGN:                                                     */
/*    DATE: Thu May  1 18:46:54 1997                            */
/****************************************************************/



#include "PKPaddleKeys.h"
#include <PKKey.h>
#include <PKClientNetworkInterface.h>
#include <PKids.h>
#include <sys/time.h>
#include <iostream.h>

PKPaddleKeys::PKPaddleKeys(PKClientNetworkInterface* network, PKClient* client) {
  network_ = network;
  client_ = client;
  for (int i = 0; i < 8;i++) {
    keysdown[i] = 0;
  }
   for (int j = 0; j < 8;j++) {
    downtime[j] = 0;
  }
  for (int l = 0; l < 5;l++) {
    lasttime[l] = 0;
  }
  for (int k = 0; k < 5; k++) {
	  lastkeys[k] = PK_KEY_UNDEFINED;
  }
}  
PKPaddleKeys::~PKPaddleKeys() {
}
void
PKPaddleKeys::keyPress(PKKey key) {
  keysdown[key] = 1;
  downtime[key] = gethrtime();
  if (key == PK_KEY_UP) {
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
    //cout << "Block!" << endl;
  }
  else if (key == PK_KEY_PUNCH) {
    if (network_) network_->sendAction(PK_ACTION_PADDLE_PUNCH);
    else client_->updateAnimation(1, PK_ANIM_PUNCH); 
    //cout << "Punch!" << endl;
  }
  else if (key == PK_KEY_KICK) {
    if (network_) network_->sendAction(PK_ACTION_PADDLE_KICK);
    else client_->updateAnimation(1, PK_ANIM_KICK); 
    //cout << "Kick!" << endl;
  }
  else if (key == PK_KEY_PAUSE) {
    unimplemented("PK_KEY_PAUSE pressed; sending kick");
    if (network_) network_->sendAction(PK_ACTION_PADDLE_KICK);
    else client_->togglePause();
    //cout << "Pause was pressed!" << endl;
  }
}
void
PKPaddleKeys::keyRelease(PKKey key) {
  keysdown[key] = 0;
  lastkeys[4] = lastkeys[3];
  lastkeys[3] = lastkeys[2];
  lastkeys[2] = lastkeys[1];
  lastkeys[1] = lastkeys[0];
  lastkeys[0] = key;
  lasttime[4] = lasttime[3];
  lasttime[3] = lasttime[2];
  lasttime[2] = lasttime[1];
  lasttime[1] = lasttime[0];
  lasttime[0] = gethrtime();
}
void
PKPaddleKeys::doDefaults(PKKey key) {
  if (key == PK_KEY_UP) {
    if (network_) network_->sendAction(PK_ACTION_PADDLE_STOP_VERTICAL);
    //cout << "Stop Moving Up!" << endl;
  }
  else if (key == PK_KEY_DOWN) {
    if (network_) network_->sendAction(PK_ACTION_PADDLE_STOP_VERTICAL);
    //cout << "Stop Moving Down!" << endl;
  }
  else if (key == PK_KEY_LEFT) {
    if (network_) network_->sendAction(PK_ACTION_PADDLE_STOP_HORIZONTAL);
    //cout << "Stop Moving Left!" << endl;
  }
  else if (key == PK_KEY_RIGHT) {
    if (network_) network_->sendAction(PK_ACTION_PADDLE_STOP_HORIZONTAL);
    //cout << "Stop Moving Right!" << endl;
  }
  else if (key == PK_KEY_BLOCK) {
    if (network_) network_->sendAction(PK_ACTION_PADDLE_UNBLOCK);
    else client_->updateAnimation(1, PK_ANIM_PADDLE_UNBLOCK); 
    //cout << "Stop Blocking!" << endl;
  }
}
