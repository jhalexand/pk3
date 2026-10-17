/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: cs032082                                            */
/*    FILE: PKClient.h                                          */
/*    ASGN:                                                     */
/*    DATE: Fri Apr 25 13:51:45 1997                            */
/****************************************************************/


#ifndef PKCLIENT_INTERFACE_HEADER
#define PKCLIENT_INTERFACE_HEADER
#include <PKids.h>
#include <PKGameClasses.h>
#include <PKObject.h>
#include <PKKey.h>
class PKGraphicsInterface;
class PKClientNetworkInterface;
class PKClient;
class PKObject;
class PKGameStatus;
class PKClientObject;

class PKClientInterface {
protected:
  PKClientInterface() {}
  //virtual ~PKClientInterface() {}
public:
  PKClientInterface(PKClient* imp) ;
  virtual ~PKClientInterface() {}
  //Graphics stuff
  virtual PKClientObject* getStateOfObject(PKID id) = 0;
  virtual void handleKeyPress(PKKey key) = 0;
  virtual void handleKeyRelease(PKKey key) = 0;
  //MainServer stuff
  virtual void addUser(int userID, const char* user, 
          const char* account, const char* host) = 0;
  virtual void removeUser(int userID) = 0;
  virtual void addGame(int gameID, const PKGameProgress& prog) = 0;
  virtual void removeGame(int gameID) = 0;
  virtual void enterGameSetup(int gameID, const PKGameParameters& parms, 
          int numPlayers) = 0;
  virtual void error(const char* err) = 0;
  //GameGathering stuff
  virtual void addPlayer(int playerNum, const PKPlayerInfo& info) = 0;
  virtual void removePlayer(int playerNum) = 0;
  virtual void rejectPlayer(int PlayerNum) = 0;
  virtual void setPaddle(int playerNum, PKTypeID paddle) = 0;
  virtual void setTeam(int playerNum, int team) = 0;
  virtual void setKombatKode(int playerNum, const char* kode) = 0;
  virtual void setChatText(int playerNum, const char* text) = 0;
  virtual void returnToMainScreen() = 0;
  virtual void enterGamePlay(const PKGameParameters& parms) = 0;
  //GameServer stuff
  virtual void cancel() = 0;
  virtual void addObject(const PKObject& obj) = 0;
  virtual void removeObject(PKID id) = 0;
  virtual void update(const PKObject& obj) = 0;
  virtual void updateAnimation(PKID unique, PKAnimID id) = 0;
  virtual void gameStatus(const PKGameStatus& stat) = 0; // Return something??
  virtual void endGame() = 0;
  virtual void playSound(PKSoundID id) = 0;
  virtual void togglePause() = 0;
  void setPause(boolean) { 
      unimplemented("pausing is quite broken on the client side");
  }
protected:
  PKClient* client_;
};
#endif
