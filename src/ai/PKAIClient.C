/*************************************************************************
 *    NAME: Benoit Hudson
 *    USER: bh
 *    FILE: PKAIClient.C
 *    DATE: Sun May  4  7:15:04 US/Eastern 1997
 *************************************************************************/
#include "PKAIClient.h"

#include <PKClientNetworkInterface.h>
#include <PKGameClasses.h>
#include <PKids.h>


const hrtime_t PKAIClient::FIRE_RATE = 5000000000 ; // every 5 seconds
const double PKAIClient::FIRE_OFF = 25;
const int PKAIClient::UP = -1 ;
const int PKAIClient::DOWN = 1 ;
const int PKAIClient::STILL = 0 ;

const long UPDATE_TIME = 100;

boolean
epsilon_close(double a, double b, double epsilon) {
    return fabs(a-b) < epsilon;
}

/*************************************************************************
 * Function Name: PKAIClient::PKAIClient
 * Parameters: const char *host, int port, int playerNum
 * Effects: 
 *************************************************************************/

PKAIClient::PKAIClient(const char *host, int port, int playerNum)
{
    // allow no X options, but we need the app to run (this is a hack)
    int zero = 0 ;
    XtAppInitialize(&app_, null, (XrmOptionDescList)NULL,
            0, &zero, null, null, null, 0);

    playerNum_ = playerNum;

    dprintf(("Opening connection to %s:%d as player %d\n",
            host, port, playerNum));
    net_ = new PKClientNetworkInterface(this, app_, host, port, playerNum_);
    lastFireTime_ = gethrtime();

    XtAppAddTimeOut(app_, UPDATE_TIME, static_updateCallback, this);
    XtAppMainLoop(app_);
}


/*************************************************************************
 * Function Name: PKAIClient::~PKAIClient
 * Parameters: 
 * Effects: 
 *************************************************************************/

PKAIClient::~PKAIClient()
{
    delete net_;
}


/*************************************************************************
 * Function Name: PKAIClient::enterGamePlay
 * Parameters: PKGameParameters& parms
 * Returns: void
 * Effects: 
 *************************************************************************/
    void
PKAIClient::enterGamePlay(const PKGameParameters&)
{
    unique_ = playerNum_ ; // works because we're assured it does
    net_->ready();
}


/*************************************************************************
 * Function Name: PKAIClient::addObject
 * Parameters: PKObject& obj
 * Returns: void
 * Effects: 
 *************************************************************************/
    void
PKAIClient::addObject(const PKObject& obj)
{
    PKClientObject *cobj = new PKClientObject(obj);
    if(unique_==obj.getUniqueID()) {
        dprintf(("ai client got itself (PKID %d, paddle %d)\n",
                obj.getUniqueID(), obj.getTypeID()));
        self_ = cobj;
        return ;
    }


    int type = obj.getTypeID();
    dprintf(("ai client adding object %d, type %d\n", obj.getUniqueID(), type));
    if(type==PK_TYPE_BALL) {
        dprintf(("    inserting into ball list\n"));
        follow_.put(obj.getUniqueID(), cobj);
        followID_ = obj.getUniqueID();
    }
    else if (type>=PK_PADDLE_MIN && type<=PK_PADDLE_MAX) {
        dprintf(("   inserting into target list\n"));
        target_.put(obj.getUniqueID(), cobj);
    }
    else {
        dprintf(("   ignoring\n"));
        delete cobj;
    }
}


/*************************************************************************
 * Function Name: PKAIClient::removeObject
 * Parameters: PKID id
 * Returns: void
 * Effects: 
 *************************************************************************/
void
PKAIClient::removeObject(PKID id)
{
    if(unique_ == id) {
        dprintf(("ai client died from lack of a life (PKID %d)\n", id));
        dprintf(("continuing to be a pain, though\n"));
        delete self_;
        self_ = null;
        return;
    }

    PKClientObject *cobj;
    dprintf(("ai client removing object %d", id));

    if( (cobj = follow_.remove(id))) { 
        dprintfNoLevel((" from ball list\n")); 
        delete cobj;
        return; 
    }

    if( (cobj = target_.remove(id))) { 
        dprintfNoLevel((" from target list\n")); 
        delete cobj;
        return; 
    }

    dprintfNoLevel((" (ignoring)\n"));
}


/*************************************************************************
 * Function Name: PKAIClient::update
 * Parameters: PKObject obj
 * Returns: void
 * Effects: 
 *************************************************************************/
    void
PKAIClient::update(const PKObject& obj)
{
    int type = obj.getTypeID();
    int uniq = obj.getUniqueID();

    if(unique_ == uniq) {
        dprintf(("ai client updating itself (PKID %d)\n", obj.getUniqueID()));
        *self_ = obj;

        return;
    }

    dprintf(("ai client updating object %d of type %d ", uniq, type));
    if(type==PK_TYPE_BALL) {
        dprintf(("in ball list\n"));
        PKClientObject *cobj = follow_.get(uniq);
        assert(cobj);
        *cobj = obj;
    }
    else if (type>=PK_PADDLE_MIN && type<=PK_PADDLE_MAX) {
        dprintf(("in target list\n"));
        PKClientObject *cobj = target_.get(uniq);
        assert(cobj);
        *cobj = obj;
    }
    else {
        dprintf(("but ignoring\n"));
    }
}


