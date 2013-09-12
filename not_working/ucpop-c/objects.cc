#include "objects.h"
#include "openc.h"
#include "parser.h"
#include "array.h"
#include "logic.h"
//#include "list.h"


#ifdef OUTLINE
#define inline
#include "objects.icc"
#undef inline
#endif

const Size TermRep::poolSize=2000;
Sym** TermRep::freeList=new Sym*[10];
TermRep* TermRep::free=NULL;

// will change to look up a table and find the strings
ostream& 
operator<< ( ostream &os, const TermRep &t )
{
  os << "(" << parser.TranslatePred(t.p);
  for (int i=0; i<t.size;i++)
     if (IsVar(t.s[i]))
	os << " " << t.s[i];
     else os << " " << parser.TranslateSymbol(t.s[i]);
  
  os << ")";	  
  return os;
}

ostream&
operator<< (ostream& os, const Term& t)
{
  os << *t.rep;
  return os;
}

// for testing
// TestTerm::TestTerm( int pd, ... )  // integers at \'...\'
// : Term(0, 0, NULL)
// {
//   p=pd;
//   int tmp;
//   va_list al;
//   va_start(al,pd);    
//   Sym bufferSym[20];		 // should be enough
//   size=0;
// 
//   for(int i=0,j=0;; i++) {
//     j=va_arg(al,int);
//     if (!j) break;
//     bufferSym[i]=j;
//     size++;
//   }
// //  cerr << "got invoked";
//   s=(size)?new Sym[size]:NULL;
// 
//   for(i=0; i<size;i++)
//      s[i]=bufferSym[i];
//   va_end(al);
// }



const int ReplTable::Chunk=8;



ostream&
operator<<(ostream& os, const ReplTable& table)
{
  os << "[";
  for (int i=0;i<table.trueSize;i++) cerr << table.table[i] <<" ";
  os << "]";
  return os;
}

//DECLAREPRINT(Term)
     

ostream& 
operator<<(ostream& os, const SList<Term>& s)
{
  SITERATE(t, s, next, Term);
  os << "<";
  SDOLIST(t, next) {
    os << t << " ";
  }
  os << ">";
  return os;
}

