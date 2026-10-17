/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: bh                                                  */
/*    FILE: PKGameClientInterface.h                             */
/*    ASGN:                                                     */
/*    DATE: Wed Apr 23 03:07:33 1997                            */
/****************************************************************/


#ifndef PKGAMECLIENTINTERFACE_HEADER
#define PKGAMECLIENTINTERFACE_HEADER

class NETReadWriteSocket ;
#include <PKids.h>
class PKClientInterface;
class PKClientNetworkImplementation;
#include <Xm/Xm.h>

class PKClientNetworkInterface {
private:
  PKClientNetworkImplementation *imp_;
public:
  // construct the client
  PKClientNetworkInterface(PKClientInterface* client, XtAppContext app,
			   const char *hostname, int port,
			   const char *name, const char *acct, 
                           const char *local) ;

  // construct connecting only to the game server
  PKClientNetworkInterface(PKClientInterface *client, XtAppContext app,
			   const char *hostname, int port,
			   int playerNum);

  void hangup(); // called at any time, for example at C-c


  // functions to call during game setup (when you're first connected)
  void createGame(); // tell the server to create a new game
  void joinGame(int gameID); // try to join the given game

  // functions to call during game gathering (after join/create game)
  void addAIPlayer(int playerNum, PKAILevel aiLevel);
  void setTeam(int teamID); // change the team
  void setPaddle(PKTypeID paddle); // the paddle id
  void sendKombatKode(const char *kode);
  void sendChatText(const char *text);
  void rejectPlayer(int playerNum); // 0-3
  void cancelGame(); // cancel the game (allowed only by creator)
  void startGame(); // start playing (allowed only by creator)
  void endGame(); // end playing (allowed only by creator)
  void ready(); // FIGHT!!
  
  // functions to call on ai clients
  void setTeam(int playerNum, int teamID); // change the team
  void setPaddle(int playerNum, PKTypeID paddle); // the paddle id
  void sendKombatKode(int playerNum, const char *kode);
  void sendChatText(int playerNum, const char *text);


  // send the action ID for processing by the server
  // We have to tell who did the action so that the server
  // knows who to tell to do the action
  void sendAction(PKActionID id);
} ;

#endif
