/*************************************************************************
 *    NAME: Benoit Hudson
 *    USER: bh
 *    FILE: PKGameServerImplementation.C
 *    DATE: Mon Apr 21  0:18:02 US/Eastern 1997
 *************************************************************************/
#include "PKGameServerImplementation.h"

#include <debug.h>
#include <MAINdefs.h>
#include <Network/NETListenSocket.h>
#include <Network/NETReadWriteSocket.h>
#include <Network/NETRequestID.h>
#include <Network/NETStream.h>
#include <Network/NetworkException.h>
#include <PKConstants.h>
#include <PKGameClasses.h>
#include <PKGameEngineInterface.h>
#include <PKObject.h>
#include <PKPaths.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <unistd.h> // dup2

    void
PKGameServerImplementation::checkErrno(PKGameServerConnection& connection)
{
    switch(connection.errno()) {
        case ENODATA:
            {
                handleHangup(connection.socketNum()) ;
                return ;
            } break ;
        case EPIPE:
            {
                handleHangup(connection.socketNum()) ;
                return ;
            } break ;
    }
}


/*************************************************************************
 * Function Name: PKGameServerImplementation::PKGameServerImplementation
 * Parameters: 
 * Returns: void
 * Effects: hack: just set all clients to null
 *************************************************************************/

