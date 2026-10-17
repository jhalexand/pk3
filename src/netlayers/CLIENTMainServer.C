/*************************************************************************
 *    NAME: Benoit Hudson
 *    USER: bh
 *    FILE: CLIENTMainServer.C
 *    DATE: Thu May  1  0:35:12 US/Eastern 1997
 *************************************************************************/
#include "CLIENTMainServer.h"

#include <debug.h>
#include <fcntl.h>
#include <Network/NETids.h>
#include <Network/NetworkException.h>
#include <PKClientInterface.h>
#include "PKClientNetworkImplementation.h"
#include <PKPaths.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <unistd.h>

int CLIENTMainServer::errno_ = 0;
const int CLIENTMainServer::EREADTOOLITTLE = 1;
const int CLIENTMainServer::EREADNONE = 2;

/*************************************************************************
 * Function Name: CLIENTMainServer::CLIENTMainserver
 * Parameters: PKClientInterface* client, XtAppContext app, char *hostname, int port, char *name, char *acct, char *local
 * Effects: 
 *************************************************************************/

CLIENTMainServer::CLIENTMainServer(PKClientInterface* client, XtAppContext app,
				   const char *hostname, int port,
				   const char *name, const char *acct,
				   const char *local,
				   PKClientNetworkImplementation *ntwrk)
{
  client_ = client;
  ntwrk_ = ntwrk;
  app_ = app;
  
  dprintf(("PKClientNetwork connecting to server on %s %d\n", hostname, port));

  stream_.attachTo(new NETReadWriteSocket(hostname, port));
  stream_.attachedTo()->setReadZero(CLIENTMainServer::static_readException, this);
  stream_.attachedTo()->setReadLittle(CLIENTMainServer::static_readException, this);

  stream_.startRequest(NETRequest::CONNECT_AS_CLIENT);
  stream_ << name;
  stream_ << acct;
  stream_ << local;
  stream_.endRequest();

  callbackID_ = XtAppAddInput(app_, stream_.attachedTo()->fileDescriptor(),
			      (void*)XtInputReadMask,
			      CLIENTMainServer::static_receive, this);
}


/*************************************************************************
 * Function Name: CLIENTMainServer::~CLIENTMainserver
 * Parameters: none
 * Effects: 
 *************************************************************************/

CLIENTMainServer::~CLIENTMainServer()
{
  hangup();
}






/*************************************************************************
 * Function Name: CLIENTMainServer::hangup
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
CLIENTMainServer::hangup()
{
  if(stream_.attachedTo()) {
    XtRemoveInput(callbackID_);
    stream_.startRequest(NETRequest::HANGUP);
    stream_.endRequest();
    delete stream_.attachedTo() ;
    stream_.detach() ;
  }
}


/*************************************************************************
 * Function Name: CLIENTMainServer::createGame
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
CLIENTMainServer::createGame()
{
  stream_.startRequest(NETRequest::CREATE_GAME);
  stream_ << userID_;
  stream_.endRequest();
}


/*************************************************************************
 * Function Name: CLIENTMainServer::joinGame
 * Parameters: int gameID
 * Returns: void
 * Effects: 
 *************************************************************************/
void
CLIENTMainServer::joinGame(int gameID)
{
  gameID_ = gameID ;

  stream_.startRequest(NETRequest::JOIN_GAME);
  stream_ << userID_ << gameID_;
  stream_.endRequest();
}


/*************************************************************************
 * Function Name: CLIENTMainServer::addAIPlayer
 * Parameters: int playerNum, PKAILevel lvl
 * Returns: void
 * Effects: 
 *************************************************************************/
void
CLIENTMainServer::addAIPlayer(int playerNum, PKAILevel lvl)
{
  stream_.startRequest(NETRequest::ADD_AI_PLAYER);
  stream_ << playerNum << lvl;
  stream_.endRequest();
}


/*************************************************************************
 * Function Name: CLIENTMainServer::setTeam
 * Parameters: int playerNum, int teamID
 * Returns: void
 * Effects: 
 *************************************************************************/
