/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: cs032082                                            */
/*    FILE: PKUser.h                                            */
/*    ASGN:                                                     */
/*    DATE: Wed Apr 30 15:36:29 1997                            */
/****************************************************************/


#ifndef PKUSER_HEADER
#define PKUSER_HEADER
#include <strings.h>
#include <stdlib.h>

class PKUser {
public:
  PKUser(int userID, char* user, char* account, char* host) {
    ID_ = userID;
    user_ = strdup(user);
    account_ = strdup(account);
    host_ = strdup(host);
    next_ = '\0' ;
  }

  virtual ~PKUser() {
    free(user_); user_ = '\0';
    free(account_); account_ = '\0';
    free(host_); host_ = '\0';
  }

  PKUser* getNext() {return next_;}
  void setNext(PKUser* next) {next_ = next;}
  PKUser* removeUser(int userID){
    if (userID == ID_) return next_;
    else if (next_) {
      PKUser* temp = next_->removeUser(userID);
      if (temp != next_) {
	delete(next_);
	next_ = temp;
      }
      return this;
    }
    else return this;
  }
  char* getUser(int id) {
    if (id == ID_) return user_;
    else if (next_) return next_->getUser(id);
    else return '\0';
  }
protected:
  PKUser* next_;
  int ID_;
  char *user_;
  char *account_;
  char *host_;
};

#endif
