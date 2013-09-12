#ifndef OBJECT_H
#define OBJECT_H
#include <stdarg.h>
#include "utility.h"
//#include "array.h"
//#include "list.h"
#include "str.h"
#include "gc.h"
// eqaulity constraints
#define EQ 1
#define NEQ -1

//template <class Type> class Array;
template <class T> class SList;

class Parser;
extern Parser parser;

class Term;
class SymArray;

//
// Defines plan components and objects for ucpop.
// $Log: objects.h,v $
// Revision 1.1  1993/07/10  01:01:14  ctkwok
// Initial revision
//
// Revision 1.1  1993/07/04  05:06:19  ctkwok
// Initial revision
//
// Written by ctkwok@wolf.cs.wasihongton.edu
//

//
// Sym id +ve variable; -ve constant; 0 unbound
// Sym is just an integer.
// Variable and Constants are Syms
// Notation:  Var will be shorthand for variable and Const for constant
// Sym for Syms
//
//
// predicate id +ve normal predicate; 0 unbound (SPECIAL); -ve negation 
// Pred for predicate
//



// class Sym {
// public:
//   Sym() : value(0) {}
//   Sym(const Sym& s) : value(s.value) {}
//   Sym(int x) : value(x) {}
//   operator int() const {return value;}
// //  operator int&() {return value;}
//   Sym& operator=(int x) {value=x; return *this;}
//   bool operator==(int x) {return value==x;}
//   bool operator==(Sym s) {return value==s.value;}
//   Sym operator+(Context x) {return value + x;}
// private:
//   int value;
// };
       
  
typedef int Sym;
typedef int StepId; // g++ has problem with defining this to be short
typedef short Size;
typedef int Context;
typedef int Pred;

#define IsVar(s) ((s)>0)
#define IsConst(s) ((s)<0)
#define SymisUnbound(s) ((s)==0)
#define isNegation(p) ((p)<0)
#define PredisUnbound(p) ((p)==0)
#define abs(i)((i>0)?i:-i)
#define PredOrNeg(p) (abs(p))



//class Buffer;
class Openc;

enum LogicPrimitive { Ordinary, And, Or, Not, Conditional, Universal, Existential };

class CS;
typedef SymArray Buffer;
class Step;

class ReplTable;
class TermRep {
  friend void PrintTerm(Term* t);// defined for parser debugging
  friend ostream& operator << (ostream& os, const TermRep& t);
  friend ostream& operator<< (ostream& os, Step& s);
  friend class CS; // cannot override this friendship (see CS::Unify)
  friend class Term;
  friend class Step;
  friend class ReplTable;
public:
  TermRep();
  ~TermRep();

  TermRep(const TermRep &t, Context context=0);
  TermRep(const TermRep& t, const ReplTable& table, Context context=0);
  TermRep(const Buffer&, Pred pred);

//  TermRep& operator=(const TermRep& t);
  
  Pred              GetPredicate()                 const;
  Sym               GetVariable()                  const;

  
  LogicPrimitive    GetType()                      const;
  bool              IsNegation()                   const;
  bool              IsOrdinary()                   const;

  bool              IsNegationOf(const TermRep& t) const;
  void              Negate();

  bool              operator==(const TermRep& t)   const;
  bool              operator!=(const TermRep& t)   const;

  const SList<Term>& GetList()                      const;
  // support for logical operations
  void              Subst(const ReplTable& table);

//  void*             operator new(size_t size);
//  void              operator delete(void* p, size_t size);
protected:
  TermRep(Size sz, Pred pred, Sym *syms);
protected:
  void Deallocate(Sym* s, Size used);
  Sym* Allocate(Size needed);
  
  Ref count;
  Size size;
  Pred p;
  Sym *s;  

  static Sym** freeList;
  static const Size poolSize;
  static TermRep* free;
};



class Term {
  friend void PrintTerm(Term* t);// defined for parser debugging
  friend ostream& operator<< ( ostream &os, const Term &t );
  friend ostream& operator<< ( ostream &os, Step &s );
  friend class CS; // cannot override this friendship (see CS::Unify)
  friend class Step;
  friend class ReplTable;
public:
  Term() : rep(new TermRep()) {}
  ~Term() { if (--rep->count <= 0) delete rep; }

  Term(const Term &t) : rep(t.rep) { rep->count++; }
  Term(const Term &t, Context context) : rep(new TermRep(*t.rep, context)) {}
  Term(const Buffer& b, Pred pred) : rep(new TermRep(b, pred)) {}
  Term(const Term& t, const ReplTable& table, Context context=0);
  Term(Pred pd, Sym sym); // typed-var constructor
  Term& operator=(const Term& t);
  
  Pred GetPredicate() const {return rep->GetPredicate();}
  // for typed variable use only
  Sym  GetVariable() const {return rep->GetVariable();}
  
  LogicPrimitive GetType() const {return rep->GetType();}
  bool IsNegation() const {return rep->IsNegation();}
  bool IsOrdinary() const {return rep->IsOrdinary();}

  bool IsNegationOf(const Term& t) const {return rep->IsNegationOf(*t.rep);}

  void Negate() {TermRep* t=new TermRep(*rep); if (--rep->count <= 0) delete rep;
		 rep=t; rep->p=-rep->p;}

  bool operator==(const Term& t) const {return *rep == *t.rep;}
  bool operator!=(const Term& t) const {return *rep != *t.rep;}

  const SList<Term>& GetList() const {return rep->GetList();}
  void ShiftAndOr();
  void ShiftUnivExist();

  bool IsBinding() const {return (rep->p==1 || rep->p==-1);}

  void Subst(const ReplTable& table);// {rep->Subst(table);}
protected:
  Term(Size sz, Pred pred, Sym *syms) : rep(new TermRep(sz, pred, syms)) {}
  void* slot() const { return (void*)rep->s; } // for its decendents
private:
  TermRep* rep;
};

// class TestTerm : public Term {
// public:
//   TestTerm(int p, ...);
// };

// yes,  this is repeating.  May be template will be future consideration
// Replacement table class
class ReplTable {

  friend ostream& operator<<(ostream&, const ReplTable&);

public:

  ReplTable();
  ~ReplTable();
  ReplTable(const ReplTable& tab);

  
  bool    Add(Sym slot, Sym thing); // FALSE if the slot already got the symbol
  bool    AddOverride(Sym slot, Sym thing); // Add anyway

  void    ClearSlot(Sym slot);
  
  Sym     Fetch(Sym slot) const;
  void    ReInitialize();
  void    AddBind(const Term& t1, const Term& t2, Context base);
  void    AddBind(const TermRep& t1, const TermRep& t2, Context base);

private:

  void Grow(int sz); // grow and make space for sz
  static const int Chunk;
  
private:

  Sym*   table;
  int    size;
  int    trueSize;

};
#ifndef OUTLINE
#include "objects.icc"
#endif


#endif				 // _OBJECT_H_


