/*************************************************************************
 *    NAME: Elaine Chen
 *    USER: eyc
 *    FILE: PKGameEngine.cxx
 *    DATE: Thu Apr 24 22:15:31 US/Eastern 1997
 *************************************************************************/
#include "PKGameEngine.h"
#include "GEGameObject.h"
#include "GEPlayer.h"
#include "GEProjectile.h"
#include "GEBall.h"
#include "GELKLeftPlayer.h"
#include "GELKRightPlayer.h"
#include "GESZLeftPlayer.h"
#include "GESZRightPlayer.h"
#include "GERepLeftPlayer.h"
#include "GERepRightPlayer.h"
#include "GEJadeLeftPlayer.h"
#include "GEJadeRightPlayer.h"
#include "GECyraxLeftPlayer.h"
#include "GECyraxRightPlayer.h"
#include "GEKabalLeftPlayer.h"
#include "GEKabalRightPlayer.h"
#include <PKDimensions.h>
#include <sys/poll.h>
#include <stdlib.h>
#include <iostream.h>
#include <unistd.h>

/** MAKE SURE THIS VALUE IS EQUAL OR LESS THAN _objArray DECLARATION!!! **/
int PKGameEngine::_maxNumObjs = 100;


/*=======================================================================*/
/*=======================================================================*/
/*==                        Public Methods                             ==*/
/*=======================================================================*/
/*=======================================================================*/


/*************************************************************************
 * Function Name: PKGameEngine::PKGameEngine
 * Parameters: PKGameServerInterface* server,
               int numplayers,
			PKTypeID players[],
			PKKombatKodeID kode
 * Effects:
 *************************************************************************/

PKGameEngine::PKGameEngine(PKGameServerInterface* server,
					  int numplayers,
					  PKTypeID players[],
					  PKKombatKodeID kode)
    : _numplayers(numplayers), _server(server), _nextfree(0), _eventList(),
	 _game_status()
{
    //initialize physics
    _physics = new PKPhysicsInterface();

    //initialize lists
    _team1 = new GEContainer();
    _team2 = new GEContainer();
    _walls = new GEContainer();
    _projectiles = new GEContainer();

    //initialize object array
    for (int i = 0; i < _maxNumObjs; i++)
	   _objArray[i] = NULL;

    //add players
    addPlayers(players, numplayers);

    //add a ball
    PKPoint* ballpos = new PKPoint(PK_DIM_SCREEN_WIDTH/3,
							((PK_DIM_SCREEN_HEIGHT -
							 PK_DIM_WALL_TOP_Y)/2 +
							PK_DIM_WALL_TOP_Y));
    PKVector* ballvect = new PKVector(1, 0.33);

    *ballvect = (*ballvect)*PK_DIM_BALL_SPEED;

    GEBall* newball = new GEBall(_nextfree, PK_TYPE_BALL, _projectiles,
						   *ballpos, *ballvect, this);
    addObject(newball);
    delete ballpos;
    delete ballvect;
		
    //add walls
    addWall(GEWALL_TOP);
    addWall(GEWALL_RIGHT);
    addWall(GEWALL_BOTTOM);
    addWall(GEWALL_LEFT);

    broadcastPlaySound (PK_SOUND_FIGHT);

     //set up any game special features
    processKombatKode(kode);

}


/*************************************************************************
 * Function Name: PKGameEngine::~PKGameEngine
 * Parameters:
 * Effects:
 *************************************************************************/

PKGameEngine::~PKGameEngine()
{
    for (int i=0; i<_maxNumObjs; i++)
	   if (_objArray[i] != NULL)
		  delete _objArray[i];
    delete _team1;
    delete _team2;
    delete _walls;
    delete _projectiles;
}


/*************************************************************************
 * Function Name: PKGameEngine::mainloop
 * Parameters:
 * Returns: winner of the game
 * Effects:
 *************************************************************************/
