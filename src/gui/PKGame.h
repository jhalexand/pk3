/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: cs032082                                            */
/*    FILE: PKGame.h                                            */
/*    ASGN:                                                     */
/*    DATE: Wed Apr 30 14:20:46 1997                            */
/****************************************************************/


#ifndef PKGAME_HEADER
#define PKGAME_HEADER
#include <strings.h>

class PKGame {
public:
  PKGame(const char* game, int gameID) {
    game_ = strdup(game);
    ID_ = gameID;
    next_ = null ;
  }

  virtual ~PKGame() {
    free((void*)game_);
  }

  PKGame* removeGame(const char* game) {
    if (!strcmp(game_, game)) return next_;
    else if (next_) {
      PKGame* temp = next_->removeGame(game);
      if (temp != next_) {
	delete(next_);
	next_ = temp;
      }
      return this;
    }
    else return this;
  }

  PKGame* removeGame(int id) {
    if (ID_ == id) return next_;
    else if (next_) {
      PKGame* temp = next_->removeGame(id);
      if (temp != next_) {
	delete(next_);
	next_ = temp;
      }
      return this;
    }
    else return this;
  }

  int getID(const char* game) const {
    if (!strcmp(game_, game)) return ID_;
    else if (next_) return next_->getID(game);
    else return 0;
  }

  const char* getGame(int id) const {
    if (id == ID_) return game_;
    else if (next_) return next_->getGame(id);
    else return NULL;
  }

  PKGame* getNext() { return next_;}
  void setNext(PKGame* next) {next_ = next;}
protected:
  const char *game_;
  int ID_;
  PKGame* next_;
};
#endif


