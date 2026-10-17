/*****************************************************************

Guys, this is my CS 123 code from a ways back.. Just include this
file when you want to use vectors. 


*****************************************************************/
#ifndef PKMATH_H
#define PKMATH_H

#include <math.h>
#include <iostream.h>

class GRScreenPoint;
class PKVector;
class PKPoint;
class PKMatrix;

class PKVector {

 public:

   // Managers ----------------------------------------------------------

// This should probably create the vector (0,0,0)
  PKVector  () {v_[0] = 0;v_[1]=0;v_[2]=0;v_[3]=0;}

// This should copy the 3 doubles into the vector:  (x,y,z)
   PKVector  (double x, double y, double z = 0 ) {v_[0] = x; v_[1]=y;v_[2]=z;v_[3]=0;}

// This should copy the sent in vector
   PKVector  (const PKVector &p) {v_[0] = p[0]; v_[1]=p[1];v_[2]=p[2];}

// The desctructor
   ~PKVector (void) { }

// Set mutator

void setCoord (int coord, double value) { v_[coord] = value; }

   // Operators ---------------------------------------------------------

// This should return 1 if the vectors are equal, 0 otherwise.
   int        operator == (const PKVector &p) const {return (p[0] == v_[0] && p[1] == v_[1] && p[2] == v_[2]);}

// This should return 1 if the vectors are unequal, 0 otherwize.
   int        operator != (const PKVector &p) const {return !(p[0] != v_[0] || p[1] != v_[1] || p[2] != v_[2]);}

// This should set the vector equal to the other.
   PKVector & operator =  (const PKVector &p) {v_[0] = p[0]; v_[1] = p[1]; v_[2]=p[2]; return *this;}

   // Methods -----------------------------------------------------------

// This should return the i'th element of the vector (0-3)
   double     operator [] (const int i) const { return v_[i]; }

friend double dot (const PKVector &, const PKVector &);
friend PKVector cross (const PKVector &, const PKVector &);
friend PKVector operator * (double, const PKVector &);
friend PKVector operator / (const PKVector &, double);
friend PKVector operator + (const PKVector &, const PKVector &);
friend PKVector operator - (const PKVector &, const PKVector &);
friend PKPoint  operator - (const PKPoint  &, const PKVector &);
friend PKVector operator - (const PKVector &);
friend double length (const PKVector &);
friend PKVector operator * (const PKMatrix &, const PKVector &);
friend PKPoint operator + (const PKVector &, const PKPoint &);

protected:

double v_[4];
};


class PKPoint {

 public:
   // Managers ----------------------------------------------------------

// This should create a point with position (0,0,0)
   PKPoint  (void) {p_[0]=0;p_[1]=0;p_[2]=0;p_[3]=1;}

// This should make a point with position (x,y,z)
   PKPoint  (double x, double y, double z = 0) {p_[0]=x;p_[1]=y;p_[2]=z;p_[3]=1;}

// This should create a point with the same position as the one sent in
   PKPoint  (const PKPoint &p) {p_[0]=p[0];p_[1]=p[1];p_[2]=p[2];}

// The destructor
   ~PKPoint (void) { }

   // Operators ---------------------------------------------------------

// This should return 1 if the points are equal, 0 otherwise
   int        operator == (const PKPoint &p) const {return (p_[0] == p[0] && p_[1] == p[1] && p_[2] == p[2]);}

// This should return 1 if the points are unequal, 0 otherwise.
   int        operator != (const PKPoint &p) const {return (!(*this == p));}

//This should set current point to the one that was sent in.
   PKPoint &  operator =  (const PKPoint &p) {p_[0] = p[0]; p_[1] = p[1]; p_[2] = p[2]; return *this;}

// Mutator:

  void setCoord (int coord, double value) {p_[coord] = value;}

  //friend GRScreenPoint operator GRScreenPoint () const;