int
PKGameEngine::mainloop()
{
    startGame();
    int endround = 0;
    while (! endround) {
        if(!_game_status.paused()) {
            addServerEvents();        //let server add events to event list
            processEventList();       //empty list and perform any events
            poll(0,0, 20);
            updateObjects();          //let physics update positions of objs
            checkIntersections();     //check intersections
            checkEndRound(endround);  //check for any end of game conditions
        }
        else {
            addServerEvents();
            poll(0,0, 100);
        }
    }
    processEventList();
    sleep(1);
    addServerEvents(); // Clear out anything waiting on the network
    endGame() ;
    return endround;
      //cout<<"Game Over."<<endl;
}


/*************************************************************************
 * Function Name: PKGameEngine::handleAction
 * Parameters: PKID id, PKActionID action
 * Returns: void
 * Effects:
 *************************************************************************/
void
PKGameEngine::handleAction(int playerNum, PKActionID action)
{
    GEPlayer* player = findPlayer(playerNum);
    if (player) {
	   switch (action) {
		
	   case PK_ACTION_PADDLE_UP:
		  player->moveUp();
		  break;
	   case PK_ACTION_PADDLE_DOWN:
		  player->moveDown();
		  break;
	   case PK_ACTION_PADDLE_LEFT:
		  player->moveLeft();
		  break;
	   case PK_ACTION_PADDLE_RIGHT:
		  player->moveRight();
		  break;
	   case PK_ACTION_PADDLE_PUNCH:
		  player->punch();
		  break;
	   case PK_ACTION_PADDLE_KICK:
		  player->kick();
		  break;
	   case PK_ACTION_PADDLE_CUT_UP:
		  player->uppercut();
		  break;
	   case PK_ACTION_PADDLE_CUT_DOWN:
		  player->lowercut();
		  break;
	   case PK_ACTION_PADDLE_SWEEP:
		  player->sweep();
		  break;
	   case PK_ACTION_PADDLE_BLOCK:
		  player->block();
		  break;
	   case PK_ACTION_PADDLE_UNBLOCK:
		  player->unblock();
		  break;
	   case PK_ACTION_PADDLE_SPECIAL_1:
		  if (!player->getBlock() && !player->getFrozen())
		      player->specialMove1();
		  break;
	   case PK_ACTION_PADDLE_SPECIAL_2:
		  if (!player->getBlock() && !player->getFrozen())
		      player->specialMove2();
		  break;
	   case PK_ACTION_PADDLE_SPECIAL_3:
	          if (!player->getBlock() && !player->getFrozen())
	          player->specialMove3();
		  break;
	   case PK_ACTION_PADDLE_STOP:
		  player->stop();
		  break;
	   case PK_ACTION_PADDLE_STOP_VERTICAL:
		  player->stopVertical();
		  break;
	   case PK_ACTION_PADDLE_STOP_HORIZONTAL:
		  player->stopHorizontal();
		  break;
	   case PK_ACTION_PAUSE:
	          _game_status.setPaused(true);
		  _server->broadcastPauseGame(true);
		  break;
           case PK_ACTION_UNPAUSE:
	          _game_status.setPaused(false);
		  _server->broadcastPauseGame(false);
		  break;
	   }
    }
}


/*************************************************************************
 * Function Name: PKGameEngine::handleHangup
 * Parameters: int playerNum
 * Returns: void
 * Effects:
 *************************************************************************/
void
PKGameEngine::handleHangup(int playerNum)
{
    //delete player.
}


/*=======================================================================*/
/*=======================================================================*/
/*==                    INTERNAL PUBLIC METHODS                        ==*/
/*=======================================================================*/
/*=======================================================================*/



/*************************************************************************
 * Function Name: PKGameEngine::addEvent
 * Parameters: GEEvent* newevent
 * Returns: void
 * Effects:
 *************************************************************************/
void
PKGameEngine::addEvent(GEEvent* newevent)
{
    _eventList.append(newevent);
}


/*************************************************************************
 * Function Name: PKGameEngine::broadcastUpdate
 * Parameters: GEGameObject* thing
 * Returns: void
 * Effects:
 *************************************************************************/
void
PKGameEngine::broadcastUpdate(GEGameObject* thing)
{
    if (_server)
	   _server->broadcastUpdate(*thing);
}


/*************************************************************************
 * Function Name: PKGameEngine::broadcastAddObject
 * Parameters: GEGameObject* thing
 * Returns: void
 * Effects:
 *************************************************************************/
