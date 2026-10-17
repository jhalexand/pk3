/*************************************************************************/
/*    NAME: Elaine Chen                                                  */
/*    ACCT: eyc                                                          */
/*    FILE: PKObject.h                                                   */
/*    DATE: Tue Apr 22 18:27:14 1997                                     */
/*************************************************************************/


#ifndef PKOBJECT_HEADER
#define PKOBJECT_HEADER

#include <debug.h>
#include <VectorMath.h>
#include <PKids.h>

class PKObject {
public:
  PKObject() {}
  PKObject(PKID uniqueID, PKTypeID typeID,
	   const PKPoint& pos, const PKVector& vect)
    : _ID(uniqueID), _typeID(typeID), _pos(pos), _vector(vect) {}

  PKObject(PKID uniqueID, PKTypeID typeID)
    : _ID(uniqueID), _typeID(typeID), _pos(), _vector() {}

  PKObject(const PKObject& other)
    : _ID(other._ID), _typeID(other._typeID),
      _pos(other._pos), _vector(other._vector) {}
      
  PKObject& operator = (const PKObject& other) {
      _ID     = other._ID;
      _typeID = other._typeID;
      _pos    = other._pos;
      _vector = other._vector;
      return *this;
  }

  virtual ~PKObject() {}

  boolean operator == (const PKObject& other) const {
    return getUniqueID()==other.getUniqueID();
  }

  //mutators
  void setPosition(const PKPoint& newpos) {
    _pos = newpos; }
  int setVector (const PKVector& vect) {
    if(_vector==vect) return 0;
    _vector = vect; return -1;
  }
  void setTypeID(PKTypeID type) {
    _typeID = type; }
  void setUniqueID(PKID id) {
    _ID = id; }

  //accessors
  const PKPoint& getPosition() const {
    return _pos; }
  const PKVector& getVector() const {
    return _vector; }
  PKTypeID getTypeID() const {
    return _typeID; }
  PKID getUniqueID() const {
    return _ID; }

protected:
  PKID     _ID;
  PKTypeID _typeID;
  PKPoint  _pos;
  PKVector _vector;
};

#endif
