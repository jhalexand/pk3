/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: bh                                                  */
/*    FILE: PKAudioClass.h                                      */
/*    ASGN:                                                     */
/*    DATE: Tue May  6 08:14:18 1997                            */
/****************************************************************/


#ifndef PKAUDIOCLASS_HEADER
#define PKAUDIOCLASS_HEADER

#include <rplay.h> // for RPLAY*

class PKAudioClass {
private:
  RPLAY *rplayObject_ ;

public:
  PKAudioClass(const char *filename);
  virtual ~PKAudioClass();

  RPLAY *rplayObject() const { return rplayObject_; }
} ;


#endif
