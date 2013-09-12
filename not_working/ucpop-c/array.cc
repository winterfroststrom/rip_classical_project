/* hold things */
#include "array.h"

#ifdef OUTLINE
#define inline
#include "array.icc"
#undef inline
#endif


SymArray::SymArray(int sz) 
: set(new Sym[sz]), size(sz), count(0) {}


SymArray::SymArray(const SymArray &a)
: size(a.size), count(a.count), set(new Sym[a.size])
{
  for(int i=0;i<size;i++) 
     set[i]=a.set[i];
}


SymArray::SymArray(const Sym *array, int sz)
: count(0), size(sz), set(new Sym[sz])
{
  for (int i=0;i<sz;i++) 
     set[i]=array[i];
}

SymArray::~SymArray()
{
  DBG(_DEL_, cerr << "Deleting Array...\n");
  delete [] set;
}


