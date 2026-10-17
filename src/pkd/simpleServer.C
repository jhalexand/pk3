/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: bh                                                  */
/*    FILE: simpleServer.C                                      */
/*    ASGN:                                                     */
/*    DATE: Sat Apr 19 18:45:36 1997                            */
/****************************************************************/



#include "bh_defs.h"
#include <iostream.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>

#include "Exception.h"
#include "NETListenSocket.h"
#include "NETReadWriteSocket.h"

void pipeHandler(int signo) {
  dprintf(("Broken pipe: the client must have hung up\n"));
  throw Exception(0);
}

void killHandler(int signo) {
  dprintf(("Killed with signal %d; dying\n", signo));
  throw Exception(0);
}

const int NUM_CLIENTS = 10 ;
int numClients = 0;
NETReadWriteSocket *sockets[NUM_CLIENTS];

void openConnection(NETListenSocket *ear) ;
void respondToRequest(int fd);


int main(int argc, char** argv) {
  try {
    for(int i=0; i<NUM_CLIENTS; i++) { sockets[i] = null; }

    signal(SIGPIPE, pipeHandler);
    signal(SIGINT,  killHandler);
    signal(SIGHUP,  killHandler);
    signal(SIGTERM, killHandler);

    if(argc < 2) {
      dprintf(("usage: simpleServer <port>\n"));
      dprintf(("for the port, specify anything ~4000 - 64k\n"));
      throw Exception(1);
    }

    char buf[STRLEN];
    int request ;
    NETListenSocket ear(atoi(argv[1]),NUM_CLIENTS-5);
    dprintf(("Opened listening socket on port %d\n", ear.portNumber()));


    while(1) {
      struct pollfd fds[NUM_CLIENTS+1];
      int topFd = 0;

      for(int i=0; i<NUM_CLIENTS; i++) {
	if(sockets[i]) {
	  fds[topFd].fd = sockets[i]->fileDescriptor();
	  fds[topFd].events = POLLIN ;
	  dprintf(("adding poll for fd %d\n", fds[topFd].fd));
	  topFd++;
	}
      }
      fds[numClients].fd = ear.fileDescriptor();
      fds[numClients].events = POLLIN;

      dprintf(("polling among %d clients and the ear\n", numClients));
      poll(fds, numClients+1, -1); // poll forever

      dprintf(("activity detected; figuring out what it is\n"));

      // some activity changes the number of clients; make sure
      // we don't go out of bounds
      int oldClients = numClients ;

      // check each open connection for activity
      for(/*int*/ i=0; i<oldClients; i++) {
	if(fds[i].revents & POLLIN) {
	    respondToRequest(fds[i].fd);
	}
      }

      // check if a new connection is pending
      if(fds[oldClients].revents & POLLIN) {
	openConnection(&ear);
      }


      // loop again
    }
  } catch(Exception& xcp) {
    xcp.print();
    return xcp.errno(); }
}


void openConnection(NETListenSocket *ear) {
  dprintf(("ear has a connection pending; dealing with it\n"));
  if(numClients>=NUM_CLIENTS) {
    dprintf(("too many clients; not dealing yet"));
  }
  else {
    dprintf(("opening a new ReadWriteSocket..."));
    // figure out where it fits
    for(int i=0; i<NUM_CLIENTS; i++) {
      if(!sockets[i]) {
	numClients++;
	sockets[i] = ear->accept();
	dprintf((" done!\n"));
	return ;
      } // else there's already a socket there
    }
  }
}


void respondToRequest(int fd) {
  dprintf(("responding to request on fd %d\n", fd));
  NETReadWriteSocket *rwSock;
  for(int i=0; i<NUM_CLIENTS; i++) {
    if(sockets[i] && (sockets[i]->fileDescriptor() == fd)) {
      rwSock = sockets[i];
      break ;
    }
  }

  int request = rwSock->getInt();
  dprintf(("got request %d", request));
  if(request==0) {
    dprintf((" (quit)\n"));
    rwSock->startRequest(0);
    rwSock->endRequest();
    delete rwSock;
    sockets[i] = null ;
    numClients--;
  }
  else if (request==4) {
    char buf[STRLEN];
    rwSock->getString(buf);
    dprintf((" (send-string: \"%s\"); acknowledging\n", buf));
    rwSock->startRequest(request+1);
    rwSock->sendString(buf);
    rwSock->endRequest();
  }
  else if (request==8) {
    dprintf((" (clean-up); killing clients and self\n"));
    for(int i=0; i<NUM_CLIENTS; i++) {
		if(sockets[i]) {
			sockets[i]->startRequest(0);
			sockets[i]->endRequest();
			delete sockets[i];
			sockets[i] = null;
			numClients--;
		}
    }
    exit(0);
  }
}
