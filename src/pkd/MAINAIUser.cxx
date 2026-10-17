/*************************************************************************
 *    NAME: Jeffrey Alexander
 *    USER: jla
 *    FILE: MAINAIUser.cxx
 *    DATE: Sun Apr 27 21:00:23 US/Eastern 1997
 *************************************************************************/
#include "MAINAIUser.h"
#include "MAINGame.h"
#include "MAINServer.h"
#include "MAINdefs.h"
#include <debug.h>
#include <Network/NETReadWriteSocket.h>
#include <Network/NETids.h>
#include <Network/NETStream.h>
#include <PKids.h>
#include <PKGameClasses.h>
#include <PKConstants.h>
#include <sys/types.h>
#include <sys/utsname.h>

#if (defined(USEDPRINTF)) || (!defined(NDEBUG) && !defined(NODPRINTF))
#define dprintUser(str) { printf("[MAINUser %x] ", getID()); dprintf(str); }
#else
#define dprintUser(str)
#endif

/*************************************************************************/
/* Function Name: MAINAIUser::MAINAIUser                                 */
/* Parameters: NETReadWriteSocket *socket, int userID                    */
/* Effects:                                                              */
/*************************************************************************/

MAINAIUser::MAINAIUser(int playerNum, MAINServer *server)
{
    _socket = null;
    _server = server;
    setPlayerNumber(playerNum);
    setTeam(1);
    setPaddle(PK_TYPE_CYRAX_1);
    setAILevel(PK_AI_DUMB);
    setUsername("dumb ai player");
    setAccount ("computer");
    setHostname("somewhere");
    dprintUser(("initialized AI user\n"));
}

/*************************************************************************/
/* Function Name: MAINAIUser::userSetTeam                                */
/* Parameters: int whichUser, int whichTeam                              */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
    void
MAINAIUser::userSetTeam(int whichUser, int whichTeam)
{
    if(whichUser == playerNumber()) {
        setTeam(whichTeam);
    }
}

/*************************************************************************/
/* Function Name: MAINAIUser::userSetPaddle                                */
/* Parameters: int whichUser, PKTypeID whichPaddle                       */
/* Returns: void                                                         */
/* Effects:                                                              */
/*************************************************************************/
    void
MAINAIUser::userSetPaddle(int whichUser, PKTypeID whichPaddle)
{
    if(whichUser == playerNumber()) {
        setPaddle(whichPaddle);
    }
}




