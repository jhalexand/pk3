/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: bh                                                  */
/*    FILE: PKGameStatus.h                                      */
/*    ASGN:                                                     */
/*    DATE: Sat Apr 26 16:02:21 1997                            */
/****************************************************************/


#ifndef PKGAMESTATUS_HEADER
#define PKGAMESTATUS_HEADER

#include <PKids.h>
#include <debug.h> // boolean, true, false, dprintf, etc
#include <stdlib.h> // free, malloc
#include <string.h> // strdup

#define null NULL

// a simple function used in operator == for strings; doesn't crash
// on null strings, like strcmp does
inline int safeStrcmp(const char *s1, const char *s2) {
    if(s1 && s2) return strcmp(s1, s2);
    else return s1==s2;
}

/****************************************************************/
/* CLASS NAME :  PKGameStatus                                   */
/* Used to convey general information about the status of the   */
/* game in progress.                                            */
/*                                                              */
/****************************************************************/

class PKGameStatus {
protected:
    boolean paused_;
    int numPlayers_;
    int *life_; // array of size numPlayers, life is 0-100
public:
    PKGameStatus() { 
        paused_ = false;
        numPlayers_ = 0;
        life_ = null; 
    }

    PKGameStatus(const PKGameStatus& other) {
        life_ = null;
        *this = other;
    }

    virtual ~PKGameStatus() { if(life_) free(life_); }

    PKGameStatus& operator = (const PKGameStatus& other) {
        setPaused(other.paused());
        setNumPlayers(other.numPlayers());
        for(int i=0; i<numPlayers(); i++) {
            setLife(i, other.life()[i]);
        }
        return *this;
    }

    boolean operator == (const PKGameStatus& other) const {
        if(numPlayers()!=other.numPlayers()) { return false; }
        if(paused()!=other.paused()) { return false ; }
        for(int i=0; i<numPlayers(); i++) 
            if(life(i)!=other.life(i)) return false;
        return true;
    }

    // accessors
    boolean paused() const { return paused_; }
    int numPlayers() const { return numPlayers_; }
    int *life() const { return life_; }
    int life(int i) const { return life_[i]; }

    // mutators
    void setPaused(boolean p) { paused_ = p; }
    void setNumPlayers(int n) {
        if(life_) free(life_);
        life_ = (int*)malloc(n*sizeof(int));
        numPlayers_ = n;
    }
    void setLife(int i, int l){ life_[i] = l; }

    
    void debugPrint() const {
        dprintf(("[PKGameStatus %x]\n", this));
        dprintfLevelUp(); dprintfLevelUp(); dprintfLevelUp();
        dprintf(("paused:   %s\n", paused() ? "yes" : "no"));
        dprintf(("nplayers: %d\n", numPlayers()));
        dprintf(("life:     %x\n", life()));
        for(int i=0; i<numPlayers(); i++) {
            dprintf(("life %d:  %d\n", life(i)));
        }
        dprintfLevelDown(); dprintfLevelDown(); dprintfLevelDown();
    }
};





/****************************************************************/
/* CLASS NAME :  PlayerInfo                                     */
/* Conveys information about the player; useful in the setup    */
/* screen.                                                      */
/* A player number of -1 is a non-player                        */
/*                                                              */
/****************************************************************/

class PKPlayerInfo {
protected:
    int  playerNum_, team_, life_;
    char *name_,    *acct_, *host_;
    PKAILevel aiLevel_;
    PKTypeID paddle_;
public:
    PKPlayerInfo() { 
        life_    = team_ = playerNum_ = 0;
        host_    = acct_ = name_      = null;
        aiLevel_ = PK_AI_HUMAN;
        paddle_  = PK_TYPE_INVALID;
    }

    PKPlayerInfo(const PKPlayerInfo& other) {
        name_ = acct_ = host_ = null;
        *this = other;
    }

    virtual ~PKPlayerInfo() {
        if(name_) free(name_);
        if(acct_) free(acct_);
        if(host_) free(host_);
    }