/*************************************************************************
 * Function Name: PKAIClient::updateAnimation
 * Parameters: PKID unique, PKAnimID id
 * Returns: void
 * Effects: if the animation is to hide, remove from the ball/user list,
 *          and insert into the hidden list; if it is to show, remove from
 *          the hidden list, and insert into the ball/user list.
 *************************************************************************/
    void
PKAIClient::updateAnimation(PKID unique, PKAnimID id)
{  
    PKClientObject *cobj;
    if(id==PK_ANIM_INVISIBLE) {
        if( (cobj = follow_.get(id)) ) {
            dprintf(("ai client hiding %d from ball list\n", unique));
            follow_.remove(id);
            hidden_.put(id, cobj);
        }
        else if ( (cobj=target_.get(id)) ) {
            dprintf(("ai client hiding %d from target list\n", unique));
            target_.remove(id);
            hidden_.put(id, cobj);
        }
        else {
            dprintf(("ai client ignoring hiding of %d\n", unique));
        }
    }
    else if(id==PK_ANIM_VISIBLE) {
        cobj = hidden_.get(id);
        assert(cobj);
        hidden_.remove(id);
        dprintf(("ai client unhiding %d\n", id));

        int type = cobj->getTypeID();
        dprintf(("ai client adding object of type %d\n", type));
        if(type==PK_TYPE_BALL) {
            dprintf(("    inserting into ball list\n"));
            follow_.put(id, cobj);
            followID_ = id;
        }
        else if (type>=PK_PADDLE_MIN && type<=PK_PADDLE_MAX) {
            dprintf(("   inserting into target list\n"));
            target_.put(id, cobj);
        }
        else {
            dprintf(("   ignoring\n"));
            delete cobj;
        }
    }
}


/*************************************************************************
 * Function Name: PKAIClient::gameStatus
 * Parameters: PKGameStatus& stat
 * Returns: void
 * Effects: "I don't give a shit"
 *************************************************************************/
    void
PKAIClient::gameStatus(const PKGameStatus&)
{
}


/*************************************************************************
 * Function Name: PKAIClient::static_updateCallback
 * Parameters: void *thus, XtIntervalId*
 * Returns: void
 * Effects: 
 *************************************************************************/
    void
PKAIClient::static_updateCallback(void *thus, XtIntervalId*)
{
    ((PKAIClient*)thus)->update();
}


/*************************************************************************
 * Function Name: PKAIClient::update
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
    void
PKAIClient::update()
{
    // self is null when we die (or haven't been born yet)
    if(self_ && follow_.size()>0) {
        dprintf(("\nai client doing its thing!!!\n"));
        
        PKClientObject *ball = follow_.get(followID_);
        if(!ball) {
            HTIterator<int,PKClientObject*> it(follow_);
            ++it;
            followID_ = it.key();
            ball = it.element();
        }
        assert(ball);

        int direction = (self_->getVector()[1]<0) ? UP :
                        (self_->getVector()[1]>0) ? DOWN :
                        STILL;

        hrtime_t newtime = gethrtime();

        self_->update(newtime);
        ball->update(newtime);

        const PKPoint& thisPt = self_->getPosition();
        const PKPoint& ballPt = ball->getPosition();

        dprintf(("\tcurrent state: (%f,%f) moving in (%f,%f); direction %d\n", 
                thisPt[0], thisPt[1], 
                self_->getVector()[0],   self_->getVector()[1],
                direction));
        dprintf(("\tball state:    (%f,%f) moving in (%f,%f)\n", 
                ballPt[0], ballPt[1], 
                ball->getVector()[0],   ball->getVector()[1]));

        // higher y means lower on-screen
        if(ballPt[1] > thisPt[1] && direction != DOWN) {
            dprintf(("\tSending PK_ACTION_PADDLE_DOWN\n"));
            net_->sendAction(PK_ACTION_PADDLE_DOWN);
        }
        else if(ballPt[1] < thisPt[1] && direction != UP) {
            dprintf(("\tSending PK_ACTION_PADDLE_UP\n"));
            net_->sendAction(PK_ACTION_PADDLE_UP);
        }

        if(newtime-lastFireTime_ > FIRE_RATE) {
            dprintf(("Looking at %d targets\n", target_.size()));
            for(HTIterator<int,PKClientObject*> it(target_); it; ++it) {
                const PKClientObject *cobj = it.element();
                const PKPoint& playerPt = cobj->getPosition();
                if(epsilon_close(thisPt[1],playerPt[1],FIRE_OFF)) {
                    dprintf(("\tSending PK_ACTION_PADDLE_SPECIAL_1 at %d\n",
                            cobj->getUniqueID()));
                    net_->sendAction(PK_ACTION_PADDLE_SPECIAL_1); // hopefully a projectile
                    lastFireTime_ = newtime;
                    break;
                } else {
                    dprintf(("Not firing at %d\n", cobj->getUniqueID()));
                }
            }
        }
    }

    XtAppAddTimeOut(app_, UPDATE_TIME, static_updateCallback, this);
}
