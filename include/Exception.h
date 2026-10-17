/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: bh                                                  */
/*    FILE: Exception.h                                         */
/*    ASGN:                                                     */
/*    DATE: Tue Apr  1 21:53:31 1997                            */
/****************************************************************/


#ifndef EXCEPTION_HEADER
#define EXCEPTION_HEADER

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <debug.h>

/****************************************************************/
/* CLASS NAME :  Exception                                      */
/* A generic exception class off which you would subclass your  */
/* own exceptions.  Just construct one and throw it.            */
/* Basically, the assumption is that if the error number is 0,  */
/* it's an internal exception; if it's non-zero, it's a         */
/* bad exception, and should be printed to console before       */
/* exiting with status errno.                                   */
/*                                                              */
/****************************************************************/

const int DEFAULT_ERRNO = -1 ;

class Exception {
protected:
  int errno_ ;
  char *msg_ ; // malloc'd
public:
  Exception(int e, const char *m) : errno_(e), msg_(m?strdup(m):null) {}
  Exception(int e) : errno_(e), msg_(null) {}
  Exception(const char *m) : errno_(DEFAULT_ERRNO), msg_(m?strdup(m):null) {}
  Exception() : errno_(DEFAULT_ERRNO), msg_(null) {}
  virtual ~Exception() { if(msg_) free(msg_) ; msg_ = null; }
  virtual boolean isBad() { return errno_!=0; }
  virtual void print() { if(isBad() && msg_) { fprintf(stderr, "%s\n", msg_); } }
  virtual int errno() { return errno_ ; }
  virtual char *msg() { return msg_ ; }
} ;

#endif