void
PKGameEngine::broadcastAddObject(GEGameObject* thing)
{
    if (_server)
    _server->broadcastAddObject(*thing);
}

/*************************************************************************
 * Function Name: PKGameEngine::broadcastRemoveObject
 * Parameters: PKID id
 * Returns: void
 * Effects:
 *************************************************************************/
void
PKGameEngine::broadcastRemoveObject(PKID id)
{
    if (_server)
    _server->broadcastRemoveObject(id);
}



/*************************************************************************
 * Function Name: PKGameEngine::broadcastAnimateObject
 * Parameters: PKID id, PKAnimID animID
 * Returns: void
 * Effects:
 *************************************************************************/
void
PKGameEngine::broadcastAnimateObject(PKID id, PKAnimID animID)
{
    if (_server)
    _server->broadcastAnimateObject(id, animID);
}

void
PKGameEngine::broadcastPlaySound (PKSoundID soundID)
{

  if (_server)
    _server->broadcastPlaySound (soundID);

}


/*************************************************************************
 * Function Name: PKGameEngine::changeGameStatus
 * Parameters: int playernum, int newlife
 * Returns: void
 * Effects:
 *************************************************************************/
void
PKGameEngine::changeGameStatus(int playernum, int newlife)
{
  cout << "Setting life of player" << playernum << " to " << newlife << endl;
    _game_status.setLife(playernum, newlife);
    cout << "Number of players: " << endl;
    int j = _game_status.numPlayers();
    cout << j << endl;
    cout << "Here are the life amounts:" << endl;
    for (int z = 0; z < 4; z++)
      {
	int *i = _game_status.life();
	cout << "Player " << z << ": " << i[z] << endl;
      }
    if (_server)
    _server->broadcastGameStatus(_game_status);
}




/*=======================================================================*/
/*=======================================================================*/
/*==                      Non-Public Methods                           ==*/
/*=======================================================================*/
/*=======================================================================*/

/*************************************************************************
 * Function Name: PKGameEngine::startGame
 * Parameters:
 * Returns: void
 * Effects:
 *************************************************************************/
void
PKGameEngine::startGame()
{
    //tell clients to play "Fight" sound. any extra setup.
}


/*************************************************************************
 * Function Name: PKGameEngine::endGame
 * Parameters:
 * Returns: void
 * Effects:
 *************************************************************************/
void
PKGameEngine::endGame()
{
    _server->broadcastPauseGame(true);
    sleep(3);
    // hangup on the clients, notify the main server
    _server->broadcastEndGame();
}


/*************************************************************************
 * Function Name: PKGameEngine::addServerEvents
 * Parameters:
 * Returns: void
 * Effects:
 *************************************************************************/
void
PKGameEngine::addServerEvents()
{
    if (_server)
    _server->receive();
}


/*************************************************************************
 * Function Name: PKGameEngine::processEventList
 * Parameters:
 * Returns: void
 * Effects:
 *************************************************************************/
void
PKGameEngine::processEventList()
{
    while (! _eventList.isEmpty()) {
	   GEEvent* nextEvent = _eventList.get();
	   nextEvent->execute();
    }
}


/*************************************************************************
 * Function Name: PKGameEngine::updateObjects
 * Parameters:
 * Returns: void
 * Effects:
 *************************************************************************/
void

PKGameEngine::updateObjects()
{
    //update the positions of all of the objects w/current physics
    RWTPtrDlistIterator<GEGameObject>* itr = (_team1->iterator());
    //if not paused --mip
    if (!_game_status.paused()) {
      for (;(*itr)();) {
	_physics->update(itr->key());
	itr->key()->update();
      }
      delete itr;
      itr = (_team2->iterator());
      for (;(*itr)();) {
	_physics->update(itr->key());
	itr->key()->update();
      }
      delete itr;
      itr = (_projectiles->iterator());
      for (;(*itr)();) {
	_physics->update(itr->key());
	itr->key()->update();
      }
      delete itr;
    }
}


/*************************************************************************
 * Function Name: PKGameEngine::checkIntersections
 * Parameters:
 * Returns: void
 * Effects:
 *************************************************************************/
