/*************************************************************************
 *    NAME: Benoit Hudson
 *    USER: bh
 *    FILE: CLIENTGameServer.C
 *    DATE: Thu May  1  0:35:11 US/Eastern 1997
 *************************************************************************/
#include "CLIENTGameServer.h"

#include "CLIENTMainServer.h"
#include <Network/NETReadWriteSocket.h>
#include <Network/NETids.h>
#include <PKids.h>
#include <PKClientInterface.h>
#include "PKClientNetworkImplementation.h"
#include <sys/time.h>

// a macro to check errno_; if there is an error condition, deal with it
// and return.
#define checkErrno() \
{ \
    switch(errno_) { \
        case ENODATA: \
                      { \
                          handleNoData() ; \
                              return ; \
                      } break ; \
        case EPIPE: \
                    { \
                        handlePipe() ; \
                            return ; \
                    } break ; \
    } \
}

    void
CLIENTGameServer::handleNoData()
{
    dprintf(("C->GAME: no data in last read; hanging up\n"));
    hangup() ;
}

    void
CLIENTGameServer::handlePipe()
{
    dprintf(("C->GAME: broken pipe in last write; hanging up\n"));
    hangup() ;
}



/*************************************************************************
 * Function Name: CLIENTGameServer::CLIENTGameServer
 * Parameters: PKClientInterface* client, XtAppContext app, char *hostname, int port, char *name, char *acct, char *local
 * Effects: 
 *************************************************************************/

CLIENTGameServer::CLIENTGameServer(PKClientInterface* client, 
        XtAppContext app, 
        const char *hostname, int port, 
        int playerNum, PKClientNetworkImplementation *ntwrk)
{
    errno_     = 0 ;
    paused_    = true;
    playerNum_ = playerNum;
    client_    = client ;
    ntwrk_     = ntwrk;

    NETReadWriteSocket *socket = new NETReadWriteSocket(hostname, port);
    stream_.attachTo(socket);
    stream_.attachedTo()->setXcpHandler(NETERR::READ_NONE,
            CLIENTGameServer::static_readException,
            this);
    stream_.attachedTo()->setXcpHandler(NETERR::READ_TOO_LITTLE,
            NETReadWriteSocket::ignore,
            null);
    stream_.attachedTo()->setXcpHandler(NETERR::SIGPIPE_RCVD,
            CLIENTGameServer::static_brokenPipe,
            this);

    dprintf(("C->GAME: connecting as client %d\n", playerNum_));
    stream_.startRequest(NETRequest::CONNECT_AS_GS_CLIENT);
    stream_ << playerNum_;
    stream_.endRequest();

    checkErrno() ;

    callbackID_ = XtAppAddInput(app, stream_.attachedTo()->fileDescriptor(),
            (void*)XtInputReadMask,
            CLIENTGameServer::static_receive, this);
}


/*************************************************************************
 * Function Name: CLIENTGameServer::~CLIENTGameServer
 * Parameters: 
 * Effects: 
 *************************************************************************/

CLIENTGameServer::~CLIENTGameServer()
{
    delete stream_.attachedTo();
}


/*************************************************************************
 * Function Name: CLIENTGameServer::ready
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
    void
CLIENTGameServer::ready()
{
    stream_.startRequest(NETRequest::CLIENT_READY);
    stream_.endRequest();

    checkErrno() ;
}


/*************************************************************************
 * Function Name: CLIENTGameServer::receive
 * Parameters: 
 * Returns: void
 * Effects: receive a packet; if an error occurs, a message will be printed,
 *          the client will return to the main screen, and errno_ will be set.
 *************************************************************************/
    void
CLIENTGameServer::receive()
{
    int request ;
    request = stream_.get();
    checkErrno() ;

    switch(request) {
        case NETRequest::CONNECT_AS_GS_CLIENT_ACK: connectAck(); break;
        case NETRequest::HANGUP: hangup(); break;
        case NETRequest::UPDATE: update(); break;
        case NETRequest::GAME_STATUS: gameStatus(); break;
        case NETRequest::ADD_OBJECT: addObject(); break;
        case NETRequest::REMOVE_OBJECT: removeObject(); break;
        case NETRequest::ANIMATE_OBJECT: animateObject(); break ;
        case NETRequest::PLAY_SOUND: playSound(); break;
        case NETRequest::DO_START_PLAY: doStartPlay(); break;
        case NETRequest::PAUSE_GAME: pauseGame(); break;
        default: 
          {
            dprintf(("C<-GAME: invalid request %d (0x%x)\n", request, request));
            char buf[STRLEN];
            sprintf(buf, "Invalid request 0x%x sent from gameserver", request);
            client_->error(buf); break;
          }
    }
}


