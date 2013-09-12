#include "symtab.h"

#ifdef OUTLINE
#define inline
#include "symtab.icc"
#undef inline
#endif

const int StrTable::InitSize=32;

StrTable::StrTable()
: trueSize(InitSize), size(0), array(new char*[InitSize]) {}


StrTable::~StrTable()
{
  for (int i=0;i<size;i++) delete [] array[i];
  delete [] array;
}

// There is no strict reason why neq has to be -1,  but
// conceptually, since eq is 1,  neq better be -1, ne?

// correct neq to be -1 (since :neq is not in the symbol table...)
Sym
UCPOPSymTab::FindPred(char* s)
{return (strcmp("neq", s)!=0)?SymTab::FindPred(s):NEQ;}
  


UCPOPSymTab::UCPOPSymTab()
: SymTab()
{
  FindPred("eq"); // make ":eq" to be #1 predicate
}


// create an empty symbol table
SymTab::SymTab()
: opTable(), predTable(), 
  constTable(), localTable() {}