PKGameServerImplementation::PKGameServerImplementation(const char *host,
        int port, int gameID)
{
    int reqnum ;
    NETListenSocket *ear ;
    PKGameParameters parms ;

    struct utsname unstruct;
    uname(&unstruct);

    ear = new NETListenSocket(0, parms.numPlayers()); // find a port

    // connect to the gameserver
    server_.init(host, port, -1);
    server_.startRequest(NETRequest::CONNECT_AS_GAMESERVER);
    server_ << gameID;
    server_ << unstruct.nodename;
    server_ << ear->portNumber();
    server_.endRequest();
    checkErrno(server_);

    // get its acknowledgment (argument is PKGameParameters)

    dprintf(("game server waiting for ack from main server\n"));
    reqnum = server_.get();
    if(reqnum!=NETRequest::CONNECT_AS_GAMESERVER_ACK) {
        fprintf(stderr, "Main server responded with wrong reqnum: %d\n", reqnum);
        exit(1);
    }

    server_ >> parms ;

    numClients_ = parms.numPlayers();

    // just debugging stuff
#if (defined(USEDPRINTF)) || (!defined(NDEBUG) && !defined(NODPRINTF))
    dprintf(("game parameters: %d players\n", parms.numPlayers()));
    dprintfLevelSkip(3);
    for(int i=0; i<parms.numPlayers(); i++) {
        PKPlayerInfo player = parms.players()[i];
        dprintf(("player %d (%s: %s): team %d, paddle %d, life %d\n",
                player.playerNumber(),
                player.aiLevel()==PK_AI_HUMAN ? "human" : "cpu",
                player.username() ? player.username() : "\"\"",
                player.team(), player.paddle(),
                player.life()));
    }
    dprintfLevelSkip(0);
#endif

    // initialize the streams and start listening for connections
    clients_ = new PKGameServerConnection[parms.numPlayers()];
#ifdef DEBUG
    for(i=0; i<parms.numPlayers(); i++) {
        clients_[i].attachTo(null, i);
    }
#endif



    // figure out exactly how many clients there really are,
    // spawn ai players (commented out the spawning)
    dprintf(("checking for clients\n"));
    int actualNumPlayers=0;
    for(i=0; i<parms.numPlayers(); i++) {
        if(parms.players(i).playerNumber()!=-1) {
            if(parms.players(i).aiLevel()!=PK_AI_HUMAN) {
                spawnAIClient(i, unstruct.nodename, ear->portNumber());
            }
            actualNumPlayers++;
        }
    }

    dprintf(("\n"));
    for(i=0; i<actualNumPlayers; i++) {
        dprintf(("waiting for connections from players (%d/%d here so far)\n",
                i, actualNumPlayers));

        // wait forever for a connection
        struct pollfd pfd;
        pfd.fd = ear->fileDescriptor();
        pfd.events = POLLIN;
        poll(&pfd, 1, -1);

        // got a connection; check and make sure it's a client.
        NETReadWriteSocket *newClient = ear->accept();
        reqnum = newClient->getInt();

        if(reqnum!=NETRequest::CONNECT_AS_GS_CLIENT) {
            // no, so kill it and don't count it as a player
            fprintf(stderr, "non-pk3 client attempted to connect; hanging up\n");
            delete newClient;
            i--; // don't count this as a player
        }
        else {
            int playerNumber = newClient->getInt();

            // yes, so now check and make sure it hasn't already been opened.
            if(clients_[playerNumber].attachedTo()) {
                dprintf(("rejecting connection from pk3 client %d: one already exists\n",
                        newClient->getInt()));
                delete newClient;
                i--; // don't count this as a player
            }
            // connection is free, so open the corresponding stream to it and get
            // more clients
            dprintf(("accepting connection from pk3 client %d and acknowledging\n",
                    playerNumber));
            clients_[playerNumber].attachTo(newClient, playerNumber);
            clients_[playerNumber].startRequest(NETRequest::CONNECT_AS_GS_CLIENT_ACK);
            clients_[playerNumber] << parms;
            clients_[playerNumber].endRequest();
        }
    }

    // now wait for all the clients to be ready
    struct pollfd *pfd = new struct pollfd[parms.numPlayers()];
    for(/*int*/ i=0; i<parms.numPlayers(); i++) {
        pfd[i].fd = clients_[i].attachedTo() ?
            clients_[i].attachedTo()->fileDescriptor() : -1 ;
    }

    dprintf(("waiting for clients to be ready\n"));
    for(int numReady=0; numReady<actualNumPlayers;) {
        for(/*int*/ i=0; i<parms.numPlayers(); i++) {
            pfd[i].events = POLLIN;
        }
        poll(pfd, parms.numPlayers(), -1);

        for(/*int*/ i=0; i<parms.numPlayers(); i++) {
            if(pfd[i].revents & POLLIN) {
                if(clients_[i].get()==NETRequest::CLIENT_READY) {
                    dprintf(("client %d is now ready\n", i));
                    pfd[i].fd = -1 ;
                    numReady++;
                }
                else {
                    dprintf(("client %d did something stupid; dying\n", i));
                    throw Exception(1, "fucked up in waiting for ready\n");
                }
            }
        } // for checking poll
    } // for waiting for clients
    delete [] pfd ;

    // now tell the clients to actually start
    dprintf(("starting connections\n"));
    for(/*int*/ i=0; i<parms.numPlayers(); i++) {
        if(clients_[i].attachedTo()) {
            clients_[i].startRequest(NETRequest::DO_START_PLAY);
            clients_[i].endRequest();
            checkErrno(clients_[i]);
        }
    }

    // finally, close the ear and set the values the game engine needs
    delete ear;

    paddles_ = new PKTypeID[numClients_];
    for(/*int*/ i=0; i<numClients_; i++) {
        paddles_[i] = parms.players()[i].paddle();
    }

    kode_ = parms.kode();
}


/*************************************************************************
 * Function Name: PKGameServerImplementation::~PKGameServerImplementation
 * Parameters: 
 * Returns: void
 * Effects: close all open connections
 *************************************************************************/

PKGameServerImplementation::~PKGameServerImplementation()
{
    for(int i=0; i<numClients_; i++) {
        delete clients_[i].attachedTo();
        clients_[i].detach();
    }
    delete [] clients_;
    delete [] paddles_;
    delete server_.attachedTo();
    server_.detach();
}


/*************************************************************************
 * Function Name: PKGameServerImplementation::receive
 * Parameters: 
 * Returns: void
 * Effects: polls the network connections for activity; deals with any activity
 *************************************************************************/
    void
