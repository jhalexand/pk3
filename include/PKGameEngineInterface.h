/*************************************************************************/
/*    NAME: Elaine Chen                                                  */
/*    ACCT: eyc                                                          */
/*    FILE: PKGameEngineInterface.h                                      */
/*    DATE: Thu Apr 24 21:24:52 1997                                     */
/*************************************************************************/


#ifndef PKGAMEENGINEINTERFACE_HEADER
#define PKGAMEENGINEINTERFACE_HEADER

#include <PKids.h>
class PKRoundEngine;
class PKGameServerInterface;

class PKGameEngineInterface {
public:
    PKGameEngineInterface(PKGameServerInterface* server,
					 int numplayers,
					 PKTypeID players[],
					 PKKombatKodeID kode);
    ~PKGameEngineInterface();

    void mainloop();

    void handleAction(int playerNum, PKActionID action);
    void handleHangup(int playerNum);

private:
    PKRoundEngine* _roundEngine;

};

#endif