void
CLIENTMainServer::setTeam(int playerNum, int teamID)
{
  dprintf(("C->MAIN: sending SET_TEAM, player=%d, team=%d\n", playerNum, teamID));
  stream_.startRequest(NETRequest::SET_TEAM);
  stream_ << gameID_ << playerNum << teamID;
  stream_.endRequest();
}


/*************************************************************************
 * Function Name: CLIENTMainServer::setPaddle
 * Parameters: PKTypeID paddle
 * Returns: void
 * Effects: 
 *************************************************************************/
void
CLIENTMainServer::setPaddle(int playerNum, PKTypeID paddle)
{
  stream_.startRequest(NETRequest::SET_PADDLE);
  stream_ << gameID_ << playerNum << paddle ;
  stream_.endRequest();
}


/*************************************************************************
 * Function Name: CLIENTMainServer::sendKombatKode
 * Parameters: char *kode
 * Returns: void
 * Effects: 
 *************************************************************************/
void
CLIENTMainServer::sendKombatKode(int playerNum, const char *kode)
{
  stream_.startRequest(NETRequest::SEND_KOMBAT_KODE);
  stream_ << gameID_ << playerNum << kode;
  stream_.endRequest();
}


/*************************************************************************
 * Function Name: CLIENTMainServer::sendChatText
 * Parameters: char *text
 * Returns: void
 * Effects: 
 *************************************************************************/
void
CLIENTMainServer::sendChatText(int playerNum, const char *text)
{
  stream_.startRequest(NETRequest::SEND_CHAT_TEXT);
  stream_ << gameID_ << playerNum << text;
  stream_.endRequest();
}


/*************************************************************************
 * Function Name: CLIENTMainServer::rejectPlayer
 * Parameters: int playerNum
 * Returns: void
 * Effects: 
 *************************************************************************/
void
CLIENTMainServer::rejectPlayer(int playerNum, int toReject)
{
  stream_.startRequest(NETRequest::REJECT_PLAYER);
  stream_ << gameID_ << playerNum << toReject ;
  stream_.endRequest();
}


/*************************************************************************
 * Function Name: CLIENTMainServer::cancelGame
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
CLIENTMainServer::cancelGame()
{
  stream_.startRequest(NETRequest::CANCEL_GAME);
  stream_ << gameID_;
  stream_.endRequest();
}


/*************************************************************************
 * Function Name: CLIENTMainServer::startGame
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
CLIENTMainServer::startGame()
{
  stream_.startRequest(NETRequest::START_GAME);
  stream_ << gameID_;
  stream_.endRequest();
}


/*************************************************************************
 * Function Name: CLIENTMainServer::endGame
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
CLIENTMainServer::endGame()
{
  stream_.startRequest(NETRequest::END_GAME);
  stream_ << gameID_;
  stream_.endRequest();
}












/*************************************************************************
 * Function Name: CLIENTMainServer::static_receive
 * Parameters: void *thus, int*, XtInputId*
 * Returns: void
 * Effects: 
 *************************************************************************/
void
CLIENTMainServer::static_receive(void *thus, int*, XtInputId*)
{
  ((CLIENTMainServer*)thus)->receive();
}


/*************************************************************************
 * Function Name: CLIENTMainServer::receive
 * Parameters: none
 * Returns: void
 * Effects: parses the request into a function call
 *************************************************************************/
