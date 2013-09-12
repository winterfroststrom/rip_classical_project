#ifndef TABLE_H
#define TABLE_H

#include "utility.h"
#include <iostream.h>
//#include "list.h"
#include "objects.h"

// table class:  general fixed size table
// fixed size set

class Table;
class Term;

// this class COPIES the Type elements onto the array, instead of
// pointing to them.  So in order for efficient execution,  it
// is the user\'s responsibility to reduce the Type size.

template <class Type>
class Array {
     friend ostream& operator<<(ostream&, const Array<Type>&);
     friend class Table<Type>;
public: 
  Array(int sz);
  Array(Type *array, int sz);

  Array(const Array<Type> &a);

  Array(const Array<Type> &a);

  int Lookup(Type& thing) const; // return index of the thing

  bool operator==(Type& thing) const;
  bool operator!=(Type& thing) const;

  Type& operator[](int index) const;

  // add an element if not in the set
  int operator+=(Type& thing);

  int Add(Type& thing);
  int Reset();

  Type* MakeArray() const;

  int GetCount() const;
protected:
  Type* set;
  int size;
  int count;
};

// 
// // is more efficient than using List
// template <class TypeK, class TypeT>
// class Table {
//      friend ostream& operator<< (ostream&, const Table<TypeK, TypeT>&);
// public:
//   Table(int sz) {keys=new TypeK[sz]; things=new TypeT[sz]; size=sz; count=0;}
//   
//   Table(const Table<TypeK, TypeT>&);
// 
//   // would not add duplicates!
//   void Add(TypeK& key, TypeT& item);
// 
//   // return TableEntry: thing; 0 means failure (very dangerous though)
//   int Lookup(TypeK& key) const;
// 
//   // member operator with Lookup
//   // useful only for seeing memebrship;  awkward for retrivial
// 
//   int operator==(TypeK key) const;
//   // See if key is in the table
// 
//   // CANNOT DO THIS DUE TO GARBAGE COLLECTION!
// //  int* Subst(int*, int sz, int destructive=FALSE);	 
// 				 // substitue symbols in the table and make
// 				 // the new term
// //  Term& Subst(const Term &);
//   // size is public
//   const int GetSize() const;
// private:
//   TypeK *keys;
//   TypeT *things;
//   int size;
//   int count;			 // eliminate in optimization
// };

#endif
