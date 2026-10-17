/*************************************************************************/
/*    NAME: Elaine Chen                                                  */
/*    ACCT: eyc                                                          */
/*    FILE: GEInjureTeamEvent.h                                          */
/*    DATE: Tue Apr 29 15:23:21 1997                                     */
/*************************************************************************/


#ifndef GEINJURETEAMEVENT_HEADER
#define GEINJURETEAMEVENT_HEADER

#include "GEEvent.h"

class PKGameEngine;

class GEInjureTeamEvent : public GEEvent {

public:
    GEInjureTeamEvent(PKGameEngine* engine, int team, int injury);
    virtual ~GEInjureTeamEvent();

    virtual void execute();

protected:
    int _team;
    int _injury; //amount lost when player is hit
};


#endif