void
PKGameEngine::checkIntersections()
{
    //use physics to check intersections of all appropriate object pairs

    //check team1 players against projectiles and walls and other players
    RWTPtrDlistIterator<GEGameObject>* team1itr = (_team1->iterator());
    for (;(*team1itr)();) {
	   //check intersections with other players
	   RWTPtrDlistIterator<GEGameObject>* team2itr = (_team2->iterator());
	   for (;(*team2itr)();) {
		  int intersected = _physics->intersect(team1itr->key(), team2itr->key());
		  if (intersected) {
			 (team1itr->key())->intersect(team2itr->key());
			 (team2itr->key())->intersect(team1itr->key());
		  }
	   }
	   delete team2itr;
	
	   //check intersections with projectiles
	   RWTPtrDlistIterator<GEGameObject>* proj =
		  (_projectiles->iterator());
	   for (;(*proj)();) {
		  int intersected = _physics->intersect(team1itr->key(), proj->key());
		  if (intersected) {
			 (proj->key())->intersect(team1itr->key());
			 (team1itr->key())->intersect(proj->key());
		  }
	   }
	   delete proj;
	
	   //check intersections with walls
	   RWTPtrDlistIterator<GEGameObject>* wallitr = (_walls->iterator());
	   for (;(*wallitr)();) {
		  int intersected = _physics->intersect(team1itr->key(), wallitr->key());
		  if (intersected) {
			 (team1itr->key())->intersect(wallitr->key());
			 (wallitr->key())->intersect(team1itr->key());
		  }
	   }
	   delete wallitr;
    }
    delete team1itr;

    //check team2 players against projectiles and walls
    RWTPtrDlistIterator<GEGameObject>* team2itr = (_team2->iterator());
    for (;(*team2itr)();) {
	   //check intersections with projectiles
	   RWTPtrDlistIterator<GEGameObject>* proj =
		  (_projectiles->iterator());
	   for (;(*proj)();) {
		  int intersected = _physics->intersect(team2itr->key(), proj->key());
		  if (intersected) {
			 (proj->key())->intersect(team2itr->key());
			 (team2itr->key())->intersect(proj->key());
		  }
	   }
	   delete proj;
	
	   //check intersections with walls
	   RWTPtrDlistIterator<GEGameObject>* wallitr = (_walls->iterator());
	   for (;(*wallitr)();) {
		  int intersected = _physics->intersect(team2itr->key(), wallitr->key());
		  if (intersected) {
			 (team2itr->key())->intersect(wallitr->key());
			 (wallitr->key())->intersect(team2itr->key());
		  }
	   }
	   delete wallitr;
    }
    delete team2itr;

    //check projectiles intersect with walls
    RWTPtrDlistIterator<GEGameObject>* proj = (_projectiles->iterator());
    for (;(*proj)();) {
	   RWTPtrDlistIterator<GEGameObject>* wallitr = (_walls->iterator());
	   for (;(*wallitr)();) {
		  int intersected = _physics->intersect(proj->key(), wallitr->key());
		  if (intersected) {
			 (proj->key())->intersect(wallitr->key());
			 (wallitr->key())->intersect(proj->key());
		  }
	   }
	   delete wallitr;
    }
    delete proj;

}


GEPlayer *
PKGameEngine::choosePlayer (int team)
{
  if (team == 1)
    {
      if (_team1->isEmpty())
	{
	  return NULL;
	}
      else
	{
	  return (GEPlayer *) _team1->first();
	}
    }
  if (team == 2)
    {
      if (_team2->isEmpty())
	{
	  return NULL;
	}
      else
	{
	  return (GEPlayer *) _team2->first();
	}
    }
}

/*************************************************************************
 * Function Name: PKGameEngine::checkGameStatus
 * Parameters:
 * Returns: void
 * Effects:
 *************************************************************************/
void
PKGameEngine::checkEndRound(int& endround)
{
//    need to check for "FINISH HIM/HER" conditions

//    if ((_team1->isEmpty()) || (_team2->isEmpty())) {
//	   send a wins for all players on the team
//	   endround = 1;
//   }

    if (_team1->isEmpty()) {
      endround = 2; // Team 2 won.
    }
    else if (_team2->isEmpty()) {
      endround = 1; // Team 1 won.
	   //send a wins for all players on team
    }
}

