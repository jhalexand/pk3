/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: dla                                                 */
/*    FILE: GRGraphicType.h                                     */
/*    ASGN:                                                     */
/*    DATE: Mon Apr 21 23:30:23 1997                            */
/****************************************************************/


#ifndef GRGRAPHICTYPE_HEADER
#define GRGRAPHICTYPE_HEADER

#include "GRFrame.h"
#include "GRAnimationSequence.h"
#include <Xm/Xm.h>
#include <PKids.h>

class GRGraphicType {

public:

  GRGraphicType(Pixmap image, Pixmap mask, int numframes, int numanims, GC graphicscontext, Widget drawingwindow);
  ~GRGraphicType();
  virtual void addFrame (int framenum, GRFrame *frame);
  virtual void addAnimationSequence (int sequencenum, GRAnimationSequence *sequence);
  virtual void setDefaultFrame (GRFrame *frame) { default_frame = frame; }

  virtual GRFrame *getFrame (PKAnimID animID, int framenum);
  
  virtual void draw (Pixmap target, GRScreenPoint &position, PKAnimID animID, int framenum);
  virtual int animate (PKAnimID animID, int currentframe); // Returns the new frame.. 
  

private:

  GC graphics_context;            // Needs to know this to draw itself.
  int num_anims;                  // Number of animations used in the object.
  int num_frames; 		  // Number of frames used in the object.
  Pixmap image_;                  // The actual image we will draw.
  Pixmap mask_;                   // Mask so we can draw w/out killing bkground
  GRFrame **frames_;              // List of frames used in animations
  GRAnimationSequence **anims_;   // Array of animations indexed by anim_id
  GRFrame *default_frame;         // Default frame to use when not animating
  Widget drawing_window;          // Needs to know this to draw itself.

};

#endif
