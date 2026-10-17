/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: cs032059                                            */
/*    FILE: bh_defs.h                                           */
/*    ASGN:                                                     */
/*    DATE: Sun Mar 16 16:17:08 1997                            */
/*    NOTE: Just some random defines, debugging macros, etc     */
/****************************************************************/


#ifndef BH_DEFS_HEADER
#define BH_DEFS_HEADER

#ifndef NULL
#define NULL 0
#endif
// I prefer lowercase
#define null NULL

#ifndef STRLEN
#define STRLEN 256
#endif

// get a boolean data type; g++ has one (draft standard implementation);
// otherwise, just define boolean to have a sane interpretation
// note that checking if(a==true) will not always do the same as if(a), since
// a could be non-zero, but not -1.
#ifdef __GNUC__
#ifdef __cplusplus
#define boolean bool
#endif
#else // not gnuc
#define boolean int
#define true  -1
#define false  0
#endif


/* get dprintfs that flush output nicely and have indentation, and a
   message stating that the method is unimplemented */
extern int __dprintfLevel_ ;
void __dprintf_();



#if (defined(USEDPRINTF)) || (!defined(NDEBUG) && !defined(NODPRINTF))
#include <iostream.h>
#include <stdio.h>
#define dprintfLevel() __dprintfLevel_
#define dprintfLevelUp() { __dprintfLevel_++ ; }
#define dprintfLevelDown() \
        { if(__dprintfLevel_ >0) __dprintfLevel_-- ; }
#define dprintfLevelSkip(i) { __dprintfLevel_ = (i)<=0 ? 0 : (i) ; }
#define dprintf(str) { __dprintf_() ; printf str ; fflush(stdout) ;}
#define dprintfNoLevel(str) { printf str ; fflush(stdout) ;}
#define dprintf2(code,str) { __dprintf_() ; printf("[%.10s] ", code) ; printf str ; fflush(stdout); }

#else
#define dprintfLevelUp()
#define dprintfLevelDown()
#define dprintfLevelSkip(i)
#define dprintf(str)
#define dprintfNoLevel(str)
#define dprintf2(code,str)
#endif

#ifndef NDEBUG
#include <stdio.h>
#define unimplemented(func) fprintf(stderr, "unimplemented: %s in line %d of %s\n", func, __LINE__, __FILE__)
#include <assert.h>
#else
#define unimplemented(func)
#define assert(condition)
#endif /* NDEBUG */

#endif
