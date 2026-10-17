/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: bh                                                  */
/*    FILE: PKGameServerImplementation.h                        */
/*    ASGN:                                                     */
/*    DATE: Sun Apr 20 23:05:33 1997                            */
/****************************************************************/


#ifndef PKGAMESERVERImplementation_HEADER
#define PKGAMESERVERImplementation_HEADER

class NETListenSocket ;
#include <Network/NETStream.h>
class PKGameEngineInterface ;
#include "PKGameServerConnection.h"
class PKGameStatus ;
#include <PKids.h>
class PKObject ;

class PKGameServerImplementation {
private:
  int numClients_;
  PKTypeID *paddles_;
  PKKombatKodeID kode_;
  PKGameServerConnection *clients_;

  PKGameServerConnection server_;

  PKGameEngineInterface *engine_;
  //boolean gamePaused_ ; // starts off false
public:
  PKGameServerImplementation(const char *host, int port, int gameID) ;
  void init(PKGameEngineInterface *engine) { engine_ = engine; }
  
  virtual ~PKGameServerImplementation(); // close all connections

  // get the number of players
  int numPlayers() { return numClients_; }

  // get the paddles (remember to copy this)
  PKTypeID *paddles() { return paddles_; }

  // get the kombat kode
  PKKombatKodeID kode() { return kode_; }

  // poll all connections for activity; deal with any active connections
  // by telling game engine to queue up events
  void receive() ;

  // broadcast an update to all clients of the objects that have changed
  // numElements is the number of elements changed
  void broadcastUpdate(PKObject& object);

  // broadcast an update of the game status to all clients
  void broadcastGameStatus(PKGameStatus& status);

  // broadcast the creation of a new object to all clients.
  // ID is the unique id of the new object
  void broadcastAddObject(PKObject& toAdd);

  // broadcast the removal of an object to all clients.
  // ID is the unique id of the object to remove
  void broadcastRemoveObject(PKID toRemove);

  // broadcast the new animation state of the object
  void broadcastAnimateObject(PKID, PKAnimID);

  // broadcast a sound to play
  void broadcastPlaySound(PKSoundID);

  // broadcast the fact that the game is paused
  void broadcastPauseGame(boolean p);

  // broadcast the fact that the game is over
  void broadcastEndGame();

private:

  // invoked when a client has an error.  Deal with the problem, then
  // continue if possible.  If socketNum==-1, it's the server
  void checkErrno(PKGameServerConnection& conn) ;
  void handleHangup(int socketNum);

  void handleAction(int socketNum);
  void spawnAIClient(int playerNum, const char *host, unsigned short port);

} ;

#endif
