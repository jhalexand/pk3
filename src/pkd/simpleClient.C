/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: bh                                                  */
/*    FILE: simpleClient.C                                      */
/*    ASGN:                                                     */
/*    DATE: Sat Apr 19 18:42:05 1997                            */
/****************************************************************/


#include "bh_defs.h"
#include <iostream.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

#include "Exception.h"
#include "NETReadWriteSocket.h"

void pipeHandler(int signo) {
  cout << "Broken pipe: the server must have hung up" << endl;
  exit(0);
}

void killHandler(int signo) {
  cout << "Killed with signal " << signo << "; dying" << endl;
  exit(0);
}

void sendString(const char *buf) ;
void sendQuit() ;
void sendKill() ;

void getString();
void getQuit();

NETReadWriteSocket *socket_;

int main(int argc, char** argv) {
  signal(SIGPIPE, pipeHandler);
  signal(SIGINT,  killHandler);
  signal(SIGHUP,  killHandler);
  signal(SIGTERM, killHandler);

  if(argc < 3) {
    printf("usage: simpleClient <server-node> <server-port>\n");
    exit(1);
  }
  
  char buf[STRLEN];
  int request ;
  socket_ = new NETReadWriteSocket(argv[1],atoi(argv[2]));
  dprintf(("Connected to server on %s:%s\n", argv[1], argv[2]));
  
  try {
    while(1) {
      struct pollfd fds[2];
      fds[0].fd = 0;
      fds[0].events = POLLIN;
      fds[1].fd = socket_->fileDescriptor();
      fds[1].events = POLLIN;
      poll(fds, 2, -1); // poll forever between stdin and net

      dprintf(("activity detected; figuring out what it is\n"));

      if(fds[0].revents & POLLIN) {
        cin.getline(buf, STRLEN, '\n');
        if(!strcasecmp(buf, "bye")) {
  	  sendQuit();
        }
        if(!strcasecmp(buf, "kill all")) {
 	  sendKill();
        }
        else {
	  sendString(buf);
        }
      }
      else if(fds[1].revents & POLLIN) {
        int rq = socket_->getInt();
        dprintf(("responding to request %d:", rq));
        if(rq == 0) {
	  getQuit();
        }
        else {
	  getString();
        }
      }
    }
  } catch (Exception& xcp) {
    xcp.print();
    delete socket_;
    return xcp.errno();
  }
}


void sendString(const char *buf) {
  dprintf(("sending request 4: send-string (\"%s\")\n", buf));
  socket_->startRequest(4);
  socket_->sendString(buf);
  socket_->endRequest();
}

void sendQuit() {
  dprintf(("sending request 0: hangup\n"));
  socket_->startRequest(0);
  socket_->endRequest();
}

void sendKill() {
  dprintf(("sending request 8: kill server and clients\n"));
  socket_->startRequest(8);
  socket_->endRequest();
}

void getString() {
  char buf[STRLEN];
  socket_->getString(buf);
  dprintf((" ack-string (\"%s\")\n", buf));
}
  
void getQuit() {
  dprintf((" ack-hangup\n"));
  throw Exception(1, "hanging up");
}
