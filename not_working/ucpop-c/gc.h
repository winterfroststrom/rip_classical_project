#ifndef GC_H
#define GC_H
// gc.h
// implements gc with ref counting
// to be inherited from,  for non-container classes
// $Log$
//
//

#include "utility.h"

class GC {
private:
  short refCount; // can try int to see if the casting is causing prob

public:
  GC() : refCount(0) {}
  void Reference() {refCount++;}
  void Dereference() {refCount--;}
  bool Deletable() const {return refCount<=0;}
};

#endif
