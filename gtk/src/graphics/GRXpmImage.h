/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: dla                                                 */
/*    FILE: GRXpmImage.h                                        */
/*    ASGN:                                                     */
/*    DATE: Tue Apr 22 12:15:13 1997                            */
/****************************************************************/


#ifndef GRXPMIMAGE_HEADER
#define GRXPMIMAGE_HEADER

#include <Xm/Xm.h>

class GRXpmImage {

public:
  
  GRXpmImage (const char *xpmfile, Widget drawingwindow);
  Pixmap getImage() const {return image_;}
  Pixmap getMask() const {return mask_;}
  GC getGraphicsContext() const {return graphics_context;}
  ~GRXpmImage();

private:

  GC graphics_context;
  Pixmap image_;
  Pixmap mask_;
  Widget drawing_window;

};

#endif
