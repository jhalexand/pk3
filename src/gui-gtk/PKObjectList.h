/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: cs032082                                            */
/*    FILE: PKObjectList.h                                      */
/*    ASGN:                                                     */
/*    DATE: Wed Apr 30 14:42:12 1997                            */
/****************************************************************/


#ifndef PKOBJECTLIST_HEADER
#define PKOBJECTLIST_HEADER
#include "PKClientObject.h"

class PKObjectList {
public:
  PKObjectList(PKClientObject* obj) {
    obj_ = obj;
    next_ = NULL;
  }
  ~PKObjectList() {}
  void setNext(PKObjectList* next) {
    next_ = next;
  }
  PKObjectList* getNext() {return next_;}
  PKObjectList* removeObject(PKID id) {
    if ( id == obj_->getUniqueID()) return next_;
    else if (next_) {
      PKObjectList* temp = next_->removeObject(id);
      if (temp != next_) {
	delete(next_);
	next_ = temp;
      }
      return this;
    }
    else return this;
  }
  PKClientObject* getObject(PKID id) {
    if ( id == obj_->getUniqueID()) return obj_;
    else if (next_) 
      return next_->getObject(id);
    else return NULL;
  }
  void update(PKClientObject* obj) {
    if (obj_->getUniqueID() == obj->getUniqueID()) {
      //dprintf(("Animation was initially %d\n", obj_->getAnimation()));
      obj->setAnimation(obj_->getAnimation());
      obj_ = obj;
      //dprintf(("Animation is now %d\n", obj_->getAnimation()));
    }
    else if (next_) next_->update(obj);
  }
protected:
  PKClientObject* obj_;
  PKObjectList* next_;
};

#endif
