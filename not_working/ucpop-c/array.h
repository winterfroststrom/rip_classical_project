#ifndef ARRAY_H
#define ARRAY_H

#include "utility.h"
#include <iostream.h>
//#include "objects.h"
//#include "list.h"
// 
// #ifdef __GNUG__
// #include "g++array.h"
// #endif

//#ifndef __GNUG__
// this class COPIES the T elements onto the array, instead of
// pointing to them.  So in order for efficient execution,  it
// is the user\'s responsibility to reduce the T size.

#ifndef Sym
typedef int Sym;
#endif

class SymArray {

  friend ostream& operator<<(ostream&, const SymArray&);

public: 
  SymArray(int sz);
  SymArray(const Sym *SymArray, int sz);
  SymArray(const SymArray& a);
  ~SymArray();
  
  int GetCount() const;
  int Reset();
  
  Sym* MakeArray() const;
  
// returns index, -1 if not found
  
  int Lookup(Sym thing) const;
  bool operator==(Sym thing) const;
  bool operator!=(Sym thing) const;
  
  int Add(Sym thing);
  Sym operator[](int index) const;
  int operator+=(Sym thing);

  // add an element if not in the set
protected:
  Sym* set;
  int size;
  int count;
};

// templates must include its .cc file
#ifndef OUTLINE
#include "array.icc"
#endif

//#include "array.cc"

#endif // ARRAY_H

