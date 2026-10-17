/*************************************************************************/
/*    NAME: Elaine Chen                                                  */
/*    ACCT: eyc                                                          */
/*    FILE: PKPlayer.h                                                   */
/*    DATE: Tue Apr 22 16:14:17 1997                                     */
/*************************************************************************/


#ifndef PKPLAYER_HEADER
#define PKPLAYER_HEADER

#include <PKids.h>

class PKPlayer : public PKObject {

public:
    PKPlayer(int uniqueID, PKType graphic); //init pos based on PKTyp
    virtual ~PKPlayer();

    virtual void moveUp();
    virtual void moveDown();
    virtual void moveLeft();
    virtual void moveRight();
    virtual void punch();
    virtual void kick();
    virtual void specialMove1();
    virtual void specialMove2();
    virtual void specialMove3();
    //too many? anything else in superclass?

protected:
    int _playerNum;
    int _life; //percentage???


};

#endif
