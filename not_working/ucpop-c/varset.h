#ifndef VARSET_H
#define VARSET_H

#include "utility.h"
#include "objects.h"
#include "bitstring.h"
#include "list.h"
#include "gc.h"
// 	$Id: varset.h,v 1.1 1993/07/06 22:54:25 ctkwok Exp ctkwok $	

typedef int BindConstraint;

// unification status: can never unify, may be able to unify, already unified.
// not using enum; since prefer explicit 0 for CannotU is preferred
typedef int Ustatus;
#define CannotU 0
#define MayU    1
#define IsU     -1
// 
// Varset.h
// implements the data structure for Sym sets.
//


class Varset : public GC {
     friend class CS;
     friend ostream& operator<< (ostream&, const Varset&);
public:
  Varset(const BitString &co, const BitString &vnc, Sym c=0);
  Varset(int size); // Sym is required to distinguish args
  Varset(const Varset &v);
  ~Varset();

  // create varset with symbols.  s1 will be in the cd set in 
  Varset(Sym s1, Sym s2, BindConstraint bc=EQ);

  Varset*        operator+(Sym symbol)    const;
  Varset*        operator+(Varset &v)     const;
  Varset         operator|(const Varset&) const;
  void           operator|=(const Varset& v);

  // these return Varset* because they can possibly be NULL
  bool           operator==(const Varset&) const;
  bool           operator!=(const Varset&) const;
  Varset*        RestrictVarset(Sym) const;
  Varset*        CombineVarsets(const Varset &v2) const;

private:
  BitString ncd;		 // cannot bind to these VARIABLES
  BitString cd; 		 // cd set
  Sym constant;			 // constant binding to this varset
}; 


// This is more complicated and so better be a derived class
// than a typedef (?)

class CS : public List<Varset> {
     friend ostream& operator<<(ostream& os, const CS& cs);
public:
  CS();
  CS(const List<Varset>& vs);
  bool             ConstrainNeq(Sym, Sym);
  bool             ConstrainEq(Sym, Sym);
  Ustatus          Codesignate(Sym,Sym) const;
  bool             AddBind(Sym s1,Sym s2, BindConstraint bc);
  bool             AddBind(const TermRep& t);
  bool             AddBind(const Term& t);  // a term (:eq a b) or (:neq a b)

  Varset*          Unify(Sym s1, Sym s2);
  List<Varset>*    Unify(const Term& t1, const Term& t2);
  List<Varset>*    Unify(const TermRep& t1, const TermRep& t2);
  List<Varset>*    Unify(const Term& t1,
			 const Term& t2,
			 ReplTable& table,
			 Context param);

  
  List<Varset>*    Unify(const TermRep &t1,
		         const TermRep &t2,
		         ReplTable& table,
		         Context param);

//  Ustatus          Affects(const TermRep&, const TermRep&) const; 
  Ustatus          Affects(const TermRep &t1,
			   const TermRep &t2,
			   Context base) const;
  Ustatus          Affects(const Term&, const Term&, Context base) const; 
  Sym              GetConstant(Sym) const;
private:
  static Varset* NilVarset;
  Varset* GetVarset(Sym) const; // private accessor
private:


  // create a varset with s1 and s2 codesignate and return it;
  // return NULL if none is possible
  Varset* CreateEqVarset(Varset* v1, Sym s1, Varset* v2, Sym s2) const;
};

#ifndef OUTLINE
#include "varset.icc"
#endif

#endif 				 // _VARSET_H_
