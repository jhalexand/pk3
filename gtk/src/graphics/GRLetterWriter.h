/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: dla                                                 */
/*    FILE: GRLetterWriter.h                                    */
/*    ASGN:                                                     */
/*    DATE: Sat Apr 26 01:01:02 1997                            */
/****************************************************************/


#ifndef GRLETTERWRITER_HEADER
#define GRLETTERWRITER_HEADER

#include "GREngine.h"

class GREngine;

/*static int letterxposition[] =
{
  1, 15, 27, 41, 55, 66, 77, 92, 105, 111
};
static int letteryposition[] =
{
  242, 242, 242, 242, 242, 242, 242, 242, 242,
  242, 242, 242, 242, 242, 242, 242, 242, 242
};*/

static int letterxposition[] =
{
  1, 11, 20, 30, 40, 48, 56, 67, 77, 81, 88, 98, 106, 119, 128, 139, 147,
  158, 1, 10, 19, 29, 39, 53, 64, 74, 82 
};

static int letteryposition[] =
{
  176, 176, 176, 176, 176, 176, 176, 176, 176, 176,
  176, 176, 176, 176, 176, 176, 176, 176, 186, 186,
  186, 186, 186, 186, 186, 186
};

class GRLetterWriter
{
public:

  GRLetterWriter(Widget drawingwindow, Pixmap workarea, GC graphicscontext);
  ~GRLetterWriter();
  void printString (int x, int y, const char *);
  void printChar (int x, int y, char);

private:

  GC graphics_context;
  Pixmap work_area;
  Widget drawing_window;
  GRXpmImage *xpm_image;
};
  

#endif
