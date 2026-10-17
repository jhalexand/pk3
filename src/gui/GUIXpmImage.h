/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: dla, modified slightly by bh                        */
/*    FILE: GUIXpmImage.h                                       */
/*    ASGN:                                                     */
/*    DATE: Tue Apr 22 12:15:13 1997                            */
/****************************************************************/


#ifndef GUIXPMIMAGE_HEADER
#define GUIXPMIMAGE_HEADER

#include <Xm/Xm.h>
#include <hashtable.h>

class GUIXpmImage {
private:
  Display *dsp_ ;
  GC gc_;
  Pixmap image_;
  Pixmap mask_;

  int width_, height_; // dimensions of Xpm

public:
  GUIXpmImage (const char *xpmfile, Widget drawingwindow);
  virtual ~GUIXpmImage();

  Pixmap getImage() const { return image_; }
  Pixmap getMask() const { return mask_; }
  GC getGraphicsContext() const { return gc_; }

  void draw(Widget drawWindow) ;

  void addCallback(Widget target);
  void remCallback(Widget target);

private:
  static void static_redrawCallback(Widget w, void *thus, void*) {
    ((GUIXpmImage*)thus)->draw(w);
  }
};

#endif
