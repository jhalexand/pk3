/*************************************************************************/
/*    NAME: Elaine Chen                                                  */
/*    ACCT: eyc                                                          */
/*    FILE: GEGameObject.h                                               */
/*    DATE: Thu Apr 24 23:04:35 1997                                     */
/*************************************************************************/

/**************************************************************************
 * This class represents my specialized generic PKObject.  All of the
 * other objects used by the game engine will subclass from this first
 * generic object.
 *************************************************************************/

#ifndef GEGAMEOBJECT_HEADER
#define GEGAMEOBJECT_HEADER

#include <PKids.h>
#include <PKObject.h>
#include <sys/time.h>

class PKGameEngine;

class GEContainer;

class GEGameObject : public PKObject {
public:
    GEGameObject(PKID id,
			  PKTypeID type,
			  int injury,
			  GEContainer* cont,
			  int width,
			  int height,
			  PKPoint& pos,
			  PKVector& vect,
			  PKGameEngine* engine);
    GEGameObject(PKID id,
			  PKTypeID type,
			  int injury,
			  GEContainer* cont,
			  int widthAdjust,
			  int heightAdjust,
			  PKGameEngine* engine);
    virtual ~GEGameObject();

    //virtual methods
    virtual void intersect(GEGameObject* obj) {}
    virtual void intersectWithBall(GEGameObject* ball) {}
    virtual void intersectWithWall(GEGameObject* wall) {}
    virtual void intersectWithPlayer(GEGameObject* player) {}
    virtual void intersectWithProjectile(GEGameObject* obj) {}
    virtual void adjustVelocity();

    virtual void update() {}

    //accessors
    GEContainer* getContainer()   {return _cont;}
    int getHeight()               {return _height;}
    int getWidth()                {return _width;}
    int getHeightAdjust()         {return _heightAdjust;}
    int getWidthAdjust()          {return _widthAdjust;}
    hrtime_t getTimeStamp() const {return _timestamp;}
    int getInjury()               {return _injury;}
    
    //mutators
    void setHeight(int newheight)    {_height = newheight;}
    void setWidth(int newwidth)      {_width = newwidth;}
    void setHeightAdjust(int adjust) {_heightAdjust = adjust;}
    void setWidthAdjust(int adjust)  {_widthAdjust = adjust;}
    void setTimeStamp(hrtime_t ts)   {_timestamp = ts;}
    void setInjury(int ouch)         {_injury = ouch;}

    //operators for use by the lists
    int operator==(const GEGameObject &obj) const;

protected:
    GEContainer* _cont; //list this object belongs to
    int _width;
    int _height;
    int _widthAdjust;
    int _heightAdjust;
    PKGameEngine* _engine;
    hrtime_t _timestamp;
    int _injury;
};

#endif

