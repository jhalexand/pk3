/*************************************************************************/
/*    NAME: Dave Akers                                                   */
/*    ACCT: dla                                                          */
/*    FILE: PKGameEngine.h                                               */
/*    DATE: Thu Apr 24 21:58:55 1997                                     */
/*************************************************************************/


#ifndef GEROUNDENGINE_HEADER
#define GEROUNDENGINE_HEADER

#include <PKids.h>
#include <PKGameClasses.h>
#include "GEContainer.h"
#include "GEEvent.h"
#include "GEWall.h"
#include <PKGameServerInterface.h>
#include <PKPhysicsInterface.h>
#include "PKGameEngine.h"

class PKRoundEngine {
public:

  PKRoundEngine(PKGameServerInterface* server,
	       int numplayers,
	       PKTypeID players[],
		PKKombatKodeID kode) :
    _numplayers(numplayers), _players(players), _kode(kode),
    _server(server), _current_game(NULL) {_score[0] = _score[1] = 0;}

  ~PKRoundEngine() {}

  void mainloop();
  void handleAction(int playerNum, PKActionID action) {
    if (_current_game) _current_game->handleAction (playerNum, action); 
  }

private:

  PKGameEngine *_current_game;
  int _score[2]; // Team 1 wins, team 2 wins..
  int _numplayers;
  PKTypeID *_players;
  PKKombatKodeID _kode;
  PKGameServerInterface *_server;

};

#endif

