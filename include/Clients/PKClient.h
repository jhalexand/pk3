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
class PKClientInterface;
class PKOpeningGUI;
class PKMainServerGUI;
class PKGameGatheringGUI;
class PKGameGUI;
class PKClientNetworkInterface;
class PKGraphicsInterface;
class PKObjectList;
class PKPaddleKeys;
class PKClientObject;

class PKClient {
public:
  PKClient(int argc, char** argv);
  ~PKClient();
  //Graphics stuff
  PKClientObject* getStateOfObject(PKID id);
  void handleKeyPress(PKKey key);
  void handleKeyRelease(PKKey key);
  //MainServer stuff
  void enterMainServer(char* host, char* name, char* port);
  void addUser(int userID, char* user, char* account, char* host);
  void removeUser(int userID);
  void addGame(int gameID, PKGameProgress prog);
  void removeGame(int gameID);
  void enterGameSetup(int gameID, PKGameParameters parms, int playerNum);
  void error(char* err);
  //GameGathering stuff
  void testGather(int num);
  void addPlayer(int playerNum, PKPlayerInfo info);
  void removePlayer(int playerNum);
  void rejectPlayer(int playerNum);
  void setPaddle(int playerNum, PKTypeID paddle);
  void setTeam(int playerNum, int team);
  void returnToMainScreen();
  void enterGamePlay(PKGameParameters& parms);
  //GameServer stuff
  void cancel();
  void addObject(PKObject& obj);
  void removeObject(PKID id);
  void update(PKObject obj);
  void updateAnimation(PKID unique, PKAnimID id);
  void gameStatus(PKGameStatus& stat);

  static void errorCB(Widget widget, XtPointer client_data, XtPointer call_data);
protected:
  PKOpeningGUI* opening_;
  PKMainServerGUI* main_;
  PKGameGatheringGUI* gather_;
  PKObjectList* top_;
  PKGameStatus status_;
  PKPaddleKeys* keys_;
  PKClientInterface* interface_;
  PKClientNetworkInterface* network_;
  PKGraphicsInterface* graphics_;
  XtAppContext app_context_;
  int player_;
  PKTypeID paddle_;
  Widget parent_, shell_, shell1_, shell2_, shell3_, window_;
};

#endif
