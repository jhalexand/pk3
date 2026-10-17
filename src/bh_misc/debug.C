/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: bh                                                  */
/*    FILE: bh_defs.c                                           */
/*    ASGN:                                                     */
/*    DATE: Wed Apr  2 00:57:55 1997                            */
/****************************************************************/



#include "debug.h"

#include <iostream.h>
#include <stdio.h>

int __dprintfLevel_ = 0 ;

void __dprintf_() {
  cout.flush() ;
  for(int i=0; i<__dprintfLevel_; i++) {
    printf(" ") ;
  }
  fflush(stdout);
}