PKGameServerImplementation::receive() 
{
    struct pollfd fds[MAX_PLAYERS] ;
    for(int i=0; i<numClients_; i++) {
        fds[i].revents = 0;
        if(clients_[i].attachedTo()) {
            fds[i].fd = clients_[i].attachedTo()->fileDescriptor();
            fds[i].events = POLLIN ;
        }
        else { // client has hung up
            // fill the space to keep the correspondance of indices;
            // the poll(2) page claims that a negative fd is ignored
            fds[i].fd = -1;
        }
    }

    poll(fds, numClients_, 0) ; // just poll; don't wait

    for(/*int*/ i=0; i<numClients_; i++) {
        if(fds[i].revents & POLLIN) {
            // deal with the activity on that socket
            int request ;
            clients_[i] >> request ;
            if(clients_[i].errno()) break ;
            switch(request) {
                case NETRequest::HANGUP :
                    {
                        handleHangup(i);
                        break;
                    }
                case NETRequest::HANDLE_ACTION :
                    {
                        handleAction(i);
                        break;
                    }
                default:
                    {
                        unimplemented("Default action in PKGameServerImplementation::receive()");
                    }
            } // switch
        } // if POLLIN
    } // for

    for(i=0; i<numClients_; i++) {
        checkErrno(clients_[i]);
    }
} // receive()


/*************************************************************************
 * Function Name: PKGameServerImplementation::broadcastUpdate
 * Parameters: int numElements, PKObject[]
 * Returns: void
 * Effects: Broadcasts an update to all clients.
 *************************************************************************/
    void
PKGameServerImplementation::broadcastUpdate(PKObject& object)
{
    for(int i=0; i<numClients_; i++) {
        if(clients_[i].attachedTo()) {
            clients_[i].startRequest(NETRequest::UPDATE);
            clients_[i] << object ;
            clients_[i].endRequest();
            checkErrno(clients_[i]);
        }
    }
}


/*************************************************************************
 * Function Name: PKGameServerImplementation::broadcastGameStatus
 * Parameters: PKGameStatus&
 * Returns: void
 * Effects: Broadcasts an update of the game status to all clients
 *************************************************************************/
    void
PKGameServerImplementation::broadcastGameStatus(PKGameStatus& status)
{
    for(int i=0; i<numClients_; i++) {
        if(clients_[i].attachedTo()) {
            clients_[i].startRequest(NETRequest::GAME_STATUS);
            clients_[i] << status ;
            clients_[i].endRequest();
            checkErrno(clients_[i]);
        }
    }
}


/*************************************************************************
 * Function Name: PKGameServerImplementation::broadcastAddObject
 * Parameters: PKID ID, PKTypeID
 * Returns: void
 * Effects: 
 *************************************************************************/
    void
PKGameServerImplementation::broadcastAddObject(PKObject& toAdd)
{
    for(int i=0; i<numClients_; i++) {
        if(clients_[i].attachedTo()) {
            clients_[i].startRequest(NETRequest::ADD_OBJECT);
            clients_[i] << toAdd ;
            clients_[i].endRequest();
            checkErrno(clients_[i]);
        }
    }
}


/*************************************************************************
 * Function Name: PKGameServerImplementation::broadcastRemoveObject
 * Parameters: PKID ID
 * Returns: void
 * Effects: 
 *************************************************************************/
    void
PKGameServerImplementation::broadcastRemoveObject(PKID id)
{
    for(int i=0; i<numClients_; i++) {
        if(clients_[i].attachedTo()) {
            clients_[i].startRequest(NETRequest::REMOVE_OBJECT);
            clients_[i] << id ;
            clients_[i].endRequest();
            checkErrno(clients_[i]);
        }
    }
}


/*************************************************************************
 * Function Name: PKGameServerImplementation::broadcastAnimateObject
 * Parameters: PKObject&, PKAnimationID
 * Returns: void
 * Effects: 
 *************************************************************************/
    void
