/*************************************************************************
 *    NAME: David Akers
 *    USER: dla
 *    FILE: GRAnimationSequence.cxx
 *    DATE: Tue Apr 22  1:38:06 US/Eastern 1997
 *************************************************************************/
#include "GRAnimationSequence.h"

/*************************************************************************
 * Function Name: GRAnimationSequence::GRAnimationSequence
 * Parameters: int *frames
 * Effects: 
 *************************************************************************/

GRAnimationSequence::GRAnimationSequence(int *frames, int numframes)
{
frames_ = new int [numframes];
for (int i = 0; i < numframes; i++)
{
  frames_[i] = frames[i];}
}


/*************************************************************************
 * Function Name: GRAnimationSequence::~GRAnimationSequence
 * Parameters: 
 * Effects: 
 *************************************************************************/

GRAnimationSequence::~GRAnimationSequence()
{
  //delete[] frames_;
}


