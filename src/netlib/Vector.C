/*************************************************************************
 *    NAME: Benoit Hudson
 *    USER: bh
 *    FILE: Vector.C
 *    DATE: Thu Apr  3  2:31:47 US/Eastern 1997
 *************************************************************************/
#include "Vector.h"
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/*************************************************************************
 * Function Name: Vector::Vector
 * Parameters: int size, int delta
 * Effects: allocates an initial size, and inits variables to what they
 *          should be.
 *************************************************************************/

Vector::Vector(int size, int delta) 
{
  delta_ = delta ;
  index_ = 0 ;
  buffer_ = null ;
  size_ = 0;
  resize(size); // size_ will be set here
}


/*************************************************************************
 * Function Name: Vector::~Vector
 * Parameters: 
 * Effects: deletes the buffer by resizing to 0
 *************************************************************************/

Vector::~Vector() 
{
    free(buffer_);
    buffer_ = null ;
}


/*************************************************************************
 * Function Name: Vector::operator [] 
 * Parameters: 
 * Returns: char&
 * Effects: just return the char, as if the vector were an array (by ref)
 *************************************************************************/
char&
Vector::operator [] (int i) 
{
  return buffer_[i];
}


/*************************************************************************
 * Function Name: Vector::append
 * Parameters: const char *data
 * Returns: void
 * Effects: appends len bytes of data to the internal buffer, resizing if
 *          necessary.
 *          NOTE: Behaviour when data is part of the buffer is undefined.
 *************************************************************************/
void
Vector::append(const char *data, int len)
{
  resize(len+size());
  //  memcpy(buffer_+index_, data, len);
  for(int i=0; i<len; i++) {
    buffer_[size()+i] = data[i];
  }
  index_ += len ;
}


/*************************************************************************
 * Function Name: Vector::appendAndSet
 * Parameters: const char *data, int dataLen, int setLen
 * Returns: void
 * Effects: for setLen bytes, copies from data (which is of length dataLen)
 *          so appendAndSet(new int(4), 4, 20) copies the int '0x00000004'
 *          five times.  If setLen is not a multiple of dataLen, truncates
 *          (copies just the bytes of data that fit).  In other words,
 *          appendAndSet(new int(4), 4, 21) copies '0x00000004' five times,
 *          then '0x00' into the remaining byte.
 *          NOTE: Behaviour when data is part of the buffer is undefined.
 *************************************************************************/
void
Vector::appendAndSet(const char *data, int dataLen, int setLen)
{
  resize(setLen+size());
  
  int i;
  for(i=0; i<setLen-dataLen; i+=dataLen) {
    memcpy(buffer_+index_+i, data, dataLen);
  }

  memcpy(buffer_+i, data, setLen%dataLen);
  index_ += setLen ;
}


/*************************************************************************
 * Function Name: Vector::appendAndSet
 * Parameters: const char *data, int dataLen, int setLen, double iter
 * Returns: void
 * Effects: if repeat is set, like appendAndSet above, but increment the
 *          get pointer by iter (i.e. lose some of the data).  Fill with
 *          fill (which has length fillLen) if repeat is off.
 *************************************************************************/
void
Vector::appendAndSet(const char *data, int dataLen, int setLen, double iter, boolean repeat, const char *fill, int fillLen)
{
  resize(setLen+size());

  // fill with data; if repeat is on, when the get pointer overflows,
  // loop back; else fill with silence
  int i; double d;
  for(i=0, d=0.0; i < setLen; d+=iter, i++) {
    if(d>(double)dataLen) { if(repeat) { d=0.0; } else break; }
    buffer_[index_+i] = data[(int)d];
  }

  // fill the remaining with the specified fill
  if(i<setLen) {
    int temp = index_ ; index_ += i ;
    appendAndSet(fill, fillLen, setLen-i-1);
    index_ = temp ;
  }

  index_ +=setLen;
    
}


/*************************************************************************
 * Function Name: Vector::resize
 * Parameters: int newSize
 * Returns: void
 * Effects: resizes the array to newSize, rounded to nearest delta
 *************************************************************************/
void
Vector::resize(int newSize)
{
  resizeTo(newSize + (delta_ - newSize%delta_));
}



/*************************************************************************
 * Function Name: Vector::toFile
 * Parameters: const char *filename
 * Returns: boolean: true if the write succeeded
 * Effects: dumps the contents of the vector to the specified file
 *************************************************************************/
boolean
Vector::toFile(const char *filename)
{
  FILE *ofile = fopen(filename, "wb"); // write a binary file
  if(!ofile) return false ;
  errno = 0;

  for(int i=0; i<size(); i++) {
    putc((*this)[i], ofile);
  }
  fclose(ofile);

  if(errno) {
    // scrap what we've done to avoid leaving crap around the file system
    unlink(filename) ;
    return false ;
  }

  // everything has succeeded up to now; we're good
  return true ;
}


/*************************************************************************
 * Function Name: Vector::setIndex
 * Parameters: int index
 * Returns: void
 * Effects: sets the current maximum index without resizing downwards
 *          (useful speed-wise if you want to reuse the vector; wasteful
 *          memory-wise).  Does resize upwards, however.
 *************************************************************************/
void
Vector::setIndex(int index)
{
  if(index>index_) resizeTo(index);
  index_ = index ;
}


/*************************************************************************
 * Function Name: Vector::resizeTo
 * Parameters: int newSize
 * Returns: void
 * Effects: resizes the array exactly, using realloc
 *************************************************************************/
void
Vector::resizeTo(int newSize)
{
  index_ = newSize < index_ ? newSize-1 : index_ ;

  char *newPtr = (char*)malloc(newSize);
  if(!newPtr) throw OutOfMemoryException(this) ;

  // if realloc moved the block, copy it over; use memmove so that overlap
  // of arrays will work
  if((newPtr!=buffer_) && (buffer_!=null)) {
    memmove(newPtr, buffer_, index_);
    free(buffer_);
  }
  buffer_ = newPtr ;
  size_ = newSize ;
}


