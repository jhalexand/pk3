/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: bh                                                  */
/*    FILE: PKAIClient.h                                        */
/*    ASGN:                                                     */
/*    DATE: Sun May  4 06:55:55 1997                            */
/****************************************************************/


#ifndef PKAICLIENT_HEADER
#define PKAICLIENT_HEADER

#include <PKClientInterface.h>
#include <PKClientObject.h>
//#include <rw/tvslist.h>
#include <HashTable.h>
#include <Xm/Xm.h>
#include <sys/time.h>

class PKAIClient : public PKClientInterface {
public:
    PKAIClient(const char *host, int port, int playerNum);
    virtual ~PKAIClient();
    virtual PKClientObject* getStateOfObject(PKID) { return null;}
    virtual void handleKeyPress(PKKey) {}
    virtual void handleKeyRelease(PKKey) {}

    //MainServer stuff
    virtual void addUser(int, const char*, const char*, const char*) {}
    virtual void removeUser(int) {}
    virtual void addGame(int, const PKGameProgress&) {}
    virtual void removeGame(int) {}
    virtual void enterGameSetup(int, const PKGameParameters&, int) {}
    virtual void error(const char*) {}

    //GameGathering stuff
    virtual void addPlayer(int, const PKPlayerInfo&) {}
    virtual void removePlayer(int) {}
    virtual void rejectPlayer(int) {}
    virtual void setPaddle(int, PKTypeID) {}
    virtual void setTeam(int, int) {}
    virtual void setKombatKode(int, const char*) {}
    virtual void setChatText(int, const char*) {}
    virtual void returnToMainScreen() {}
    virtual void cancel() {}
    virtual void enterGamePlay(const PKGameParameters&);  

    //GameServer stuff
    virtual void addObject(const PKObject&);
    virtual void removeObject(PKID);
    virtual void update(const PKObject&);
    virtual void updateAnimation(PKID, PKAnimID);
    virtual void gameStatus(const PKGameStatus&);
    virtual void endGame() { exit(0); }
    virtual void setPause(boolean paused) { is_paused_ = paused;}
    virtual void togglePause() { setPause(!is_paused_); }

    virtual void playSound(PKSoundID) {}

private:
    static void static_updateCallback(void*, XtIntervalId*);
    void update();
    static const hrtime_t FIRE_RATE ;
    static const double FIRE_OFF;
    static const int UP;
    static const int DOWN;
    static const int STILL;


    XtAppContext app_ ;
    PKClientNetworkInterface *net_ ;

    hrtime_t lastFireTime_;

    int playerNum_;
    int is_paused_;
    PKClientObject *self_;
    PKID unique_;

    IntHash<PKClientObject*> follow_;
    IntHash<PKClientObject*> target_;
    IntHash<PKClientObject*> hidden_;
    
    int followID_; // id of the ball (or anything) to follow
} ;

#endif
