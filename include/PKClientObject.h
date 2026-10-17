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
      : PKObject(uniqueID, typeID, pos, vect) {
          animation_ = PK_ANIM_NOT;
          timestamp_ = gethrtime();
    }

    PKClientObject(PKID uniqueID, PKTypeID typeID)
	   : PKObject(uniqueID, typeID) { }

    PKClientObject(const PKObject& other) : PKObject(other) {
        animation_ = PK_ANIM_NOT;
        timestamp_ = gethrtime();
    }

    PKClientObject(const PKClientObject& other) : PKObject(other) {
        animation_ = other.animation_;
        timestamp_ = other.timestamp_;
    }
    
    PKClientObject& operator = (const PKClientObject& other) {
        PKObject::operator = (other);
        animation_ = other.animation_;
        timestamp_ = other.timestamp_;
        return *this;
    }

    //accessors
    hrtime_t getTime()      const { return timestamp_; }
    PKAnimID getAnimation() const { return animation_; }

    //mutators
    void setTime(hrtime_t time)    {timestamp_ = time;}
    void setAnimation(PKAnimID id) {animation_ = id;}

    void update() {
        update(gethrtime());
    }

    void update(hrtime_t newstamp) {
        hrtime_t elapsed = newstamp - timestamp_;
        _pos = _pos + (elapsed*_vector*.00000001);
        timestamp_ = newstamp;
    }


protected:
    hrtime_t timestamp_;
    PKAnimID animation_;
};

#endif