/*************************************************************************
 * Function Name: CLIENTGameServer::hangup
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
    void
CLIENTGameServer::hangup()
{
    dprintf(("C->GAME: hanging up from game server\n"));
    XtRemoveInput(callbackID_);
    stream_.startRequest(NETRequest::HANGUP);
    stream_.endRequest(); // may cause a handled SIGPIPE; that's ok
    delete stream_.attachedTo();
    stream_.release();
    errno_ = 0 ;
    ntwrk_->endGame() ;
}


/*************************************************************************
 * Function Name: CLIENTGameServer::sendAction
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
    void
CLIENTGameServer::sendAction(PKActionID id)
{
    dprintf(("C->GAME: Sending action %d\n", id));
    if(paused_ && id != PK_ACTION_UNPAUSE) { 
        dprintf(("\t(ignored because paused)\n")); 
        return; 
    }

    stream_.startRequest(NETRequest::HANDLE_ACTION);
    stream_ << playerNum_ << id ;
    stream_.endRequest();
    checkErrno() ;
}






/*************************************************************************
 * Function Name: CLIENTGameServer::update
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
    void
CLIENTGameServer::update()
{
    PKObject obj ;
    stream_ >> obj;

    checkErrno() ;

    client_->update(obj);
}


/*************************************************************************
 * Function Name: CLIENTGameServer::gameStatus
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
    void
CLIENTGameServer::gameStatus()
{
    PKGameStatus status;
    stream_ >> status;

    checkErrno() ;

    client_->gameStatus(status);
}


/*************************************************************************
 * Function Name: CLIENTGameServer::addObject
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
    void
CLIENTGameServer::addObject()
{
    PKObject obj ;
    stream_ >> obj;

    checkErrno() ;

    client_->addObject(obj);
}


/*************************************************************************
 * Function Name: CLIENTGameServer::removeObject
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
    void
CLIENTGameServer::removeObject()
{
    PKID id ;
    stream_ >> id ;

    checkErrno() ;

    client_->removeObject(id);
}


/*************************************************************************
 * Function Name: CLIENTGameServer::animateObject
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
    void
CLIENTGameServer::animateObject()
{
    PKID id ;
    PKAnimID anim ;
    stream_ >> id >> anim;

    checkErrno() ;

    client_->updateAnimation(id, anim);
}


/*************************************************************************
 * Function Name: CLIENTGameServer::playSound()
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
    void
CLIENTGameServer::playSound()
{
    PKSoundID id ;
    stream_ >> id ;

    checkErrno() ;

    client_->playSound(id);
}


/*************************************************************************
 * Function Name: CLIENTGameServer::connectAck
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
    void
CLIENTGameServer::connectAck()
{
    dprintf(("CLIENTGameServer::connectAck()\n"));
    PKGameParameters parms ;
    stream_ >> parms ;
    parms.debugPrint();

    checkErrno() ;

    client_->enterGamePlay(parms);
}


/*************************************************************************
 * Function Name: CLIENTGameServer::readException
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
    void
CLIENTGameServer::readException()
{
    errno_ = ENODATA ;
}


/*************************************************************************
 * Function Name: CLIENTGameServer::readException
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
    void
CLIENTGameServer::brokenPipe()
{
    errno_ = EPIPE ;
}


/*************************************************************************
 * Function Name: CLIENTGameServer::doStartPlay
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
    void
CLIENTGameServer::doStartPlay()
{
    dprintf(("CLIENTGameServer: actually starting play\n"));
    paused_ = false;
}


/*************************************************************************
 * Function Name: CLIENTGameServer::pauseGame
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
    void
CLIENTGameServer::pauseGame()
{

    stream_ >> paused_ ;
    dprintf(("CLIENTGameServer: %s game\n", paused_ ? "pausing": "unpausing"));

    client_->setPause(paused_);
}
