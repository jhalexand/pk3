/*************************************************************************
 *    NAME: Jeffrey Alexander
 *    USER: jla
 *    FILE: MAINNetwork.cxx
 *    DATE: Sun Apr 27 21:00:09 US/Eastern 1997
 *************************************************************************/
#include "MAINNetwork.h"
#include "MAINdefs.h"
#include "MAINUser.h"
#include "MAINGame.h"

#include <Network/NETListenSocket.h>
#include <Network/NETReadWriteSocket.h>
#include <Network/NETids.h>
#include <Network/NetworkException.h>
#include <debug.h>
#include <iostream.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>

/*************************************************************************/
/* Function Name: MAINNetwork::MAINNetwork                               */
/* Parameters: MAINServer* theServer                                     */
/* Effects:                                                              */
/*************************************************************************/

MAINNetwork::MAINNetwork(MAINServer* theServer)
{
	_server = theServer;
	_numUsers = 0;
	_numGames = 0;
	_userArray = new MAINUser*[MAX_USERS];
	_gameArray = new NETReadWriteSocket*[MAX_GAMES];

	// complicated by bh Mon May  5 02:46:38 EDT 1997 to
	// search for an open pair of ports
	_clientListener = _gameListener = null ;
	int clientPort = MAIN_SERVER_CLIENT_PORT ;
	while(!_clientListener && !_gameListener) {
	  try {
	    _clientListener = new NETListenSocket(clientPort, MAX_PENDING);
	    _gameListener = new NETListenSocket(clientPort+1, MAX_PENDING);
	  } catch (NetworkException& xcp) {
	    clientPort+=2;
	  }
	}
	dprintf(("server listening on port %d for clients, %d for games\n",
		 clientPort, clientPort+1));
	// end bh modifications
	
	for (int i=0;i<MAX_USERS;i++) {
		_userArray[i]=0;
	}
	for (i=0;i<MAX_GAMES;i++) {
		_gameArray[i]=0;
	}
}


/*************************************************************************/
/* Function Name: MAINNetwork::~MAINNetwork                              */
/* Parameters:                                                           */
/* Effects:                                                              */
/*************************************************************************/

MAINNetwork::~MAINNetwork()
{
	for (int i = 0; i < MAX_USERS; i++) {
		if (_userArray[i]) {
			delete _userArray[i];
		}
	}
	for (i = 0; i < MAX_GAMES; i++) {
		if (_gameArray[i]) {
			delete _gameArray[i];
		}
	}
	delete[] _userArray;
	delete[] _gameArray;
	delete _clientListener;
	delete _gameListener;
}


/*************************************************************************/
/* Function Name: MAINNetwork::listen                                    */
/* Parameters:                                                           */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINNetwork::listen()
{
	struct pollfd fds[MAX_SOCKETS+3]; // room for users, listener, stdin

	// whenever we listen, we make an array of poll file descriptors...
	// we set those to be the file descriptor of the users' sockets.
	for (int i = 0; i < MAX_USERS; i++) {
		if (_userArray[i]) {
			fds[i].fd = _userArray[i]->fileDescriptor();
			fds[i].events = POLLIN;
			fds[i].revents = -1;
		} else {
			fds[i].fd = -1; // don't check this one
		}
	}

	// then we add in the fds of the game's sockets
	for (i = 0; i < MAX_GAMES; i++) {
		if (_gameArray[i]) {
			fds[MAX_USERS+i].fd = _gameArray[i]->fileDescriptor();
			fds[MAX_USERS+i].events = POLLIN;
			fds[MAX_USERS+i].revents = -1;
		} else {
			fds[MAX_USERS+i].fd = -1;
		}
	}

	// Now tack on the server's socket for new client connections
	fds[MAX_SOCKETS].fd = _clientListener->fileDescriptor();
	fds[MAX_SOCKETS].events = POLLIN;
//	dprintf(("fd for client listener: %d\n", fds[MAX_SOCKETS].fd));

	// and the same thing for new game connections
	fds[MAX_SOCKETS+1].fd = _gameListener->fileDescriptor();
	fds[MAX_SOCKETS+1].events = POLLIN;
//	dprintf(("fd for game listener: %d\n", fds[MAX_SOCKETS+1].fd));
        
        // bh
        // and stdin, for a nicer way to kill this (so we can do 
        // mem-leak checking).
        fds[MAX_SOCKETS+2].fd = 0;
        fds[MAX_SOCKETS+2].events = POLLIN;
        fds[MAX_SOCKETS+2].revents = 0;
        // end bh
	
	// Poll away...  block until we get something
	poll(fds, MAX_SOCKETS+3, -1);
	dprintf(("Poll returned...\n"));
        
        // bh
        if(fds[MAX_SOCKETS+2].revents) {
            dprintf(("Got activity on stdin: exiting if C-d\n"));
            char foo[256];
            if(!fgets(foo, 256, stdin)) exit(0);
        }
        // end bh

//	dprintfNoLevel(("\n"));
	// See which client sockets had something happen on them and deal with it.
	for (i = 0; i<MAX_USERS; i++) {
		if (_userArray[i] && ((fds[i].revents & POLLHUP) || (fds[i].revents & POLLERR))) {
			dprintf(("Cleaning up because a client hung up... "));
			_server->removeUserFromList(i);
			delete _userArray[i];
			_userArray[i]=0;
			// THIS IS A TEMPORARY SOLUTION
			// IT DOES NOT HANDLE USERS IN A GATHERING GAME
			dprintf((" ...done.\n"));
		} else if (_userArray[i] && (fds[i].revents & POLLIN)) {
			dprintf(("Incoming data from client, error checking...\n"));
			try {
				readFromUser(i);
			} catch(NetworkException& netdied) {
				dprintf(("Looks like we had a problem...\n"));
				netdied.print(); putchar('\n');
				dprintf(("Removing user from userlist...\n"));
				_server->removeUserFromList(i);
				dprintf(("Removing user from current games...\n"));
				_server->checkAndRemoveUserFromGames(_userArray[i]);
				delete _userArray[i];
				_userArray[i]=0;
				_numUsers--;
				dprintf((" ...done.\n"));
			}
		}
	}

	for (i = 0; i<MAX_GAMES; i++) {
		if (_gameArray[i] && (fds[MAX_USERS+i].revents & POLLIN)) {
			dprintf(("Incoming data from _game_ server...\n"));
			try {
				readFromGame(i);
			} catch(NetworkException &gamedied) {
				dprintf(("Dammit, I'm caring about a game server that died, and i'll bet i shouldn't be\n"));
				gamedied.print(); putchar('\n');
				MAINGame *deadGame = _server->getGameBySocketAddress((int)_gameArray[i]);
				if (deadGame) {
					deadGame->dumpAllUsers();
					_server->deleteGame(deadGame->getID());
				}
				delete _gameArray[i];
				_gameArray[i]=0;
				_numGames--;
			}
		}
	}

	// See if we got any new clients to connect.
	if (fds[MAX_SOCKETS].revents & POLLIN) {
		dprintf(("Looks like a client is connecting\n"));
		createUser();
	}

	// See if we got any new game servers.
	if (fds[MAX_SOCKETS+1].revents & POLLIN) {
		dprintf(("Looks like a game server is connecting\n"));
		addGameServer();
	}
}


