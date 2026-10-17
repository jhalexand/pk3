/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: cs032082                                            */
/*    FILE: PKClientObject.h                                    */
/*    ASGN:                                                     */
/*    DATE: Thu May  1 16:56:22 1997                            */
/****************************************************************/


#ifndef PKCLIENTOBJECT_HEADER
#define PKCLIENTOBJECT_HEADER
#include <PKObject.h>
#include <sys/time.h>

class PKClientObject : public PKObject {
public:
    PKClientObject(PKID uniqueID, PKTypeID typeID,
		   const PKPoint& pos, const PKVector& vect)
      : PKObject(uniqueID, typeID, pos, vect) {animation_ = PK_ANIM_NOT;
    timestamp_ = gethrtime();}
    PKClientObject(PKID uniqueID, PKTypeID typeID)
	   : PKObject(uniqueID, typeID) {}
  //accessors
  hrtime_t getTime() {return timestamp_;}
  PKAnimID getAnimation() {return animation_;}
  //mutators
  void setTime(hrtime_t time) {timestamp_ = time;}
  void setAnimation(PKAnimID id) {animation_ = id;}
protected:
  hrtime_t timestamp_;
  PKAnimID animation_;
};
		  
   

#endif
