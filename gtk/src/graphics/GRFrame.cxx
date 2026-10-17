/*************************************************************************
 *    NAME: David Akers
 *    USER: dla
 *    FILE: GRFrame.cxx
 *    DATE: Tue Apr 22 22:39:25 US/Eastern 1997
 *************************************************************************/
#include "GRFrame.h"
#include "GR_local.h"

/*************************************************************************
 * Function Name: GRFrame::GRFrame
 * Parameters: GRScreenPoint start, GRScreenPoint end
 * Effects: 
 *************************************************************************/

GRFrame::GRFrame(GRScreenPoint start, GRScreenPoint end)
{
  start_ = start; end_ = end;
}


/*************************************************************************
 * Function Name: GRFrame::intersect
 * Parameters: GRFrame *other
 * Returns: int
 * Effects: 
 *************************************************************************/
int
GRFrame::intersect(GRFrame *other)
{
  if (other == this) return FALSE;
 
  /*
  if ((start_[0] > other->end_[0] || start_[0] < other->start_[0]) &&
      (end_[0] > other->end_[0] || end_[0] < other->start_[0]))
    return FALSE;
  if ((start_[1] > other->end_[1] || start_[1] < other->start_[1]) &&
      (end_[1] > other->end_[1] || end_[1] < other->end_[1]))
    return FALSE;*/

  /*if ((start_[0] > other->start_[0] && start_[0] < other->end_[0] &&
      start_[1] > other->start_[1] && start_[1] < other->end_[1]) ||
      (end_[0] > other->start_[0] && end_[0] < other->end_[0] &&
      end_[1] > other->start_[1] && end_[1] < other->end_[1]) ||
      (start_[0] > other->start_[0] && start_[0] < other->end_[0] &&
      end_[1] > other->start_[1] && end_[1] < other->end_[1]) ||
      (end_[0] > other->start_[0] && end_[0] < other->end_[0] &&
      start_[1] > other->start_[1] && start_[1] < other->end_[1]))      
  return TRUE;
   else return FALSE;*/

  if (MAX (other->start_[0], start_[0]) > MIN (other->end_[0], end_[0]) ||
      MAX (other->start_[1], start_[1]) > MIN (other->end_[1], end_[1]))
    return FALSE;
  else return TRUE;
}


/*************************************************************************
 * Function Name: GRFrame::~GRFrame
 * Parameters: 
 * Effects: 
 *************************************************************************/

GRFrame::~GRFrame()
{
}


void GRFrame::mergeFrame (GRFrame *other)
{
  int startx, starty, endx, endy;
  if (other->start_[0] < start_[0]) start_.setCoord (0,  other->start_[0]);
  if (other->start_[1] < start_[1]) start_.setCoord (1,  other->start_[1]);
  if (other->end_[1] > end_[1]) end_.setCoord (1, other->end_[1]);
  if (other->end_[0] > end_[0]) end_.setCoord (0, other->end_[0]);
}




