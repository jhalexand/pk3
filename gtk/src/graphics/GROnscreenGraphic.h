/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: dla                                                 */
/*    FILE: GROnscreenGraphic.h                                 */
/*    ASGN:                                                     */
/*    DATE: Sun Apr 20 19:07:42 1997                            */
/****************************************************************/


#ifndef GRONSCREENGRAPHIC_HEADER
#define GRONSCREENGRAPHIC_HEADER

#include "GRGraphicType.h"
#include <PKids.h>

class PKClientObject;

class GROnscreenGraphic {

public:

  GROnscreenGraphic(GRGraphicType *grtype, PKID uniqueID, GRScreenPoint position);
  ~GROnscreenGraphic();
  virtual int updateStatus (PKClientObject *newposition); // Returns TRUE if changed 
  virtual void draw(Pixmap target) const; // Tells the object to draw itself
  virtual GRFrame *getFrame() const; // frame that surrounds the object.
  virtual int animate(PKClientObject *);      // Call this every graphics callback.
  virtual PKID getID() {return unique_ID;}
  virtual int isDrawn() { return is_drawn; }
  virtual void initialize() { is_drawn = TRUE; }

  int operator==(const GROnscreenGraphic &obj) const;

 
private:

  PKID unique_ID;         // The unique ID given to the graphic by the server.
  GRGraphicType *gr_type; // Graphics type pointer (knows how to draw)
  PKAnimID anim_id; // Current animation we are running.
  int frame_number;      // Current frame we are on.
  GRScreenPoint position_;     // Position of the object (on screen)
  int is_drawn;
  
};

#endif
