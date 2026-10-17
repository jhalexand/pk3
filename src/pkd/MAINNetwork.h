/*************************************************************************/
/*    NAME: Jeff Alexander                                               */
/*    FILE: MAINNetwork.h                                                */
/*    ASGN: Final Project                                                */
/*    DATE: Sat Apr 26 21:19:03 1997                                     */
/*************************************************************************/


#ifndef MAINNETWORK_HEADER
#define MAINNETWORK_HEADER

#include "MAINServer.h"
#include "MAINUser.h"

#include <Network/NETListenSocket.h>
#include <Network/NETReadWriteSocket.h>

class MAINNetwork {
public:
	MAINNetwork(MAINServer* theServer);
	virtual ~MAINNetwork();

	void listen();
	void readFromUser(int whichUser);
	void readFromGame(int whichGame);
	void createUser();
	void addGameServer();

  int getGamePort() { return _gameListener->portNumber(); }
  int getClientPort() { return _clientListener->portNumber(); }
protected:
	MAINUser**           _userArray;
	MAINServer*          _server;
	NETListenSocket*     _clientListener;
	NETListenSocket*     _gameListener;
	NETReadWriteSocket** _gameArray;

	int                 _numUsers;
	int                 _numGames;
};

#endif
