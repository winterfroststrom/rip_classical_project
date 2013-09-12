#include "varset.h"
#include "parser.h"
#include "utility.h"

#ifdef OUTLINE
#define inline
#include "varset.icc"
#undef inline
#endif


// dummy varset
Varset* CS::NilVarset=new Varset(1);

// this definitely inline
Varset*
CS::Unify(Sym s1, Sym s2)
{
  if (s1 != s2) {
    if (!(IsConst(s1) && IsConst(s2))) {
      Varset* v1=GetVarset(s1); 
      Varset* v2=GetVarset(s2);
      if (v1!=v2 || !v1) {    // if v1==v2, then see if v1 is actually null
	return (IsConst(s2)) ?
	   CreateEqVarset(v2, s2, v1, s1) : CreateEqVarset(v1, s1, v2, s2);
      }
    } else return NULL;  // s1 != s2 and both are constants
  }  
  return NilVarset; // catch all:  unify without additional bindings
}

List<Varset>*
CS::Unify(const TermRep &t1, const TermRep &t2)
{
  if (t1.size!=t2.size || t1.p!=t2.p) return NULL;

  DBG(_VAR_, cerr << "==== Unifying ===> " << t1 << " and " << t2 << endl);
  List<Varset>* vslist=new List<Varset>;
  Varset *v;
  
  for (int i=0; i<t1.size; i++) {
    if (v=Unify(t1.s[i], t2.s[i])) {
      if (v!=NilVarset) vslist->Push(v);
    } else {
      delete vslist;
      return NULL;
    }
  }
  DBG(_VAR_, cerr << "Unification success ;; " << endl);
  return vslist;			 // return pointer to l as List*
}

// Algorithm:
// Assume the first one is the effect with universal variables.
// The "base" of the domain is represeted by the fourth parameter.
// If the variable is greater than the base,  then the variable is universal.
// This needs no unification,  enter the variable into the table
// (3rd parameter) and then move along.
// table is initialized when passed here

List<Varset>*
CS::Unify(const TermRep &t1,
	  const TermRep &t2,
	  ReplTable& table,
	  Context param)
{
  if (t1.size!=t2.size || t1.p!=t2.p) return NULL;

  DBG(_VAR_, cerr << "==== Unifying ===> " << t1 << " and " << t2 << endl);
  List<Varset>* vslist=new List<Varset>;
  Varset *v;
  
  table.ReInitialize();
  for (int i=0; i<t1.size; i++) {
    if (t1.s[i] > param) {
      table.Add(t1.s[i], t2.s[i]);
    } else {
      if (v=Unify(t1.s[i], t2.s[i])) {
	if (v!=NilVarset) vslist->Push(v);
      } else {
	delete vslist;
	return NULL;
      }
    }
  }
  DBG(_VAR_, cerr << "Univ Unification success ;; " << endl);
  return vslist;			 // return pointer to l as List*
}

ostream& 
operator<<(ostream& os, const Varset& vs)
{
  os << "<VARSET::";
  if (vs.constant!=0) 
     os << " Constant=" << parser.TranslateSymbol(vs.constant);
  
  os << " CD=" << vs.cd << " NCD=" <<\
     vs.ncd << ">";
  return os;
}

ostream&
operator<< (ostream& os, const CS& cs)
{
  os << "Constraint Set::\n";
  ListIterator<Varset> vptr(cs);
  Varset *v;
  while (v=vptr()) os << *v;
  return os;
}

// ostream&
// operator<< (ostream& os, const List<Varset>& cs)
// {
//   os << "Constraint Set::\n";
//   ListIterator<Varset> vptr(cs);
//   Varset *v;
//   while (v=vptr()) os << *v;
//   return os;
// }
// 
DECLAREPRINT(Varset)
     
