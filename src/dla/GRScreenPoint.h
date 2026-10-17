/****************************************************************/
/*    NAME:                                                     */
/*    ACCT: dla                                                 */
/*    FILE: GRScreenPoint.h                                     */
/*    ASGN:                                                     */
/*    DATE: Tue Apr 22 22:24:34 1997                            */
/****************************************************************/


#ifndef GRSCREENPOINT_HEADER
#define GRSCREENPOINT_HEADER

#include <VectorMath.h>
#include "GR_local.h"

class GRScreenPoint {

public:

  GRScreenPoint() {}
  GRScreenPoint (int x, int y) { p_[0] = x; p_[1] = y;}
  GRScreenPoint (const PKPoint &p) {p_[0] = (int) floor(p[0]); p_[1] = (int) floor(p[1]);}

  int operator == (const GRScreenPoint &other) const {if (other[0] == p_[0] && other[1] == p_[1]) return TRUE; else return FALSE;}
  
  int operator != (const GRScreenPoint &other) const {if (!(other == *this)) return TRUE; else return FALSE;}
  
  int operator[] (int coord) const {return p_[coord];}
  void setCoord (int coord, int value) {p_[coord] = value;}
  friend GRScreenPoint operator + (const GRScreenPoint &, const GRScreenPoint &);
  ~GRScreenPoint() {}

private:

  int p_[2];
};

inline GRScreenPoint  operator + (const GRScreenPoint &u, const GRScreenPoint &v)
{return GRScreenPoint (u.p_[0] + v.p_[0], u.p_[1] + v.p_[1]);}
  
#endif