    PKPlayerInfo& operator = (const PKPlayerInfo& other) {
        setPlayerNumber(other.playerNumber());
        setTeam(other.team());
        setPaddle(other.paddle());
        setLife(other.life());
        setUsername(other.username());
        setAccount(other.account());
        setHostname(other.hostname());
        setAILevel(other.aiLevel());
        return *this;
    }

    boolean operator == (const PKPlayerInfo& other) const {
        if(playerNumber()!=other.playerNumber()) return false ;
        if(life()!=other.life()) return false;
        if(paddle()!=other.paddle()) return false;
        if(team()!=other.team()) return false;
        if(aiLevel()!=other.aiLevel()) return false;
        if(safeStrcmp(username(), other.username())) return false ;
        if(safeStrcmp(account(), other.account())) return false ;
        if(safeStrcmp(hostname(), other.hostname())) return false ;
        return true;
    }

    // accessors
    int playerNumber() const { return playerNum_; }
    int team() const { return team_; }
    PKTypeID paddle() const { return paddle_; }
    int life() const { return life_; }
    PKAILevel aiLevel() const { return aiLevel_; }

    char* username() const { return name_; }
    char* account()  const { return acct_; }
    char* hostname() const { return host_; }



    // mutators
    virtual void setPlayerNumber(int pnum) { playerNum_ = pnum; }
    virtual void setTeam(int t) { team_ = t; }
    virtual void setPaddle(PKTypeID t) { paddle_ = t; }
    virtual void setLife(int l) { life_ = l; }
    virtual void setAILevel(PKAILevel lvl)  { aiLevel_ = lvl; }

    void setUsername(const char *name) {
        if(name_) free(name_);
        name_ = name ? strdup(name) : null ;
    }

    void setAccount (const char *acct) {
        if(acct_) free(acct_);
        acct_ = acct ? strdup(acct) : null ;
    }

    void setHostname(const char *host) {
        if(host_) free(host_);
        host_ = host ? strdup(host) : null ;
    }


    void debugPrint() const {
        dprintf(("[PKPlayerInfo %x]\n", this));
        dprintfLevelUp(); dprintfLevelUp(); dprintfLevelUp();
        dprintf(("player:   %d\n", playerNumber()));
        dprintf(("team:     %d\n", team()));
        dprintf(("paddle:   %d\n", paddle()));
        dprintf(("life:     %d\n", life()));
        dprintf(("username: %s\n", username() ? username(): "(nil)"));
        dprintf(("account:  %s\n", account()  ? account() : "(nil)"));
        dprintf(("hostname: %s\n", hostname() ? hostname(): "(nil)"));
        dprintf(("aiLevel:  %d\n", aiLevel()));
        dprintfLevelDown(); dprintfLevelDown(); dprintfLevelDown();
    }
};



/****************************************************************/
/* CLASS NAME :  PKGameProgress                                 */
/* Encapsulates the information to be displayed on the main     */
/* screen (the screen with lists of players and games).         */
/* Note that a player with player number -1 is an empty slot    */
/*                                                              */
/****************************************************************/


class PKGameProgress {
private:
    char *creatorName_; // name of whoever created the game
    int numPlayers_;
public:
    PKGameProgress() { 
        creatorName_=null; 
        numPlayers_ = 0;
    }
    PKGameProgress(const char *creatorName, int numPlayers) {
        creatorName_ = creatorName ? strdup(creatorName) : null ;
        numPlayers_ = numPlayers;
    }
    PKGameProgress(const PKGameProgress& prog) {
        creatorName_ = null;
        *this = prog;
    }

    virtual ~PKGameProgress() { if(creatorName_) free(creatorName_); }

    PKGameProgress& operator = (const PKGameProgress& other) {
        setCreatorName(other.creatorName());
        setNumPlayers(other.numPlayers());
        return *this ;
    }

    boolean operator == (const PKGameProgress& other) const {
        if(numPlayers()!=other.numPlayers()) return false ;
        if(safeStrcmp(creatorName(), other.creatorName())) return false;
        return true;
    }

