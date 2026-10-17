/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: dla                                                 */
/*    FILE: GRKeyMap.h                                          */
/*    ASGN:                                                     */
/*    DATE: Wed Apr 23 18:02:33 1997                            */
/****************************************************************/


#ifndef GRKEYMAP_HEADER
#define GRKEYMAP_HEADER

#include <Xm/MainW.h>
#include <PKKey.h>

class GRKeyMap {
public:

  GRKeyMap (KeySym sym, PKKey key) : sym_(sym), key_(key) {}
  ~GRKeyMap() {}

public:

  KeySym sym_;
  PKKey key_;
};

#endif