/*************************************************************************
 * Function Name: PKGameEngine::addObject
 * Parameters: GEGameObject* thing
 * Returns: void
 * Effects:
 *************************************************************************/
void
PKGameEngine::addObject(GEGameObject* thing)
{
    thing->setUniqueID(_nextfree);
    _objArray[_nextfree] = thing;
    GEContainer* cont = thing->getContainer();
    cont->addObject(thing);
    findNextFree();
    if ((thing->getTypeID() != PK_TYPE_WALL_HORIZONTAL) &&
	   (thing->getTypeID() != PK_TYPE_WALL_VERTICAL))
	   broadcastAddObject(thing);
};


/*************************************************************************
 * Function Name: PKGameEngine::findNextFree
 * Parameters: none
 * Returns: void
 * Effects: finds the next array index where there is an available ID
 *************************************************************************/
void
PKGameEngine::findNextFree()
{
    //debug!!!
    int start = _nextfree;

    //find next free ID
    while (_objArray[_nextfree] != NULL) {
	   _nextfree ++;

	   if (_nextfree >= _maxNumObjs)
		  _nextfree -= _maxNumObjs;

	   //debug!!!
	   if (_nextfree == start) {
		  cout<<"RAN OUT OF ARRAY SPACES FOR OBJECTS!!!"<<endl;
		  return;
	   }
		
    }
}


/*************************************************************************
 * Function Name: PKGameEngine::removeObject
 * Parameters: int ID
 * Returns: void
 * Effects:
 *************************************************************************/
void
PKGameEngine::removeObject(PKID ID)
{
    /* hack by bh: _objArray[ID] was null at one point after a client
        violently quit, so now I check. */
    if(!_objArray[ID]) return;
    GEContainer* currcont = (_objArray[ID])->getContainer();
    GEGameObject* deadobj = currcont->removeObject(_objArray[ID]);
    _objArray[ID] = NULL; //so setNextFree will work
    delete deadobj;
    // broadcastRemoveObject(ID);

}


/*************************************************************************
 * Function Name: PKGameEngine::addPlayer
 * Parameters: PKTypeID type
 * Returns: void
 * Effects:
 *************************************************************************/