   // Methods -----------------------------------------------------------

// This should return the i'th component of the point (0-3)
   inline double     operator [] (const int i) const { return p_[i]; }

friend PKPoint  operator + (const PKVector &, const PKPoint  &);
friend PKPoint  operator - (const PKPoint  &, const PKVector &);
friend PKVector operator - (const PKPoint  &p, const PKPoint  &q);
friend PKPoint  operator * (const PKMatrix &, const PKPoint &);
friend PKMatrix rot_mat (const PKPoint &, const PKVector &, double);

private:
double p_[4];
};

static const double identity[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}; 
/*****************************************************************
CLASS PKMatrix
*****************************************************************/
class PKMatrix {
 private:
   double m_[4][4];

 public:

  void Print() {for (int x=0;x<=3;x++) {for(int y=0;y<=3;y++) {cout << m_[x][y] << " ";} cout << endl; }};
   // Managers ----------------------------------------------------------

// This should probably create the identity matrix.
  PKMatrix  (void) {for (int x = 0; x < 4; x++){for (int y = 0; y < 4; y++) {m_[y][x] = identity[x][y];}}}

// This should create a matrix with the same entries as the one sent in.
  PKMatrix  (const PKMatrix & m) {for (int x = 0; x < 4; x++){for (int y = 0; y < 4; y++) m_[x][y] = m.m_[x][y];}}

// The destructor
   ~PKMatrix (void) { }

   // Operators ---------------------------------------------------------

// This should return 1 if this matrix and the one sent in are equal, 0 
// if they are not.
  int        operator == (const PKMatrix &m) const {int condition=1;for (int x = 0; x < 4; x++) {for (int y = 0; y < 4; y++) {if (m_[x][y] != m.m_[x][y]) condition = 0;}} return condition;} 

// This should return 1 if this matrix and the one sent in are unequal, 0
// if they are equal.
   int        operator != (const PKMatrix &m) const {return !(*this == m);}

// This should set the entries of this matrix to the one sent in.
  PKMatrix & operator =  (const PKMatrix &m) {for (int x = 0; x < 4; x++){for (int y = 0; y < 4; y++) m_[x][y] = m.m_[x][y];} return *this;}

   // Methods -----------------------------------------------------------

// This should return the (i,j) element in the matrix.  Used with
//   int foo = mymatrix_(1,2);
   inline double     operator () (int i, int j) const { return m_[i][j];}

// This should return a reference to the (i,j) element in the matrix. 
// Used with 
//   mymatrix_(1,2)=3;
   double &   operator () (int i, int j) {return (double &) m_[i][j];}

  friend PKVector operator * (const PKMatrix &, const PKVector &);
  friend PKPoint  operator * (const PKMatrix &, const PKPoint &);
  friend PKMatrix operator * (const PKMatrix &, const PKMatrix &);
};


// Arithmetic Operators ------------------------------------------------

// --- Scalars (done)

// This should multiply the vector by the scalar, returning a vector
inline PKVector operator * (double s, const PKVector &v) {return PKVector(s*v.v_[0], s*v.v_[1], s*v.v_[2]);}
// This does the same.
inline PKVector operator * (const PKVector &v, double s) {return (s*v);}
// This divides a vector by a scalar
inline PKVector operator / (const PKVector &v, double s) {return PKVector(v.v_[0]/s, v.v_[1]/s, v.v_[2]/s);}


// --- Vectors and Points (done)

// This adds two vectors, and returns the resultant one
inline PKVector operator + (const PKVector &u, const PKVector &v) {return PKVector(u.v_[0] + v.v_[0], u.v_[1] + v.v_[1], u.v_[2] + v.v_[2]);}
// This adds a vector to a point, and returns the resultant point
inline PKPoint  operator + (const PKVector &v, const PKPoint  &p) {return PKPoint(v.v_[0] + p.p_[0], v.v_[1]+ p.p_[1], v.v_[2] + p.p_[2]);}
// This does the same.
inline PKPoint  operator + (const PKPoint  &p, const PKVector &v) {return v+p;}
// Note: no (point + point) operator

