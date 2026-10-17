/*************************************************************************/
/*    NAME: Elaine Chen                                                  */
/*    ACCT: eyc                                                          */
/*    FILE: PKGameEngine.h                                               */
/*    DATE: Thu Apr 24 21:58:55 1997                                     */
/*************************************************************************/


#ifndef PKGAMEENGINE_HEADER
#define PKGAMEENGINE_HEADER


#include <PKids.h>
#include <PKGameClasses.h>
#include "GEContainer.h"
#include "GEEvent.h"
#include "GEWall.h"
#include <PKGameServerInterface.h>
#include <PKPhysicsInterface.h>

#include <rw/gqueue.h>

class PKGameStatus;
class GEGameObject;
class PKGameServerInterface;
class PKPhysics;
class GEPlayer;

declare(RWGQueue, GEEvent)

class PKGameEngine {
public:

    //interface to outside
    PKGameEngine(PKGameServerInterface* server,
			  int numplayers,
			  PKTypeID players[],
			  PKKombatKodeID kode);
    ~PKGameEngine();

    int mainloop();
    void handleAction(int playerNum, PKActionID action);
    void handleHangup(int playerNum);

    //internal interface for objects related to the Game Engine
    void broadcastUpdate(GEGameObject* thing);
    void broadcastAddObject(GEGameObject* thing);
    void broadcastRemoveObject(PKID id);
    void broadcastAnimateObject(PKID id, PKAnimID animID);
    void broadcastPlaySound(PKSoundID soundID);

    void addObject(GEGameObject* thing);
    void removeObject(PKID ID); 
    void addEvent(GEEvent* newevent);
    void changeGameStatus (int playernum, int newlife);

    GEPlayer *choosePlayer(int team);

    //accessors
    GEContainer* getTeam1List() {return _team1;}
    GEContainer* getTeam2List() {return _team2;}
    GEContainer* getWallList() {return _walls;}
    GEContainer* getProjList() {return _projectiles;}
    PKPhysicsInterface* getPhysics() {return _physics;}
    
protected:
    
    //counts, objects and references
    int _numplayers;
    int _nextfree;                  //index to next available ID space
    static int _maxNumObjs;         //make sure <= _objArray declaration
    GEGameObject* _objArray[100];
    PKGameServerInterface* _server;
    RWGQueue(GEEvent) _eventList;
    PKPhysicsInterface* _physics;

    // Game status: 
    PKGameStatus _game_status;
  
    //lists
    GEContainer* _team1;
    GEContainer* _team2;
    GEContainer* _walls;
    GEContainer* _projectiles;

    //protected methods

    //used in mainloop
    void addServerEvents();
    void processEventList();
    void updateObjects();      
    void checkIntersections();
    void checkEndRound(int& endround);

    //accessory methods
    void startGame();
    void endGame();
    void findNextFree();
    void addPlayers(PKTypeID* players, int numplayers);
    void addWall(GEWallSide side);
    void processKombatKode(PKKombatKodeID kode);
    GEPlayer* findPlayer(int playerNum);
    
};

#endif