void
CLIENTMainServer::receive()
{
  int reqnum ;
  stream_ >> reqnum ;
  if(errno_) return ;

  dprintf(("getting request %d from main server\n", reqnum));
  switch(reqnum) {
  case NETRequest::HANGUP: hangup(); break;

  case NETRequest::CONNECT_AS_CLIENT_ACK: connectAsClientAck(); break;

  case NETRequest::ADD_USER: addUser(); break;
  case NETRequest::REMOVE_USER: removeUser(); break;

  case NETRequest::ADD_GAME: addGame(); break;
  case NETRequest::REMOVE_GAME: removeGame(); break;

  case NETRequest::CREATE_GAME_ACK: createGameAck(); break;
  case NETRequest::JOIN_GAME_ACK: joinGameAck(); break;
  case NETRequest::JOIN_GAME_REJECT_ACK: joinGameAck(); break;

  case NETRequest::ADD_PLAYER: addPlayer(); break;
  case NETRequest::REMOVE_PLAYER: removePlayer(); break;

  case NETRequest::SET_TEAM_ACK: setTeamAck(); break;
  case NETRequest::SET_PADDLE_ACK: setPaddleAck(); break;
  case NETRequest::SEND_KOMBAT_KODE_ACK: sendKombatKodeAck(); break;
  case NETRequest::SEND_CHAT_TEXT_ACK: sendChatTextAck(); break;
  case NETRequest::REJECT_PLAYER_ACK: rejectPlayerAck(); break;

  case NETRequest::START_GAME_ACK: startGameAck(); break;

  case NETRequest::CANCEL_GAME_ACK: cancelGameAck(); break;
  case NETRequest::ATTACH_TO_GAME_SERVER: attachToGameServer(); break;

  default:
    {
      dprintf(("PKClientNetwork::receive: unhandled request %d\n", reqnum));
      char buf[STRLEN];
      sprintf(buf, "Invalid request 0x%x sent from pkd", reqnum);
      client_->error(buf);
      ntwrk_->hangupOnMainServer();
      return ;
    }
  }
}


