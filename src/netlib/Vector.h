/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: bh                                                  */
/*    FILE: Vector.h                                            */
/*    ASGN:                                                     */
/*    DATE: Thu Apr  3 02:27:27 1997                            */
/****************************************************************/


#ifndef VECTOR_HEADER
#define VECTOR_HEADER

#include <debug.h>
#include <errno.h>
#include "Exception.h"


/****************************************************************/
/* CLASS NAME :  Vector                                         */
/* A resizing array with good facilities to append data but     */
/* none to remove.  Externally, all you care about is that you  */
/* can append or appendAndSet, or access an element by its index*/
/* Also, the [] operator returns a char by reference, so you    */
/* can modify the vector as if it were just an array like that. */
/*                                                              */
/****************************************************************/


class Vector {
private:
  int size_ ; // the current allocated size
  int index_; // the current size used by the user
  int delta_; // the amount to add on overflow
  char *buffer_ ; // uses mmap
public:
  Vector(int size, int delta) ; // throws OutOfMemoryException
  virtual ~Vector() ;

  size() { return index_ ; }
  char& operator [] (int i) ; // should throw OutOfBoundsException
  char *underlyingArray() { return buffer_; }
  
  void append(const char *data, int len); // throws OutOfMemoryException
  void appendAndSet(const char *data, int dataLen, int setLen); // throws
  void appendAndSet(const char *data, int dataLen, int setLen, double iter, boolean repeat, const char *fill, int fillLen); // throws

  void setIndex(int index); // if past the current size, resizes to there
  void resize(int newSize); // resize to newSize, rounded to delta

  boolean toFile(const char *filename); // dumps the array to file; true on success
private:
  void resizeTo(int newSize); // resizes exactly
} ;

class OutOfMemoryException : public Exception {
private:
  Vector *v_ ;
public:
  OutOfMemoryException(Vector *v) : Exception(::errno, null) { v_ = v ; }
  Vector *vector() { return v_ ; }
} ;

#endif
