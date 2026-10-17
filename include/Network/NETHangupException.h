/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: bh                                                  */
/*    FILE: NETHangupException.h                                */
/*    ASGN:                                                     */
/*    DATE: Wed Apr 23 11:26:33 1997                            */
/****************************************************************/


#ifndef NETHANGUPEXCEPTION_HEADER
#define NETHANGUPEXCEPTION_HEADER

#include <stdio.h>
#include "Exception.h"

// a boolean data type
#define boolean int
#define true -1
#define false 0

class NETHangupException : public Exception {
public:
  NETHangupException() : Exception() {}
  virtual void print() { fprintf(stderr, "server hung up\n"); }
  virtual boolean isBad() { return true ; }
} ;

#endif
