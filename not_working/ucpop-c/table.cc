/* hold things */
#include "table.h"
//#include "list.h"

#ifdef OUTLINE
#define inline
#include "table.icc"
#undef inline
#endif


template<class Type>
Array<Type>::Array(int sz) 
: set(new Type[sz]), size(sz), count(0) {}


template<class Type>
Array<Type>::Array(const Array<Type> &a)
: size(a.size), count(a.count), set(new Type[a.size])
{
  for(int i=0;i<size;i++) 
     set[i]=a.set[i];
}


template<class Type>
Array<Type>::Array(Type *array, int sz)
: count(0), size(sz), set(new Type[sz])
{
  for (int i=0;i<sz;i++) 
     set[i]=array[i];
}

// 
// ostream& 
// operator <<(ostream &os, Table<TypeK, TypeT>& t)
// {
//   for (int i=0;i<t.size;i++)
//      os << "[" << t.keys[i] << "," << t.things[i] << "]";
//   return os;
// }


// Term&
// Table::Subst(const Term &t)
// {
//   Term& tm=*new Term(t);
//   Subst(tm.s,tm.GetSize(),TRUE);	 // use the argument
//   return tm;
// }
