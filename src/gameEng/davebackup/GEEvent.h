/*************************************************************************/
/*    NAME: Elaine Chen                                                  */
/*    ACCT: eyc                                                          */
/*    FILE: GEEvent.h                                                    */
/*    DATE: Sun Apr 27 15:07:25 1997                                     */
/*************************************************************************/


#ifndef GEEVENT_HEADER
#define GEEVENT_HEADER

class PKGameEngine;

class GEEvent {
public:
    GEEvent(PKGameEngine* engine);
    virtual ~GEEvent();

    virtual void execute();
    
protected:
    PKGameEngine* _engine;
};
    
#endif