// This returns the negated vector
inline PKVector operator - (const PKVector &v) {return PKVector(-v.v_[0], -v.v_[1], -v.v_[2]);}
// This subtracts the second vector from the first, and returns the resultant.
inline PKVector operator - (const PKVector &u, const PKVector &v) {return PKVector(u.v_[0] - v.v_[0], u.v_[1] - v.v_[1], u.v_[2] - v.v_[2]);}
// This subtracts a vector from a point, and returns the resultant point.
inline PKPoint  operator - (const PKPoint  &p, const PKVector &v) {return PKPoint(p.p_[0]-v.v_[0], p.p_[1]-v.v_[1], p.p_[2] - v.v_[2]);}
// This returns the vector spanning point 1 and point 2
inline PKVector operator - (const PKPoint  &p, const PKPoint  &q) {return PKVector(p.p_[0]-q.p_[0], p.p_[1] - q.p_[1], p.p_[2] - q.p_[2]);}
// Note: no (vector - point) or (- point) operators


// --- Vector dot and cross products (done)

// Returns the dot product of the two vectors.
inline double dot (const PKVector &u, const PKVector &v) {return u.v_[0] * v.v_[0] + u.v_[1] * v.v_[1] + u.v_[2] * v.v_[2];}
// Returns the cross product of the two vectors.
inline PKVector cross (const PKVector &u, const PKVector &v) {return PKVector(u.v_[1]*v.v_[2] - u.v_[2]*v.v_[1], u.v_[2]*v.v_[0] - u.v_[0]*v.v_[2], u.v_[0]*v.v_[1] - u.v_[1] * v.v_[0]);}


// --- Length of a vector (done)

// returns the length of the vector
inline double length (const PKVector &v) {return sqrt(v.v_[0]*v.v_[0] + v.v_[1]*v.v_[1] + v.v_[2]*v.v_[2]); }


// --- Unit length vector pointing in the same direction (done)

// Returns the normalized vector 
inline PKVector normalize  (const PKVector &v) {return v/length(v);}



// --- Matrix Operators (done)

// Applies the matrix to the vector, returns the new vector.
inline PKVector operator * (const PKMatrix &m, const PKVector &v) {

return PKVector(m.m_[0][0]*v.v_[0] + m.m_[0][1]*v.v_[1] + m.m_[0][2]*v.v_[2] + m.m_[0][3]*v.v_[3], 
										   m.m_[1][0]*v.v_[0] + m.m_[1][1]*v.v_[1] + m.m_[1][2]*v.v_[2] + m.m_[1][3]*v.v_[3],

										   m.m_[2][0]*v.v_[0] + m.m_[2][1]*v.v_[1] + m.m_[2][2]*v.v_[2] + m.m_[2][3]*v.v_[3]);
}

// Applies the matrix to a point, returns the new point
inline PKPoint  operator * (const PKMatrix &m, const PKPoint &p) {PKPoint pnew(m.m_[0][0]*p.p_[0] + m.m_[0][1]*p.p_[1] + m.m_[0][2]*p.p_[2] + m.m_[0][3]*p.p_[3], 
										   m.m_[1][0]*p.p_[0] + m.m_[1][1]*p.p_[1] + m.m_[1][2]*p.p_[2] + m.m_[1][3]*p.p_[3],

										   m.m_[2][0]*p.p_[0] + m.m_[2][1]*p.p_[1] + m.m_[2][2]*p.p_[2] + m.m_[2][3]*p.p_[3]); 
 
double homog = m(3,0)*p[0] + m(3,1)*p[1] + m(3,2)*p[2] + m(3,3); 
pnew.p_[0] /= homog; pnew.p_[1] /= homog; pnew.p_[2] /= homog; pnew.p_[3] = 1; return pnew;  }

// Multiplies two matrices together, returns the resultant matrix
inline PKMatrix operator * (const PKMatrix &m, const PKMatrix &n) {PKMatrix result; 
PKMatrix m1 = m;
PKMatrix n1 = n;
for (int x = 0; x <= 3; x++)
  {
    for (int y = 0; y <= 3; y++)
      {
	result(x,y)=0;
	for (int index = 0; index <= 3; index++)
	  {
	    result.m_[x][y] += m.m_[x][index]*n.m_[index][y];
	  }
      }
  }

return result;
}


// Transforms --------------------------------------------------------

// Returns the identity matrix

inline PKMatrix ident_mat () {
return PKMatrix();
}