void
PKGameEngine::addPlayers(PKTypeID* players, int numplayers)
{
   GEPlayer* newplayer = NULL;
   PKPoint team1pos((PK_DIM_WALL_LEFT_X +30),
				(PK_DIM_WALL_TOP_Y + 100));
   PKPoint team2pos((PK_DIM_WALL_RIGHT_X - 30),
				(PK_DIM_WALL_TOP_Y + 100));

   _game_status.setNumPlayers(numplayers);
   _game_status.setPaused(0);   //not paused initially

   for (int j=0; j<_numplayers; j++) {
	  if (players[j] != PK_TYPE_INVALID)
		 _game_status.setLife(j, 100);
	  else
		 _game_status.setLife (j, -1);
	
	  PKTypeID type = players[j];
	
	  switch (type) {

	  case PK_TYPE_INVALID:
		 newplayer = NULL;
		 break;
	  case PK_TYPE_CYRAX_1:
		 //newplayer = new GECyraxLeftPlayer(_nextfree, j, &team1pos,
		 //team1, this);
		 newplayer = new GECyraxLeftPlayer(_nextfree, j, &team1pos,
							 _team1, this);
		 team1pos.setCoord(1, team1pos[1] + 100);
		 break;
		
	  case PK_TYPE_JADE_1:
		 newplayer = new GEJadeLeftPlayer(_nextfree, j, &team1pos,
		 _team1, this);
		
		 team1pos.setCoord(1, team1pos[1] + 100);
		 break;
	  case PK_TYPE_KABAL_1:
		 //newplayer = new GEKabalLeftPlayer(_nextfree, j, &team1pos,
		 //team1, this);
		 newplayer = new GEKabalLeftPlayer(_nextfree, j, &team1pos,
							 _team1, this);
		 team1pos.setCoord(1, team1pos[1] + 100);
		 break;
	  case PK_TYPE_LIU_KANG_1:
		 newplayer = new GELKLeftPlayer(_nextfree, j, &team1pos,
							 _team1, this);
		 team1pos.setCoord(1, team1pos[1] + 100);
		 break;

	  case PK_TYPE_REPTILE_1:
	    //newplayer = new GEReptileLeftPlayer(_nextfree, j, &team1pos,
	    // _team1, this);
		 newplayer = new GERepLeftPlayer(_nextfree, j, &team1pos,
		 					 _team1, this);
		 team1pos.setCoord(1, team1pos[1] + 100);
		 break;
	  case PK_TYPE_SCORPION_1:
		 //newplayer = new GEScorpionLeftPlayer(_nextfree, j, &team1pos,
		 //team1, this);
		 newplayer = new GELKLeftPlayer(_nextfree, j, &team1pos,
							 _team1, this);
		 team1pos.setCoord(1, team1pos[1] + 100);
		 break;
	  case PK_TYPE_SMOKE_1:
		 //newplayer = new GESmokeLeftPlayer(_nextfree, j, &team1pos,
		 //team1, this);
		 newplayer = new GELKLeftPlayer(_nextfree, j, &team1pos,
							 _team1, this);
		 team1pos.setCoord(1, team1pos[1] + 100);
		 break;
	  case PK_TYPE_SONYA_1:
		 //newplayer = new GESonyaLeftPlayer(_nextfree, j, &team1pos,
		 //team1, this);
		 newplayer = new GELKLeftPlayer(_nextfree, j, &team1pos,
							 _team1, this);
		 team1pos.setCoord(1, team1pos[1] + 100);
		 break;
	  case PK_TYPE_SUB_ZERO_1:
		 newplayer = new GESZLeftPlayer(_nextfree, j, &team1pos,
							 _team1, this);
		 team1pos.setCoord(1, team1pos[1] + 100);
		 break;

		 //team 2 players
	  case PK_TYPE_CYRAX_2:
		 //newplayer = new GECyraxRightPlayer(_nextfree, j, &team1pos,
		 //team1, this);
		 newplayer = new GECyraxRightPlayer(_nextfree, j,
&team2pos,
							 _team2, this);
		 team2pos.setCoord(1, team2pos[1] + 100);
		 break;
	  case PK_TYPE_JADE_2:
		 //newplayer = new GEJadeRightPlayer(_nextfree, j, &team1pos,
		 //team1, this);
		 newplayer = new GEJadeRightPlayer(_nextfree, j,
&team2pos,
							 _team2, this);
		 team2pos.setCoord(1, team2pos[1] + 100);
		 break;
	  case PK_TYPE_KABAL_2:
		 //newplayer = new GEKabalRightPlayer(_nextfree, j, &team1pos,
		 //team1, this);
		 newplayer = new GEKabalRightPlayer(_nextfree, j, &team2pos,
							 _team2, this);
		 team2pos.setCoord(1, team2pos[1] + 100);
		 break;
	  case PK_TYPE_LIU_KANG_2:
		 newplayer = new GELKRightPlayer(_nextfree, j, &team2pos,
							 _team2, this);
		 team2pos.setCoord(1, team2pos[1] + 100);
		 break;
	  case PK_TYPE_REPTILE_2:
		 newplayer = new GERepRightPlayer(_nextfree, j, &team2pos,
							 _team2, this);
		 team2pos.setCoord(1, team2pos[1] + 100);
		 break;
	  case PK_TYPE_SCORPION_2:
		 //newplayer = new GEKabalRightPlayer(_nextfree, j, &team1pos,
		 //team1, this);
		 newplayer = new GELKRightPlayer(_nextfree, j, &team2pos,
							 _team2, this);
		 team2pos.setCoord(1, team2pos[1] + 100);
		 break;
	  case PK_TYPE_SMOKE_2:
		 //newplayer = new GEKabalRightPlayer(_nextfree, j, &team1pos,
		 //team1, this);
		 newplayer = new GELKRightPlayer(_nextfree, j, &team2pos,
							 _team2, this);
		 team2pos.setCoord(1, team2pos[1] + 100);
		 break;
	  case PK_TYPE_SONYA_2:
		 //newplayer = new GEKabalRightPlayer(_nextfree, j, &team1pos,
		 //team1, this);
		 newplayer = new GELKRightPlayer(_nextfree, j, &team2pos,
							 _team2, this);
		 team2pos.setCoord(1, team2pos[1] + 100);
		 break;
	  case PK_TYPE_SUB_ZERO_2:
		 //newplayer = new GEKabalRightPlayer(_nextfree, j, &team1pos,
		 //team1, this);
		 newplayer = new GESZRightPlayer(_nextfree, j, &team2pos,
							 _team2, this);
		 team2pos.setCoord(1, team2pos[1] + 100);
		 break;
	  } //end switch(type)

	  if (newplayer != NULL)
		 addObject(newplayer);
	
   } //end for loop

} //end addPlayers


