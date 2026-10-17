/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: cs032082                                            */
/*    FILE: PKClient.h                                          */
/*    ASGN:                                                     */
/*    DATE: Sat Apr 26 20:57:10 1997                            */
/****************************************************************/


#ifndef PKCLIENT_HEADER
#define PKCLIENT_HEADER
#include <Xm/Xm.h>
#include <PKids.h>
#include <PKGameClasses.h>
#include <PKObject.h>
#include <PKKey.h>
#include <PKClientInterface.h>
class PKOpeningGUI;
class PKKonnectGUI;
class PKMainServerGUI;
class PKGameGatheringGUI;
class PKGameGUI;
class PKClientNetworkInterface;
class PKGraphicsInterface;
class PKObjectList;
class PKPaddleKeys;
class PKClientObject;
class PKAudioPlayer;

class PKClient : public PKClientInterface {
public:
  //  PKClient();
  PKClient(int argc, char** argv);
  ~PKClient();
  //Graphics stuff
  PKClientObject* getStateOfObject(PKID id);
  virtual void handleKeyPress(PKKey key);
  virtual void handleKeyRelease(PKKey key);

  //Opening & Connecting stuff
  virtual void enterKonnectScreen();
  virtual void enterSinglePlayer();

  //MainServer stuff
  virtual void enterMainServer(const char* host, const char* name, 
          const char* port);
  virtual void addUser(int userID, const char* user, const char* account, 
          const char* host);
  virtual void removeUser(int userID);
  virtual void addGame(int gameID, const PKGameProgress& prog);
  virtual void removeGame(int gameID);
  virtual void enterGameSetup(int gameID, const PKGameParameters& parms, 
          int playerNum);
  virtual void error(const char* err);
  //GameGathering stuff
  //  virtual void testGather(int num);
  virtual void addPlayer(int playerNum, const PKPlayerInfo& info);
  virtual void removePlayer(int playerNum);
  virtual void rejectPlayer(int playerNum);
  virtual void setPaddle(int playerNum, PKTypeID paddle);
  virtual void setTeam(int playerNum, int team);
  virtual void setKombatKode(int playerNum, const char *text);
  virtual void setChatText(int playerNum, const char *text);
  virtual void returnToMainScreen();
  virtual void enterGamePlay(const PKGameParameters& parms);
  //GameServer stuff
  virtual void cancel();
  virtual void addObject(const PKObject& obj);
  virtual void removeObject(PKID id);
  virtual void update(const PKObject& obj);
  virtual void updateAnimation(PKID unique, PKAnimID id);
  virtual void gameStatus(const PKGameStatus& stat);
  virtual void endGame();
  virtual void playSound(PKSoundID id);
  virtual void rejectMe();
  virtual void setPause(boolean paused);
  virtual void togglePause() { setPause(!is_paused_); }
  static void errorCB(Widget widget, XtPointer client_data, XtPointer call_data);
  static void fileCB(Widget widget, XtPointer client_data, XtPointer call_data);

private:
  void startSound() ; // create the audio and initialize it
  void loadDefaults(int argc, const char **) ; // parse .pk3rc, command-line
  
protected:
  PKOpeningGUI* opening_;
  PKKonnectGUI* konnect_;
  PKMainServerGUI* main_;
  PKGameGatheringGUI* gather_;
  PKObjectList* top_;
  PKGameStatus status_;
  PKPaddleKeys* keys_;
  PKClientNetworkInterface* network_;
  PKGraphicsInterface* graphics_;
  PKAudioPlayer* audio_;
  XtAppContext app_context_;
  int player_;
  PKTypeID paddle_;
  Widget parent_, shell_, shell1_, shell2_, shell3_, shell4_, window_;
  boolean is_paused_ ;
};

#endif
