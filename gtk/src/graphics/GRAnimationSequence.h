/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: dla                                                 */
/*    FILE: GRAnimationSequence.h                               */
/*    ASGN:                                                     */
/*    DATE: Mon Apr 21 23:53:51 1997                            */
/****************************************************************/


#ifndef GRANIMATIONSEQUENCE_HEADER
#define GRANIMATIONSEQUENCE_HEADER

class GRAnimationSequence {

public:

  GRAnimationSequence() {}
  GRAnimationSequence (int *frames, int numplayers);
  ~GRAnimationSequence();
  int operator[] (int number) { return frames_[number]; }

private:

  int *frames_;

};
  

#endif