/*************************************************************************
 * Function Name: CLIENTMainServer::connectAsClientAck
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
CLIENTMainServer::connectAsClientAck()
{
  stream_ >> userID_ ;
  dprintf(("user id set to %d\n", userID_));
}


/*************************************************************************
 * Function Name: CLIENTMainServer::addUser
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
CLIENTMainServer::addUser()
{
  int userID;
  char *user, *acct, *host;

  stream_ >> userID >> &user >> &acct >> &host ;

  client_->addUser(userID, user, acct, host);

  free(user);
  free(acct);
  free(host);
}


/*************************************************************************
 * Function Name: CLIENTMainServer::removeUser
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
CLIENTMainServer::removeUser()
{
  client_->removeUser(stream_.get());
}


/*************************************************************************
 * Function Name: CLIENTMainServer::addGame
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
CLIENTMainServer::addGame()
{
  int gameID ;
  PKGameProgress prog;

  stream_ >> gameID;
  stream_ >> prog;

  client_->addGame(gameID, prog);
}


/*************************************************************************
 * Function Name: CLIENTMainServer::removeGame
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
CLIENTMainServer::removeGame()
{
  client_->removeGame(stream_.get());
}


/*************************************************************************
 * Function Name: CLIENTMainServer::createGameAck
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
CLIENTMainServer::createGameAck()
{
  PKGameParameters parms;
  int playerNum;
  
  dprintf(("C<-MAIN: about to start getting createGameAck parameters from main server\n"));
  dprintfLevelUp();
  stream_ >> gameID_ ; dprintf(("game id: %d\n", gameID_));
  stream_ >> playerNum ; dprintf(("player: %d\n", playerNum));
  stream_ >> parms; dprintf(("got game parms\n"));
  dprintfLevelDown(); 
  dprintf(("create game ack received; passing off to client\n"));

  ntwrk_->setPlayerNumber(playerNum);
  client_->enterGameSetup(gameID_, parms, playerNum);
}


/*************************************************************************
 * Function Name: CLIENTMainServer::joinGameAck
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
CLIENTMainServer::joinGameAck()
{
  PKGameParameters parms;
  int playerNum;
  
  dprintf(("C<-MAIN: about to start getting joinGameAck parameters from main server\n"));
  dprintfLevelUp();
  stream_ >> playerNum ; dprintf(("player: %d\n", playerNum));
  stream_ >> parms;      dprintf(("got game parms\n"));
  dprintfLevelDown(); 
  dprintf(("C<-MAIN: received join game acknowledgment for player %d\n",
	   playerNum));

  ntwrk_->setPlayerNumber(playerNum);
  client_->enterGameSetup(gameID_, parms, playerNum);
}


/*************************************************************************
 * Function Name: CLIENTMainServer::addPlayer
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
CLIENTMainServer::addPlayer()
{
  int playerNum;
  PKPlayerInfo play;

  stream_ >> playerNum >> play;

  client_->addPlayer(playerNum, play);
}


/*************************************************************************
 * Function Name: CLIENTMainServer::removePlayer
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
CLIENTMainServer::removePlayer()
{
  client_->removePlayer(stream_.get());
}


/*************************************************************************
 * Function Name: CLIENTMainServer::setTeamAck
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
CLIENTMainServer::setTeamAck()
{
  int playerNum, teamNum;

  stream_ >> playerNum >> teamNum ;

  dprintf(("\tSET_TEAM_ACK: player %d; team %d\n", playerNum, teamNum));
  client_->setTeam(playerNum, teamNum);
}


/*************************************************************************
 * Function Name: CLIENTMainServer::setPaddleAck
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
CLIENTMainServer::setPaddleAck()
{
  int playerNum;
  PKTypeID paddle;

  stream_ >> playerNum >> paddle ;
  client_->setPaddle(playerNum, paddle);
}


/*************************************************************************
 * Function Name: CLIENTMainServer::sendKombatKodeAck
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
CLIENTMainServer::sendKombatKodeAck()
{
  int playerNum;
  char *kode ;

  stream_ >> playerNum >> &kode ;
  client_->setKombatKode(playerNum, kode);

  free(kode);
}


/*************************************************************************
 * Function Name: CLIENTMainServer::sendChatTextAck
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
CLIENTMainServer::sendChatTextAck()
{
  int playerNum;
  char *text ;

  stream_ >> playerNum >> &text ;
  client_->setChatText(playerNum, text);

  free(text);
}


/*************************************************************************
 * Function Name: CLIENTMainServer::rejectPlayerAck
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
CLIENTMainServer::rejectPlayerAck()
{
  int playerNum;

  stream_ >> playerNum ;
  client_->rejectPlayer(playerNum);
}


/*************************************************************************
 * Function Name: CLIENTMainServer::startGameAck
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
CLIENTMainServer::startGameAck()
{
  PKGameParameters parms;
  char *host;
  int port;

  stream_ >> parms >> &host >> port;

  XtRemoveInput(callbackID_);

  if(fork()==0) {
    // then you are the child; exec the game server    

    char portBuf[STRLEN] ;
    char gameIDBuf[STRLEN] ;
    char toexec[STRLEN];
    int fd ;

    // USAGE: pkgameserver <host> <port> <gameid>
    // host is already a string
    sprintf(portBuf, "%d", port);
    sprintf(gameIDBuf, "%d", gameID_);

    // set up the exec name
    sprintf(toexec, "%s/pkgameserver", PKBINPATH);

    // open the output as /tmp/pkgameserver<pid>.out
    char outfile[STRLEN];
    sprintf(outfile, "/tmp/pkgameserver%d.out", getpid());
    
    // write-only, default perms for stdout and stderr
    fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    close(1); close(2);
    dup2(fd, 1) ;
    dup2(fd, 2) ;
    if(fd!=1 && fd!=2) close(fd);

    execl(toexec, "pkgameserver", host, portBuf, gameIDBuf, null) ;

    // it returned, which is bad
    client_->error("couldn't fork game server!");
    perror("fork failed");
    exit(1);
  }

  callbackID_ = XtAppAddInput(app_, stream_.attachedTo()->fileDescriptor(),
			      (void*)XtInputReadMask,
			      CLIENTMainServer::static_receive, this);

  free(host); host=null;
}


/*************************************************************************
 * Function Name: CLIENTMainServer::cancelGameAck
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
CLIENTMainServer::cancelGameAck()
{
  client_->returnToMainScreen();
}


/*************************************************************************
 * Function Name: CLIENTMainServer::attachToGameServer
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
CLIENTMainServer::attachToGameServer()
{
  char *host;
  int port ;
  PKGameParameters parms ;

  stream_ >> &host >> port >> parms ;
  ntwrk_ -> attachToGameServer(host, port);
}


/*************************************************************************
 * Function Name: CLIENTMainServer::static_readException
 * Parameters: void *thus
 * Returns: void
 * Effects: 
 *************************************************************************/
void
CLIENTMainServer::static_readException(void *thus) 
{
  ((CLIENTMainServer*)thus)->readException();
}


/*************************************************************************
 * Function Name: CLIENTMainServer::readException
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
CLIENTMainServer::readException()
{
  client_->error("The server hung up or something");
  ntwrk_->hangup();
  errno_ = EREADNONE;
}


