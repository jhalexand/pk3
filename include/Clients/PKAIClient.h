/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: bh                                                  */
/*    FILE: PKAIClient.h                                        */
/*    ASGN:                                                     */
/*    DATE: Sun May  4 06:55:55 1997                            */
/****************************************************************/


#ifndef PKAICLIENT_HEADER
#define PKAICLIENT_HEADER

#include <PKClientInterface.h>
#include <rw/tvslist.h>
#include <Xm/Xm.h>
#include <sys/time.h>
#include <Clients/PKClient.h>

class PKAIClient : public PKClientInterface {
private:
  XtAppContext app_ ;
  PKClientNetworkInterface *net_ ;

  int direction_; // 1=up, 0=still, -1=down
  hrtime_t lastFireTime_;
    
  int playerNum_;
  PKObject self_;
  PKID unique_;

  RWTValSlist<PKObject> followList_;
  RWTValSlist<PKObject> targetList_;
  RWTValSlist<PKObject> hiddenList_; // invisible players, etc
public:
  PKAIClient(const char *host, int port, int playerNum);
  virtual ~PKAIClient();
  virtual PKClientObject* getStateOfObject(PKID id) { return null;}
  virtual void handleKeyPress(PKKey key) {}
  virtual void handleKeyRelease(PKKey key) {}

  //MainServer stuff
  virtual void addUser(int userID, char* user, char* account, char* host) {}
  virtual void removeUser(int userID) {}
  virtual void addGame(int gameID, PKGameProgress prog) {}
  virtual void removeGame(int gameID) {}
  virtual void enterGameSetup(int gameID, PKGameParameters& parms, int numPlayers
) {}
  virtual void error(char* err) {}

  //GameGathering stuff
  virtual void addPlayer(int playerNum, PKPlayerInfo info) {}
  virtual void removePlayer(int playerNum) {}
  virtual void rejectPlayer(int PlayerNum) {}
  virtual void setPaddle(int playerNum, PKTypeID paddle) {}
  virtual void setTeam(int playerNum, int team) {}
  virtual void setKombatKode(int playerNum, char* kode) {}
  virtual void setChatText(int playerNum, char* text) {}
  virtual void returnToMainScreen() {}
  virtual void cancel() {}
  virtual void enterGamePlay(PKGameParameters& parms);  

  //GameServer stuff
  virtual void addObject(PKObject& obj);
  virtual void removeObject(PKID id);
  virtual void update(PKObject obj);
  virtual void updateAnimation(PKID unique, PKAnimID id);
  virtual void gameStatus(PKGameStatus& stat);
  virtual void endGame() { exit(0); }

  virtual void playSound(PKSoundID) {}

private:
  static void static_updateCallback(void *thus, XtIntervalId*);
  void update();
  static const hrtime_t FIRE_RATE ;
  static const double FIRE_OFF;
  static const int UP;
  static const int DOWN;
  static const int STILL;
} ;

#endif
