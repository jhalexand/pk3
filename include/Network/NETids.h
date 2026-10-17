/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: bh                                                  */
/*    FILE: NETRequestID.h                                      */
/*    ASGN:                                                     */
/*    DATE: Mon Apr 21 16:41:12 1997                            */
/****************************************************************/


#ifndef NETID_HEADER
#define NETID_HEADER

class NETPort {
public:
  enum NETPortID {
    GAME_SERVER_LISTEN=45880
  };
};

class NETRequest {
public:
  enum NETRequestID {
    // identify the kind of application you are
    CONNECT_AS_CLIENT=1, // (char *name, char *acct, char *hostname)
    CONNECT_AS_GAMESERVER, // (int gameID, char *host, int port)
    CONNECT_AS_GS_CLIENT, // (int playerNum)

    // return some info that whoever just connected would like
    CONNECT_AS_CLIENT_ACK, // (int userID)
    CONNECT_AS_GAMESERVER_ACK, // (PKGameParamteters parms)
    CONNECT_AS_GS_CLIENT_ACK, // (PKGameParameters parms)

    // warn the other end you're hanging up (issued by anyone anytime)
    HANGUP, // ()

    // issued by server to clients before game setup
    ADD_USER, // (int userID, char *user, char *acct, char *host)
    REMOVE_USER, // (int userID)
    ADD_GAME, // (int gameID, PKGameProgress prog)
    REMOVE_GAME, // (int gameID)


    // issued by clients to main server before game setup
    CREATE_GAME, // (int userID)
    JOIN_GAME, // (int userID, int gameID)

    // issued by server to clients to start game setup
    CREATE_GAME_ACK, // (int gameID, int playerNum, PKGameParameters parms)
    JOIN_GAME_ACK, // (int playerNum, PKGameParameters parms)
    JOIN_GAME_REJECT_ACK, // (int errnum)
    ADD_AI_PLAYER, // (int playerNum, int aiLevel)

    // issued by server to clients to keep setup screen accurate
    ADD_PLAYER, // (int playerNum, PKPlayerInfo player)
    REMOVE_PLAYER, // (int playerNum)

    // issued by clients to main server during game setup
    // all have as first parameters (int gameID, int thisPlayerNum)
    SET_TEAM, // (int teamID)
    SET_PADDLE, // (PKTypeID paddleID)
    SEND_KOMBAT_KODE, // (char *string)
    SEND_CHAT_TEXT, // (char *string)
    REJECT_PLAYER, // (int playerID)
    LEAVE_GAME, // ()

    // issued by server to clients during game setup to
    // broadcast the requests above
    SET_TEAM_ACK, // (int playerNum, int teamID)
    SET_PADDLE_ACK, // (int playerNum, PKTypeID paddleNum)
    SEND_KOMBAT_KODE_ACK, // (int playerNum, char *string)
    SEND_CHAT_TEXT_ACK, // (int playerNum, char *string)
    REJECT_PLAYER_ACK, // (int playerNum)


    // issued by client that created game to actually start playing 
    // or cancel the game, and when the game ends
    CANCEL_GAME, // (int gameID)
    START_GAME, // (int gameID)

    // issued by mainserver to client that created game to create the game
    // server host and port are the main server host/port
    START_GAME_ACK, // (PKGameParameters parms, char *host, int port)

    // issued by gameserver to clients to actually start playing or cancel
    CANCEL_GAME_ACK, // ()
    ATTACH_TO_GAME_SERVER, // (char *host, int port, PKGameParameters parms)

    // issued by clients to tell the game server the graphics have loaded
    CLIENT_READY, // ()

    // issued by gameserver to clients when all clients are ready
    DO_START_PLAY, // ()

    // issued by client to game server during game
    HANDLE_ACTION, // (int playerNum, PKActionID action)

    // issued by game server to clients during game
    UPDATE, // (PKObject changedObject)
    GAME_STATUS, // (PKGameStatus newStatus)
    ADD_OBJECT, // (PKID id, PKTypeID type)
    REMOVE_OBJECT, // (PKID id)
    ANIMATE_OBJECT, // (PKID id, PKAnimationID anim)
    PLAY_SOUND, // (PKSoundID id)
    PAUSE_GAME,  // (boolean pause)

    // issued by gameserver to mainserver at end of game
    END_GAME // ()
  } ;
} ;
#endif
