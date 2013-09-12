#ifndef LOGIC_H
#define LOGIC_H

#include "objects.h"
#include "slist.h"
#include "gc.h"
#include "list.h"

#define VA_BUFSIZE 20 // vararg buffers

// a node:
// 1.  If it is a term,  it is a term;
// 2.  If it is And or Or,  it holds a list in 's' field
// 3.  If it is a Not,  it holds a node.

typedef SList<SList<Sym> > ReplList;

class Node : public Term, public GC {

  friend class Parser;
  friend ostream& operator<< (ostream& os, const Node& n);

public:

  Node(const Buffer& b, Pred pred);             // Term
  Node(List<Node>,      LogicPrimitive prim);   // Conj and Disj clauses
  Node(Node* precond,   List<Node>* effs);      // conditional clauses
  Node(const Node&,     LogicPrimitive prim);   // Neg clauese
  Node(Pred pd,         Sym sym);               // typed-var constructor
  Node(const Node& n);                          // copy constructor
  Node(SList<Sym> forallVar,                    // universal clauses
       List<Node> effs,
       Context& scope,
       Context numParams);
  Node(List<Node> conds, List<Node> types, LogicPrimitive type);

  // accessors
  List<Node>          GetList()          const;
  List<Node>          GetConditions()    const;
  List<Node>          GetNegConditions() const;
  Node&               GetTerm();
  Context             GetBase()          const;
  List<Node>          GetTypeList()      const;

  // reform universal clauses
  void                Subst(const ReplTable& table, Context params);
  List<Node>          Instantiate(List<Node> nl, const ReplTable& table);
  Node&               Instantiate(List<Node> initialConditions);
  void                Instantiate(ReplTable table,
				  ReplList variables,
				  List<Node>& ret);
private:

  List<Node>   conditionalList;     // effects hold condition, openc hold type
  List<Node>   negConditionalList;
  Context      base;
};

void Subst(List<Node>& l, const ReplTable& table, Context params);

#ifndef OUTLINE
#include "logic.icc"
#endif

#endif
