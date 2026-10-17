/*************************************************************************
 *    NAME: David Akers
 *    USER: dla
 *    FILE: GROnscreenGraphic.cxx
 *    DATE: Tue Apr 22 22:36:20 US/Eastern 1997
 *************************************************************************/
#include "GROnscreenGraphic.h"
#include <PKClientObject.h>



/****************************************************************/
/*                                                              */
/* Function Name: operator ==                                   */
/* Parameters:                                                  */
/* Returns:                                                     */
/* Effects:                                                     */
/*                                                              */
/****************************************************************/



int GROnscreenGraphic::operator==(const GROnscreenGraphic &obj) const
{
    return (this == &obj);
}

/*************************************************************************
 * Function Name: GROnscreenGraphic::GROnscreenGraphic
 * Parameters: GRGraphicType *grtype, PKID uniqueID
 * Effects: 
 *************************************************************************/

GROnscreenGraphic::GROnscreenGraphic(GRGraphicType *grtype, PKID uniqueID, GRScreenPoint position)
{
  is_drawn = FALSE;
  unique_ID = uniqueID;
  gr_type = grtype;
  anim_id = PK_ANIM_NOT;
  frame_number = -2; // Default frame
  position_ = position; 
}


/*************************************************************************
 * Function Name: GROnscreenGraphic::~GROnscreenGraphic
 * Parameters: 
 * Effects: 
 *************************************************************************/

GROnscreenGraphic::~GROnscreenGraphic()
{
}

/*************************************************************************
 * Function Name: GROnscreenGraphic::updateStatus
 * Parameters: PKObject *newposition
 * Returns: int
 * Effects: 
 *************************************************************************/
int
GROnscreenGraphic::updateStatus(PKClientObject *newposition)
{
  PKPoint newpos;
  newpos = newposition->getPosition();
  PKAnimID newanimID;
  newanimID = newposition->getAnimation();

  int returnvalue;

  GRScreenPoint newscreenpos = GRScreenPoint (newpos);

  if (newanimID != anim_id) frame_number = 0;
  
  if (position_ != newscreenpos ||
      newanimID != anim_id)
    returnvalue = TRUE;
  else
    returnvalue = FALSE;

  anim_id = newanimID; // Object is now animating with a new animation id
  
  if (anim_id == PK_ANIM_NOT) frame_number = GR_REVERT_TO_DEFAULT_FRAME;
  
  position_ = newscreenpos;

  return returnvalue;
}


/*************************************************************************
 * Function Name: GROnscreenGraphic::draw
 * Parameters: Pixmap target
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GROnscreenGraphic::draw(Pixmap target) const
{
  gr_type->draw (target, (GRScreenPoint &) position_, anim_id, frame_number);
}


/*************************************************************************
 * Function Name: GROnscreenGraphic::getFrame
 * Parameters: 
 * Returns: GRFrame *
 * Effects: 
 *************************************************************************/
GRFrame *
GROnscreenGraphic::getFrame() const
{
  GRFrame *temp = gr_type->getFrame (anim_id, frame_number);
  int xsize,ysize;
  xsize = temp->getEnd()[0] - temp->getStart()[0];
  ysize = temp->getEnd()[1] - temp->getStart()[1];
  //cout << xsize << " " << ysize << endl;
  GRFrame *returnframe = new GRFrame (GRScreenPoint (position_[0]-xsize/2, position_[1]-ysize/2), GRScreenPoint (position_[0] + xsize/2,position_[1] + ysize/2));
  return returnframe;
  
}


/*************************************************************************
 * Function Name: GROnscreenGraphic::animate
 * Parameters: 
 * Returns: int
 * Effects: returns TRUE if the object changed animation states.
 *************************************************************************/
int
GROnscreenGraphic::animate(PKClientObject *object)
{
  int newfnum = gr_type->animate (anim_id, frame_number);
  int retval;
  if (newfnum == frame_number) retval = 0; else retval = 1;
  frame_number = newfnum;
   if (frame_number == GR_REVERT_TO_DEFAULT_FRAME && retval && (anim_id == object->getAnimation())) object->setAnimation(PK_ANIM_NOT);
  return retval;
}