PKGameServerImplementation::broadcastAnimateObject(PKID id, PKAnimID anim)
{
    for(int i=0; i<numClients_; i++) {
        if(clients_[i].attachedTo()) {
            clients_[i].startRequest(NETRequest::ANIMATE_OBJECT);
            clients_[i] << id << anim ;
            clients_[i].endRequest();
            checkErrno(clients_[i]);
        }
    }
}


/*************************************************************************
 * Function Name: PKGameServerImplementation::broadcastPlaySound
 * Parameters: PKSoundID
 * Returns: void
 * Effects: 
 *************************************************************************/
    void
PKGameServerImplementation::broadcastPlaySound(PKSoundID id)
{
    for(int i=0; i<numClients_; i++) {
        if(clients_[i].attachedTo()) {
            clients_[i].startRequest(NETRequest::PLAY_SOUND);
            clients_[i] << id;
            clients_[i].endRequest();
            checkErrno(clients_[i]);
        }
    }
}


/*************************************************************************
 * Function Name: PKGameServerImplementation::broadcastPauseGame
 * Parameters: PKSoundID
 * Returns: void
 * Effects: 
 *************************************************************************/
    void
PKGameServerImplementation::broadcastPauseGame(boolean p)
{
    for(int i=0; i<numClients_; i++) {
        if(clients_[i].attachedTo()) {
            clients_[i].startRequest(NETRequest::PAUSE_GAME);
            clients_[i] << p;
            clients_[i].endRequest();
            checkErrno(clients_[i]);
        }
    }
}


/*************************************************************************
 * Function Name: PKGameServerImplementation::broadcastEndGame
 * Parameters: PKSoundID
 * Returns: void
 * Effects: 
 *************************************************************************/
    void
PKGameServerImplementation::broadcastEndGame()
{
    server_.startRequest(NETRequest::END_GAME);
    server_.endRequest();
    checkErrno(server_);
}


/*************************************************************************
 * Function Name: PKGameServerImplementation::handleHangup
 * Parameters: int socketNum
 * Returns: void
 * Effects: 
 *************************************************************************/
    void
PKGameServerImplementation::handleHangup(int socketNum)
{
    if(socketNum==-1) {
        delete server_.attachedTo();
        server_.detach();
    }
    else {
        delete clients_[socketNum].attachedTo() ;
        clients_[socketNum].detach();
        engine_->handleHangup(socketNum);
    }
}


/*************************************************************************
 * Function Name: PKGameServerImplementation::handleAction
 * Parameters: int socketNum
 * Returns: void
 * Effects: 
 *************************************************************************/
    void
PKGameServerImplementation::handleAction(int socketNum)
{
    int playerNum ;
    PKActionID id ;

    clients_[socketNum] >> playerNum >> id ;

    engine_->handleAction(playerNum, id);
    checkErrno(clients_[socketNum]);
}



/*************************************************************************
 * Function Name: PKGameServerImplementation::spawnAIClient
 * Parameters: int playerNum, unsigned short port
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKGameServerImplementation::spawnAIClient(int playerNum,
        const char *host, unsigned short port)
{
    dprintf(("game server spawning player %d as AI client\n", playerNum));

    pid_t child = fork() ;
    if(child<0) {
        perror("Fork failed");
        exit(1);
    }
    else if(child==0) {
        // we're the child; exec
        char playerNumS[STRLEN];
        char portS[STRLEN];
        char aiout[STRLEN];
        char aierr[STRLEN];
        char execname[STRLEN];

        sprintf(playerNumS, "%d", playerNum);
        sprintf(portS, "%d", port);

        sprintf(aiout, "/tmp/aiclient%d", getpid());

        int fd = open(aiout, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if(fd!=1) dup2(fd, 1);
        if(fd!=2) dup2(fd, 2);
        if(fd!=1 && fd!=2) close(fd);

        sprintf(execname, "%s/pkaiclient", PKBINPATH);

        execl(execname, "pkaiclient",
                host, portS, playerNumS, null);
        perror("exec failed");
        exit(1);      
    }
    else {
        // we're the parent
        dprintf(("Forked process %d as an ai client.\n", child));
    }
}