/*************************************************************************
 * Function Name: PKGameEngine::addWall
 * Parameters: none
 * Returns: void
 * Effects:
 *************************************************************************/
void
PKGameEngine::addWall(GEWallSide side)
{
    GEWall* newwall = NULL;
    PKPoint* pos = NULL;
    PKVector* vect = new PKVector(); //walls don't move. zero vector.
    switch (side) {
	 case GEWALL_TOP:
	   pos = new PKPoint((PK_DIM_SCREEN_WIDTH/2),
					 (PK_DIM_WALL_TOP_Y - 5));
	   newwall = new GEWall(_nextfree, PK_TYPE_WALL_HORIZONTAL, 0, _walls,
					    PK_DIM_SCREEN_WIDTH, 10, *pos, *vect, this);
	   break;
	
	 case GEWALL_BOTTOM:
	   pos = new PKPoint((PK_DIM_SCREEN_WIDTH/2),
					 (PK_DIM_WALL_BOTTOM_Y + 5));
	   newwall = new GEWall(_nextfree, PK_TYPE_WALL_HORIZONTAL, 0, _walls,
					    PK_DIM_SCREEN_WIDTH, 10, *pos, *vect, this);
	   break;
	
	 case GEWALL_LEFT:
	   pos = new PKPoint((PK_DIM_WALL_LEFT_X - 5),
					 ((PK_DIM_SCREEN_HEIGHT - PK_DIM_WALL_TOP_Y)/2
					  + PK_DIM_WALL_TOP_Y));
	   newwall = new GEWall(_nextfree, PK_TYPE_WALL_VERTICAL, 1, _walls,
					    10, PK_DIM_SCREEN_HEIGHT, *pos, *vect, this);
	   break;
	
	 case GEWALL_RIGHT:
	   pos = new PKPoint((PK_DIM_WALL_RIGHT_X + 5),
					 ((PK_DIM_SCREEN_HEIGHT - PK_DIM_WALL_TOP_Y)/2
					  + PK_DIM_WALL_TOP_Y));
	   newwall = new GEWall(_nextfree, PK_TYPE_WALL_VERTICAL, 2, _walls,
					    10, PK_DIM_SCREEN_HEIGHT, *pos, *vect, this);
	   break;
    }
    addObject(newwall);
}


/*************************************************************************
 * Function Name: PKGameEngine::findPlayer
 * Parameters: int playerNum
 * Returns: PKPlayer*
 * Effects:
 *************************************************************************/
GEPlayer*
PKGameEngine::findPlayer(int playerNum)
{
    RWTPtrDlistIterator<GEGameObject>* player = (_team1->iterator());
    for (;(*player)();) {
	   GEPlayer* currplayer = (GEPlayer*) player->key();
	   if (currplayer->getPlayerNum() == playerNum)
		  return currplayer;
    }
    delete player;
    player = (_team2->iterator());
    for (;(*player)();) {
	   GEPlayer* currplayer = (GEPlayer*) player->key();
	    if (currplayer->getPlayerNum() == playerNum)
		  return currplayer;
    }
    delete player;
    return 0;
}

/*************************************************************************
 * Function Name: PKGameEngine::processKombatKode
 * Parameters: PKKombatKodeID kode
 * Returns: void
 * Effects:
 *************************************************************************/
void
PKGameEngine::processKombatKode(PKKombatKodeID kode)
{
    //enum type.  Each will set up different attributes of game
}



