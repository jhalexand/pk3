#ifndef HT_DICT_HEADER
#define HT_DICT_HEADER

#include <debug.h>
#include <string.h> // strcmp
#include <ULDict.h> // unsorted list dictionary

typedef unsigned int (*HashFunc)(const char *) ;

class HashTableDict {
friend class HTIterator ;
private:
  HashFunc func_ ;  // should return an integer between 0 and <size>-1
  UnsortedListDict *array_ ;
  unsigned int numelts_ ;
  int size_ ; // number of buckets

public:
  HashTableDict(HashFunc func, int size) {
    func_  = func ;
    array_ = new UnsortedListDict[size] ;
    size_  = size ;
    numelts_ = 0 ;
  }

  ~HashTableDict() {
    delete [] array_ ;
    size_ = 0 ;
    func_ = 0 ;
  }

  // return the data associated with the string
  void *get(const char *str) const {
    return array_[func_(str)].get(str) ;
  }

  // set the data associated with the string (create if not already set)
  void set(const char *str, void *data) {
    if(!isset(str)) numelts_++ ;
    array_[func_(str)].set(str, data) ;
  }

  // check if str is contained (allows seeing if get of null is failed find
  // or data is null)
  boolean isset(const char *str) {
    return array_[func_(str)].isset(str);
  }

  unsigned int numelts() { return numelts_ ; }
  boolean isEmpty() { return numelts_==0; }
} ;

class HTIterator {
private:
  int curbucket_ ;
  ULDIterator it_;
  HashTableDict *d_ ;

public:
  HTIterator(HashTableDict& d) { d_ = &d; curbucket_ = -1; next() ; }
  ~HTIterator() {}

  void reset(HashTableDict& d) { d_ = &d; curbucket_ = -1 ; next() ; }

  const char *current() const {
    return it_.current() ;
  }

  const void *curdata() const {
    return it_.curdata() ;
  }

  const char *next() {
    if(!it_.next()) {
      while(!it_.current()) {
	curbucket_++ ;
	if(curbucket_ >= d_->size_) return '\0' ;
	it_.reset(d_->array_[curbucket_]) ;
      }
    }
    return it_.current() ;
  }

  void setdata(void *data) {
    it_.setdata(data);
  }
} ;


#endif
