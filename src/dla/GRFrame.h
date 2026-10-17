/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: dla                                                 */
/*    FILE: GRFrame.h                                           */
/*    ASGN:                                                     */
/*    DATE: Mon Apr 21 23:50:34 1997                            */
/****************************************************************/


#ifndef GRFRAME_HEADER
#define GRFRAME_HEADER

#include <VectorMath.h>
#include "GRScreenPoint.h"

class GRFrame {

public:
  GRFrame () {}
  GRFrame (GRScreenPoint start, GRScreenPoint end);
  virtual GRScreenPoint getStart() { return start_; }
  virtual GRScreenPoint getEnd() { return end_; }
  virtual int intersect (GRFrame *other);
  virtual void mergeFrame (GRFrame *other);
  virtual void print() { cout << start_[0] << start_[1] << " x " <<
end_[0] << end_[1] << endl; }
  ~GRFrame();

private:

  GRScreenPoint start_;
  GRScreenPoint end_;
};

#endif
