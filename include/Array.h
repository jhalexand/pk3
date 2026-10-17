#ifndef Array_H
#define Array_H

#include <debug.h>

/**************************************************************
 *	Name: Benoit Hudson (bh)
 *	File: Array.h
 *	Date: Thu Jul 16 15:26:51 EDT 1998
 *      Desc: A templated resizable array 
 **************************************************************/


#include <stdlib.h> // malloc, realloc

template <class T> class Array {
private:
    T *array_;
    int allocated_;
    int used_;

public:

    Array() {
        allocated_ = 2;
        array_ = (T*)malloc(allocated_*sizeof(T));
        used_ = 0;
    }
 
    Array(int i) {
        allocated_ = i;
        array_ = (T*)malloc(allocated_*sizeof(T));
        used_ = 0;
    }

    // make a deep copy
    Array(const Array<T>& copyFrom) {
        allocated_ = copyFrom.size();
        used_ = copyFrom.size();
        array_ = (T*)malloc(allocated_*sizeof(T));
        memcpy(array_, copyFrom.array_, used_*sizeof(T));
    }

    // make a deep copy
    Array<T>& operator = (const Array<T>& other) {
        allocated_ = used_ = other.used_;
        array_ = (T*)realloc(array_,allocated_*sizeof(T));
        memcpy(array_, other.array_, used_*sizeof(T));
        return *this;
    }

    ~Array() {
        free(array_);
#ifdef DEBUG
        array_ = null;
        allocated_ = 0;
        used_ = 0;
#endif
    }

    void clear() { used_ = 0; }
    
    void shrink() {
        allocated_ = used_;
        array_ = (T*)realloc(array_,allocated_*sizeof(T));
    }

    // return how many elements we have in the array
    int size() const { return used_; }

    // return the element at index i, rvalue only (read-only)
    const T& operator [] (int i) const { 
#ifdef DEBUG
        if(i>=used_ || i<0)
            err_print("Array", ("Index %d out of [0..%d)", i, used_));
#endif
        return array_[i]; 
    }
    const T& get (int i) const { return operator[] (i); }

 
    // return the element at index i; can be used as an lvalue (read-write)
    T& operator [] (int i) { 
#ifdef DEBUG
        if(i>=used_ || i<0)
            err_print("Array", ("Index %d out of [0..%d)", i, used_));
#endif
        return array_[i]; 
    }
    T& get (int i) { return operator[] (i); }

    const T& last() const { return operator[](size()-1); }
    T& last() { return operator[](size()-1); }
    



    // extend the vector, allocating more space if necessary
    void append(const T& element) {
        if(used_>=allocated_) {
            allocated_ *= 2;
            array_ = (T*)realloc(array_, allocated_*sizeof(T));
        }
        array_[used_] = element;
        used_++;
    }

    // remove the specified element.
    void remove(int index) {
        for(int i=index; i<used_-1; i++) {
            array_[i] = array_[i+1];
        }
        used_--;
    }

    void removeLast() { remove(size()-1); }

    // copy the range [start..end) from this array into 
    // dest starting at destStart.  Make sure dest is big enough.
    void copy(int start, int end, Array<T>& dest, int destStart) const {
        int size = end-start;
        dest.growTo(destStart+size);
        
        for(int i=0; i<size; i++) {
            dest[destStart+i] = array_[start+i];
        }
    }
    
    void growTo(int size) {
        if(size<=used_) return;
        used_ = size;
        if(used_ > allocated_) {
            allocated_ = used_;
            array_ = (T*)realloc(array_,allocated_*sizeof(T));
        }
    }

    void setSize(int size) {
        if(size>used_) growTo(size);
        else used_ = size;
    }

    // sort using the standard qsort
/*    void qsort(int (*compar)(const T*,const T*)) {
         ::qsort(array_, size(), sizeof(T*), 
                 (int (*)(const void*,const void*))compar);
    }*/
} ;

#endif
