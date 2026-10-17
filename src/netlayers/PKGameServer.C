/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: bh                                                  */
/*    FILE: PKGameServer.C                                      */
/*    ASGN:                                                     */
/*    DATE: Thu May  1 04:17:15 1997                            */
/****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "PKGameServerInterface.h"
#include "PKGameServerImplementation.h"
#include "PKGameEngineInterface.h"
#include <debug.h>
#include <Exception.h>
#include <Network/NetworkException.h>

int main(int argc, char **argv) {
  // usage: pkgameserver <host> <port> <gameID>
  dprintf(("welcome to the friendly neighbourhood %s\n", argv[0]));
  
  if(argc!=4) {
    fprintf(stderr, "usage: %s <host> <port> <gameID>\n", argv[0]);
    fprintf(stderr, "where host+port are the main server's gameserver port\n");
    fprintf(stderr, "you sent: ");
    for(int i=0; i<argc; i++) {
      fprintf(stderr,"%s ", argv[i]);
    }
    fprintf(stderr, "\n");
    exit(argc);
  }

  PKGameServerInterface *server_ ;
  PKGameEngineInterface *engine_ ;

  // this blocks until all the clients have connected
  server_ = new PKGameServerInterface(argv[1], atoi(argv[2]), atoi(argv[3]));

  // start up the game engine
  engine_ = new PKGameEngineInterface(server_,
				      server_->numPlayers(),
				      server_->paddles(),
				      server_->kode());
  server_->init(engine_);

  // start looping
  engine_->mainloop();
  
  delete engine_;
  delete server_;
}