// returns a scaling transformation matrix, which will scale by the vector v

inline PKMatrix scale_mat (const PKVector &v) {
PKMatrix result;
for (int x = 0; x <= 2; x++)
  for (int y = 0; y <= 2; y++)
    {if (x == y) result(x,y) = v[x]; else result(x,y) = 0;} 
return result;
}

// Returns a translation matrix, which will translate by the vector v 
inline PKMatrix trans_mat (const PKVector &v) {
PKMatrix result;
for (int row = 0; row <= 2; row++)
  {result(row, 3) = v[row];}
return result;
}
// returns a rotation matrix effecting a rotation around the X axis by 
// specified radians
inline PKMatrix rotX_mat  (double radians) {
PKMatrix result; 
double cosfactor = cos(radians);
double sinfactor = sin(radians);
result(1,1) = cosfactor;
result(1,2) = -sinfactor;
result(2,1) = sinfactor;
result(2,2) = cosfactor;
return result;
}
// Returns a rotation matrix effecting rotation around the Y axis
inline PKMatrix rotY_mat  (double radians) {
PKMatrix result; 
double cosfactor = cos(radians);
double sinfactor = sin(radians);
result(0,0) = cosfactor;
result(0,2) = sinfactor;
result(2,0) = -sinfactor;
result(2,2) = cosfactor;
return result;

}
// Returns a rotation matrix effecting rotation around the Z axis
inline PKMatrix rotZ_mat  (double radians) {
PKMatrix result; 
double cosfactor = cos(radians);
double sinfactor = sin(radians);
result(0,0) = cosfactor;
result(0,1) = -sinfactor;
result(1,0) = sinfactor;
result(1,1) = cosfactor;
return result;
}

// Returns the transpose of a matrix
inline PKMatrix transpose (const PKMatrix &v) {
PKMatrix result;
for (int x = 0; x <= 3; x++)
  {
    for (int y = 0; y <= 3; y++)
      {
	result(x,y) = v(y,x);
      }
  }
return result;
}

// Returns a rotation matrix effecting a rotation around the given vector and
// point, by the specified number of radians.
inline PKMatrix rot_mat (const PKPoint  &p, const PKVector &v, double radians){

PKMatrix step1;
PKMatrix step2, step3, step4;
PKMatrix result;
PKVector norm_v = normalize(v);
step1 = trans_mat(PKVector(-p[0], -p[1], -p[2]));
double a = sqrt(norm_v[1]*norm_v[1] + norm_v[2]*norm_v[2]);
step2(1,1) = norm_v[2]/a;
step2(2,2) = norm_v[2]/a;
step2(2,1) = norm_v[1]/a;
step2(1,2) = -norm_v[1]/a;
step3(0,0) = a;
step3(2,2) = a;
step3(0,2) = -norm_v[0];
step3(2,0) = norm_v[0];
step4 = rotZ_mat (radians);

result = trans_mat(PKVector(p[0], p[1], p[2]))*transpose(step2)*transpose(step3)*step4*step3*step2*step1;
return result;
}
	
// Returns the inverse matrix of scale_mat()
inline PKMatrix inv_scale_mat (const PKVector &v){
return scale_mat(PKVector(1/v[0], 1/v[1], 1/v[2]));
}
// Returns the inverse matrix of trans_mat()
inline PKMatrix inv_trans_mat (const PKVector &v){return trans_mat(PKVector(-v));}
// Returns the inverse matrix of rotX_mat()
inline PKMatrix inv_rotX_mat  (double radians){return transpose(rotX_mat(radians));}
// Returns the inverse matrix of rotY_mat()
inline PKMatrix inv_rotY_mat  (double radians){return transpose(rotY_mat(radians));}
// Returns the inverse matrix of rotZ_mat()
inline PKMatrix inv_rotZ_mat  (double radians){return transpose(rotZ_mat(radians));}
// Returns the inverse matrix of rot_mat()
inline PKMatrix inv_rot_mat (const PKPoint  &p, const PKVector &v, double a){return rot_mat(p, v, -a);}


#endif  /* PKMATH_H */




