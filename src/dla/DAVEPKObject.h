/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: dla                                                 */
/*    FILE: DAVEPKObject.h                                      */
/*    ASGN:                                                     */
/*    DATE: Wed Apr 23 20:47:31 1997                            */
/****************************************************************/


#ifndef DAVEPKOBJECT_HEADER
#define DAVEPKOBJECT_HEADER
#include <VectorMath.h>

class PKObject {

public:
  
  PKObject() {anim_ID = PK_ANIM_NOT;}
  PKObject (int x, int y) {p_ = PKPoint (x, y); anim_ID = PK_ANIM_NOT;}
  PKPoint getPosition() {return p_;}
  PKAnimID getAnimID() {return anim_ID;}
  void setAnimID (PKAnimID id) {anim_ID = id;}
  ~PKObject() {}

  PKPoint p_;
  PKAnimID anim_ID;
  PKVector velocity_;
};

#endif
