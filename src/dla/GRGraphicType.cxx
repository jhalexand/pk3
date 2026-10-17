/*************************************************************************
 *    NAME: David Akers
 *    USER: dla
 *    FILE: GRGraphicType.cxx
 *    DATE: Tue Apr 22  1:38:16 US/Eastern 1997
 *************************************************************************/
#include "GRGraphicType.h"
#include <PKids.h>
#include "GR_local.h"

/*************************************************************************
 * Function Name: GRGraphicType::GRGraphicType
 * Parameters: Pixmap image, Pixmap mask, int numframes, int numanims
 * Effects: 
 *************************************************************************/

GRGraphicType::GRGraphicType(Pixmap image, Pixmap mask, int numframes, int numanims, GC graphicscontext, Widget drawingwindow)
{

  drawing_window = drawingwindow;
  graphics_context = graphicscontext;
  //cout << (int) graphics_context << endl;
  //graphics_context = XCreateGC (XtDisplay (drawing_window), 
  //RootWindowOfScreen (XtScreen (drawing_window)), 0, NULL);

  //XSetClipMask(XtDisplay(drawingwindow), graphics_context, mask_);
  
  image_ = image;
  mask_ = mask;

  //XSetClipMask(XtDisplay(drawingwindow), graphics_context, mask_);
  
  num_frames = numframes;
  num_anims = numanims;

  if (num_anims > 0)
    {
  anims_ = new GRAnimationSequence*[numanims];
  for (int i =0; i < numanims; i++)
   { anims_[i] = NULL;}
    }
  else anims_ = NULL;
  
  if (num_frames > 0)
    {
      frames_ = new GRFrame*[num_frames];
    }
   else frames_ = NULL;
  default_frame = NULL;
}


/*************************************************************************
 * Function Name: GRGraphicType::~GRGraphicType
 * Parameters: 
 * Effects: 
 *************************************************************************/

GRGraphicType::~GRGraphicType()
{

  for (int i = 0; i < num_anims; i++)
    {
      if (anims_[i]) delete anims_[i];
    }
  if (anims_) delete[] anims_;
  for (int j = 0; j < num_frames; j++)
    {
      if (frames_[j]) delete frames_[j];
    }
  if (frames_) delete[] frames_;
  if (default_frame) delete default_frame;

}


/*************************************************************************
 * Function Name: GRGraphicType::addFrame
 * Parameters: int framenum, GRFrame *frame
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GRGraphicType::addFrame(int framenum, GRFrame *frame)
{

  frames_[framenum] = frame;
  
}


/*************************************************************************
 * Function Name: GRGraphicType::addAnimationSequence
 * Parameters: int sequencenum, GRAnimationSequence *sequence
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GRGraphicType::addAnimationSequence(int sequencenum, GRAnimationSequence *sequence)
{
  anims_[sequencenum] = sequence;
}


/*************************************************************************
 * Function Name: GRGraphicType::animate
 * Parameters: int currentframe
 * Returns: int
 * Effects: 
 *************************************************************************/
int
GRGraphicType::animate(PKAnimID animID, int currentframe)
{
  if (animID == PK_ANIM_NOT) return GR_REVERT_TO_DEFAULT_FRAME;
  int where_to_go = (*(anims_[animID]))[currentframe+1];
  if (where_to_go == GR_REPEAT_FRAME) return currentframe;
  if (where_to_go == GR_REVERT_TO_DEFAULT_FRAME) return where_to_go;
  if (where_to_go == GR_REVERT_TO_INITIAL_FRAME) return 0; // repeat anim
  return currentframe+1;
}


/*************************************************************************
 * Function Name: GRGraphicType::getFrame
 * Parameters: PKAnimationID animID, int framenum
 * Returns: GRFrame *
 * Effects: 
 *************************************************************************/
GRFrame *
GRGraphicType::getFrame(PKAnimID animID, int framenum)
{
  if (animID == PK_ANIM_NOT) return default_frame;
  int frameindex = (*(anims_[animID]))[framenum];
  if (frameindex == GR_REPEAT_FRAME) return frames_[(*(anims_[animID]))[framenum-1]];
  if (frameindex == GR_REVERT_TO_DEFAULT_FRAME) return default_frame;
  return frames_[(*(anims_[animID]))[framenum]];
}


/*************************************************************************
 * Function Name: GRGraphicType::draw
 * Parameters: Pixmap target, GRScreenPoint &position, int animID, int framenum
 * Returns: void
 * Effects: 
 *************************************************************************/
void
GRGraphicType::draw(Pixmap target, GRScreenPoint &position, PKAnimID animID, int framenum)
{

  GRFrame *frame = getFrame (animID, framenum);

  int framexstart, frameystart, framexend, frameyend;

  framexstart = frame->getStart()[0];
  framexend = frame->getEnd()[0];
  frameystart = frame->getStart()[1];
  frameyend = frame->getEnd()[1];

  /*
  cout << "Size of frame is: " << (int) (framexend-framexstart) << "x" <<
(frameyend-frameystart) << endl;
  */

  //cout << "Size of frame is: " << (int) (frame->getEnd()[0] - frame->getStart()[0]);
  int xtarget = position[0]-(framexend-framexstart)/2;
  int ytarget = position[1]-(frameyend-frameystart)/2;

  //XSetClipMask(XtDisplay(drawing_window), graphics_context, mask_);
  
  XSetClipOrigin(XtDisplay(drawing_window), graphics_context,
  xtarget-framexstart, ytarget - frameystart);
  
  XCopyArea (XtDisplay (drawing_window), image_, target, graphics_context, framexstart, frameystart, framexend-framexstart, frameyend-frameystart, xtarget, ytarget);
}