/*************************************************************************/
/* Function Name: MAINNetwork::readFromUser                              */
/* Parameters: int whichUser                                             */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINNetwork::readFromUser(int whichUser)
{
	_userArray[whichUser]->respondToRequest();
}


/*************************************************************************/
/* Function Name: MAINNetwork::readFromGame                              */
/* Parameters: int whichGame                                             */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINNetwork::readFromGame(int whichGame)
{
	int request = _gameArray[whichGame]->getInt();
//	_gameArray[whichGame]->respondToRequest();
	if (request == NETRequest::CONNECT_AS_GAMESERVER) {
		dprintf(("Got a CONNECT_AS_GAMESERVER\n"));
		int gameID = _gameArray[whichGame]->getInt();
		char *host = _gameArray[whichGame]->getString();
		int port = _gameArray[whichGame]->getInt();
		_server->attachServerToGame(_gameArray[whichGame], gameID, host, port);
	} else if (request == NETRequest::HANGUP) {
		dprintf(("Got a game server hangup... cleaning it up."));
		MAINGame *deadGame = _server->getGameBySocketAddress((int)_gameArray[whichGame]);
		if (deadGame) {
			deadGame->dumpAllUsers();
			_server->deleteGame(deadGame->getID());
		}
		delete _gameArray[whichGame];  // THIS ONLY DELETES THE SOCKET!
		_gameArray[whichGame]=0;
		_numGames--;
	}
	dprintf(("-----Done servicing game request-----\n"));
}


/*************************************************************************/
/* Function Name: MAINNetwork::createUser                                */
/* Parameters:                                                           */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINNetwork::createUser()
{
	if (_numUsers >= MAX_USERS) {
		system("echo \"Main Server has run out of client sockets!\" |mail jla");
	}
	else {
		// make a new read write socket in the lowest available space
		dprintf(("creating a new user!\n"));
		for (int i=0; i < MAX_USERS; i++) {
			if (!_userArray[i]) {
				_numUsers++;
				// construct a new user with a new socket
				_userArray[i] = new MAINUser(_clientListener->accept(), i, _server);
				dprintf(("...the User has ID: %d\n", i));
				// tell the server to add the user
//				_server->addUser(_userArray[i]);
				// actually, user will tell server after getting a
				// CONNECT_AS_CLIENT request (and not before that mind you!)
				return ;
			}
		}
	}
}


/*************************************************************************/
/* Function Name: MAINNetwork::addGameServer                             */
/* Parameters:                                                           */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
void
MAINNetwork::addGameServer()
{
	if (_numGames >= MAX_GAMES) {
		system("echo \"Main Server has run out of game sockets!\" |mail jla");
	}
	else {
		for (int i=0; i < MAX_GAMES; i++) {
			if (!_gameArray[i]) {
				_numGames++;
				dprintf(("Accepting a game server connection\n"));
				_gameArray[i] = _gameListener->accept();
//				_server->setGameServerOfGame(_gameArray[i], i);
				return ;
			}
		}
	}
}
