#include "bitstring.h"
#include "utility.h"

#ifdef OUTLINE
#define inline
#include "bitstring.icc"
#undef inline
#endif


ostream& 
operator<< (ostream& os, const BitString& b)
{
  os << "<";
  for(int i=0; i<b.size; i++ )
     if (b==i) os << i << " ";
  return os << ">";
}

const int BitString::poolSize=10000; // allocate 2000 strings each time
BitStr* BitString::freeList=new BitStr[10];


