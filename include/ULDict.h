#ifndef DICT_HEADER
#define DICT_HEADER

#include <debug.h>
#include <stdlib.h> // free
#include <string.h> // strcmp

class ULDNode {
  friend class UnsortedListDict ;
  friend class ULDIterator ;

private:
  ULDNode *next_;
  const char *str_;
  void *data_ ;

  ULDNode(ULDNode *next, const char *str, void *data) {
    next_ = next; str_ = strdup(str); data_ = data ;
  }
  
  ~ULDNode() { next_ = null; free((void*)str_); str_ = null; data_ = null ;}

  ULDNode *next() const { return next_; }
  void setNext(ULDNode *next) { next_ =  next ; }

  void *data() const { return data_; }
  const char *str() const { return str_; }

  void setData(void *newdata) { data_ = newdata; }
} ;

class UnsortedListDict {
friend class ULDIterator ;
private:
  ULDNode *head_;
  ULDNode *tail_;

  void append(const char *str, void *data ) {
    if(isEmpty()) {
      head_ = tail_ = new ULDNode(null, str, data);
    }
    else {
      tail_->setNext(new ULDNode(null, str, data));
      tail_ = tail_->next();
    }
  }

  ULDNode *find(const char *str) const {
    ULDNode *cur ;
    ULDNode *next= head_ ;
    while( (cur=next) ) { // assign
      next = cur->next();
      if( !strcmp(cur->str(), str) ) {
	return cur ; // return the found node
      }
    }
    return null ; // not found
  }
  
public:
  UnsortedListDict() { head_ = tail_ = null; }

  ~UnsortedListDict() {
    ULDNode *cur = head_ ;
    ULDNode *next ;

    while(cur) {
      next = cur->next();
      delete cur;
      cur = next ;
    }
  }

  // return the data associated with the string
  void *get(const char *str) const {
    ULDNode *found = find(str) ;
    if(!found) return null ;
    else return found->data() ;
  }

  // set the data associated with the string (create if not already set)
  void set(const char *str, void *data) {
    ULDNode *found = find(str) ;
    if(!found) append(str, data);
    else found->setData(data) ;
  }

  // check if str is contained (allows seeing if get of null is failed find
  // or data is null)
  boolean isset(const char *str) {
    return find(str) ? true : false ;
  }

  boolean isEmpty() {
    return head_ == null;
  }
} ;

class ULDIterator {
private:
  ULDNode *cur_;

public:
  ULDIterator() { cur_ = null ; }
  ULDIterator(UnsortedListDict& l) { cur_ = l.head_; }
  ~ULDIterator() {}

  void reset(UnsortedListDict& l) { cur_ = l.head_; }

  const char *current() const { return cur_ ? cur_->str() : (const char*)null; }
  const void *curdata() const { return cur_ ? cur_->data(): (const void*)null; }
  
  const char *next() { if(cur_) cur_ = cur_->next(); return current(); }

  void setdata(void *d) {
    if(cur_) cur_->setData(d);
  }
} ;
#endif
