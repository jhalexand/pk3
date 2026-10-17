/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: bh                                                  */
/*    FILE: PKGameServerInterface.h                             */
/*    ASGN:                                                     */
/*    DATE: Sun Apr 20 23:05:33 1997                            */
/****************************************************************/


#ifndef PKGAMESERVERINTERFACE_HEADER
#define PKGAMESERVERINTERFACE_HEADER

#include <PKids.h>
#include <debug.h>
class PKGameEngineInterface ;
class PKGameServerImplementation ;
class PKGameStatus ;
class PKObject ;
class NETReadWriteSocket ;
class NETListenSocket ;

class PKGameServerInterface {
private:
  PKGameServerImplementation *imp_;
public:
  // this constructor interface will most probably need parameters;
  // it's just here to allow compiling, and not crashing when making
  // calls
  PKGameServerInterface(const char *host, int port, int gameID) ;
  virtual ~PKGameServerInterface() ;

  // get the number of players
  int numPlayers() ;

  // get the paddles (remember to copy this)
  PKTypeID *paddles();

  // get the kombat kode
  PKKombatKodeID kode();

  // link the network up with the client
  void init(PKGameEngineInterface *inter);


  // poll all connections for activity; deal with any active connections
  // by telling game engine to queue up events
  void receive() ;

  // broadcast an update to all clients of the objects that have changed
  // numElements is the number of elements changed
  void broadcastUpdate(PKObject&);

  // broadcast an update of the game status to all clients
  void broadcastGameStatus(PKGameStatus&);

  // broadcast the creation of a new object to all clients.
  // ID is the unique id of the new object
  void broadcastAddObject(PKObject&);

  // broadcast the removal of an object to all clients.
  // ID is the unique id of the object to remove
  void broadcastRemoveObject(PKID ID);

  // broadcast the new animation state of the object
  void broadcastAnimateObject(PKID, PKAnimID);

  // broadcast a sound to play
  void broadcastPlaySound(PKSoundID);

  // broadcast the fact that the game is paused
  void broadcastPauseGame(boolean p);

  // broadcast the fact that the game is over
  void broadcastEndGame();
} ;

#endif
