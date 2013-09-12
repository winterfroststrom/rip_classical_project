#ifndef SYMTAB_H
#define SYMTAB_H

// $Log: symtab.h,v $
// Revision 1.1  1993/08/03  08:38:33  ctkwok
// Initial revision
//
// Revision 1.1  1993/07/04  05:06:19  ctkwok
// Initial revision
//
// symbol table management


#include "str.h"
#include "objects.h"
#include "array.h"
//template <class Type> class Array;

class StrTable {
public:
  StrTable();
  ~StrTable();
  Sym operator+=(char* s);
  Sym Lookup(char* s);
  Sym Add(char* s);  // add w/o checking
  Sym Find(char* s);
  Context Reset();
  char* Fetch(Sym s) const;
private:
  void grow();  // grow array,  size doesn't change,  trueSize * 2
private:
  static const int InitSize;
  char** array;
  int trueSize;
  int size;    // how many things the table contains
};

// for now the fixed size implementation is used

class SymTab {
public:
  SymTab();
  Sym AddOp(char*);
  Sym AddVar(char*);    // return the symbol representing the string
  Sym FindVar(char*);
  Sym LookupVar(char*);
  Sym FindConst(char*);
  Sym FindPred(char*);

  // enter a new operator def, flush the localTable,  return number of
  // variables in local table.
  int NewScope();
  String FetchSymName(Sym symbol) const;// fetch both const and variable
  String FetchPredicate(Pred pred) const;
  String FetchOperator(Sym opname) const;
private:
  StrTable opTable;
  StrTable predTable;
  StrTable constTable;
  StrTable localTable;
};
  

// this class is for some initialization stuff
class UCPOPSymTab : public SymTab {
public:
  UCPOPSymTab();
  Sym FindPred(char*); // override to prepare for :eq and :neq
};


#ifndef OUTLINE
#include "symtab.icc"
#endif

#endif
