/*************************************************************************
 *    NAME: Elaine Chen
 *    USER: eyc
 *    FILE: GEInjureTeamEvent.cxx
 *    DATE: Thu May  1 22:29:01 US/Eastern 1997
 *************************************************************************/
#include "GEInjureTeamEvent.h"
#include "PKGameEngine.h"
#include "GEPlayer.h"

/*************************************************************************
 * Function Name: GEInjureTeamEvent::GEInjureTeamEvent
 * Parameters: int team
 * Effects: 
 *************************************************************************/

GEInjureTeamEvent::GEInjureTeamEvent(PKGameEngine* engine,
							  int team,
							  int injury)
    : GEEvent(engine), _team(team), _injury(injury)
{
}


/*************************************************************************
 * Function Name: GEInjureTeamEvent::~GEInjureTeamEvent
 * Parameters: 
 * Effects: 
 *************************************************************************/

GEInjureTeamEvent::~GEInjureTeamEvent()
{
}


/*************************************************************************
 * Function Name: GEInjureTeamEvent::execute
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GEInjureTeamEvent::execute()
{
    GEContainer* teamList = NULL;
    if (_team == 1)
	   teamList = _engine->getTeam1List();
    else if (_team == 2)
	   teamList = _engine->getTeam2List();
    
    RWTPtrDlistIterator<GEGameObject>* itr = teamList->iterator();
    for (;(*itr)();) {
	   GEPlayer* player = (GEPlayer*) itr->key();
	   player->subtractLife(_injury);
	   //play sounds?
    }
}