    char *creatorName() const { return creatorName_; }
    int numPlayers() const { return numPlayers_; }

    void setCreatorName(const char *name) {
        if(creatorName_) { free(creatorName_); }
        creatorName_ = name ? strdup(name) : null;
    }
    void setNumPlayers(int np) {
        numPlayers_ = np;
    }

    void debugPrint() const {
        dprintf(("[PKGameProgress %x]\n", this));
        dprintfLevelUp(); dprintfLevelUp(); dprintfLevelUp();
        dprintf(("creatorName: %s\n", creatorName() ? creatorName():"(nil)"));
        dprintf(("numPlayers:  %d\n", numPlayers()));
        dprintfLevelDown(); dprintfLevelDown(); dprintfLevelDown();
    }
} ;



/****************************************************************/
/* CLASS NAME :  GameParameters                                 */
/* Conveys information about how the game is setup;             */
/* useful in the setup screen (when collecting players into a   */
/* game.                                                        */
/****************************************************************/

class PKGameParameters {
protected:
    int numPlayers_;
    PKPlayerInfo *players_; // array of size numPlayers
    boolean gameInProgress_; // 0=on setup screen; else playing
    PKBackgroundID background_;
    PKKombatKodeID kode_;

public:
    PKGameParameters() { 
        numPlayers_ = 0;
        players_ = null; 
        gameInProgress_ = false;
        background_ = PK_BACKGROUND_LAVA;
        kode_ = PK_KOMBAT_KODE_NONE;
    }

    PKGameParameters(const PKGameParameters& other) {
        players_ = null;
        *this = other;
    }

    virtual ~PKGameParameters() { if(players_) delete [] players_; }

    PKGameParameters& operator = (const PKGameParameters& other) {
        setNumPlayers(other.numPlayers());
        for(int i=0; i<numPlayers(); i++) {
            getPlayer(i) = other.players()[i];
        }
        setGameInProgress(other.gameInProgress());
        setBackground(other.background());
        setKode(other.kode());
        return *this;
    }

    boolean operator == (const PKGameParameters& other) const {
        if(numPlayers()!=other.numPlayers()) return false;
        if(kode()!=other.kode()) return false;
        if(background()!=other.background()) return false;
        if(gameInProgress()!=other.gameInProgress()) return false;
        for(int i=0; i<numPlayers(); i++) if(players(i)==other.players(i)) return false;
        return true;
    }

    // accessors
    int numPlayers() const { return numPlayers_; }
    PKPlayerInfo *players() const { return players_; }
    PKPlayerInfo& players(int i) const { return players_[i]; }
    int gameInProgress() const { return gameInProgress_; }
    PKBackgroundID background() const { return background_; }
    PKKombatKodeID kode() const { return kode_; }

    // mutators
    void setNumPlayers(int np) {
        numPlayers_ = np;
        if(players_) delete [] players_;
        players_ = new PKPlayerInfo[numPlayers_];
    }
    PKPlayerInfo& getPlayer(int i) { return players_[i]; } // non-const version
    const PKPlayerInfo& getPlayer(int i) const { return players_[i]; } // const version
    void setGameInProgress(int gip) { gameInProgress_ = gip; }
    void setBackground(PKBackgroundID bg) { background_ = bg; }
    void setKode(PKKombatKodeID kode) { kode_ = kode; }

    void debugPrint() const {
        dprintf(("[PKGameParameters %x]\n", this));
        dprintfLevelUp(); dprintfLevelUp(); dprintfLevelUp();
        dprintf(("numPlayers:  %d\n", numPlayers()));
        dprintf(("kode:        %d\n", kode()));
        dprintf(("background:  %d\n", background()));
        dprintf(("gameInProgress: %s\n", gameInProgress() ? "true" : "false"));
        for(int i=0; i<numPlayers(); i++) {
            players(i).debugPrint();
        }
        dprintfLevelDown(); dprintfLevelDown(); dprintfLevelDown();
    }
};


#endif
