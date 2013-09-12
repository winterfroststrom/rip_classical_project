#include "logic.h"
#include "parser.h"
#include "slist.h"

#ifdef OUTLINE
#define inline
#include "logic.icc"
#undef inline
#endif


Node::Node(List<Node> lt, LogicPrimitive prim)
: Term((int)prim, 0, (Sym*)new List<Node>(lt)),
  conditionalList(),
  negConditionalList(),
  base(0)
{}


Node::Node(Node* precond, List<Node>* effs)
: Term((int)Conditional, 0, (Sym*)effs),
  conditionalList(),
  negConditionalList(),
  base(0)
{

  conditionalList += precond;
  ReformTree(conditionalList);
  ReformTree(GetList());
  negConditionalList=CopyTree(conditionalList);

  NegateTree(negConditionalList);

  conditionalList=RemoveAndTree(conditionalList);
//  conditionalList=RemoveOrTree(conditionalList);

  negConditionalList=RemoveAndTree(negConditionalList);
//  negConditionalList=RemoveOrTree(negConditionalList);
//  parser.PrintNodes( conditionalList );  
//  parser.PrintNodes( negConditionalList );  
}


Node::Node(const Node& nod, LogicPrimitive prim)
: Term((int)prim, 0, (Sym*)&nod),
  conditionalList(),
  negConditionalList(),
  base(nod.base)
{}

// copy ordinary Nodes
Node::Node(const Node& nod)
: Term(nod),
  conditionalList(),
  negConditionalList(),
  base(nod.base)
{}


// the following things fixes the scope of universal quantification
Node::Node(SList<Sym> forallVar,
	   List<Node> effs,
	   Context& scope,
	   Context params)
: Term((int)And, 0, (Sym*)new List<Node>(effs)),
  conditionalList(),
  negConditionalList(),
  base(0)
{
  ReplTable table;

  // make the "bindings"
  while (forallVar.Valid()) {
//    cerr << forallVar.First() << ",";
     if (table.Add(forallVar.Pop(), scope+1)) scope++;
  }
//  cerr << table <<endl;
//  parser.PrintNodes(effs);
  ::Subst(effs, table, params);
//  parser.PrintNodes(effs);
}  


// trial
// the following things fixes the scope of universal quantification
Node::Node(List<Node> conds,
	   List<Node> types,
	   LogicPrimitive type)
: Term((int)type, 0, (Sym*)new List<Node>(conds)),
  // hacked s.t. this node won't be taken apart
  conditionalList(types),
  negConditionalList(),
  base(0)
{
  // there MAY be problems with contexts;  since this table uses up
  // entries which are not really needed,  but this could wait?
  // All I really care here is the values in forallVar list,  and
  // later hey would be replaced once planning begun.
//  parser.PrintNodes(conds);
}  

void
Subst(List<Node>& l, const ReplTable& table, Context params)
{
  ITERATE(node, l, next, Node);
  DOLIST (node, next) node->Subst(table, params);
}


void
Node::Subst(const ReplTable& table, Context params)
{
  switch(GetType()) {
  case Ordinary:
//    cerr << "BEFORE========= " << (Term)*this << endl;
    Term::Subst(table); 
//    cerr << "AFTER========== " << (Term)*this << endl;
    break;
  case Conditional:
    // this must be universal & conditional
    ::Subst(conditionalList, table, params); 
    ::Subst(negConditionalList, table, params); 
    ::Subst(GetList(), table, params);
    break;
  case And:
  case Or:
    ::Subst(GetList(), table, params); break;
  case Not:
    GetTerm().Subst(table, params); break;
  case Universal:
  case Existential:
    // hmmm?  What should I do with these? They are opencs.
//    ::Subst(GetList(), table, params);
//    ::Subst(GetTypeList(), table, params);
    break;
  default:
    cerr << "unknow type" << endl; break;
  }    
  base=params;
}


Node::Node(const Buffer& b, Pred pred)
: Term(b, pred),
  conditionalList(),
  negConditionalList(),
  base(0)
{}


Node::Node(Pred pred, Sym sym)
: Term(pred, sym),
  conditionalList(),
  negConditionalList(),
  base(0)
{}


ostream&
operator<< (ostream& os, const Node& n)
{
  os << (Term)n;
  return os;
}


// node is an universal node.
List<Node>
Instantiate(List<Node> nl, const ReplTable& table)
{
  Node* tmp;
  List<Node> ret;
  ITERATE(n, nl, next, Node);
  DOLIST(n, next) {
    switch(n->GetType()) {
    case Ordinary:
      tmp=new Node(*n);
      tmp->Term::Subst(table);
      ret += tmp;
      break;
    case And:
    case Or:
      ret += new Node(Instantiate(n->GetList(), table), n->GetType());
      break;
    case Not:
      cerr << "Instantiate2 :: Should not have *not*"  << endl;
      exit(1);
      break;
    case Universal:
    case Existential:
      cerr << "Instantiate2 :: Not yet implemented" << endl;
      exit(1);
      break;
    default:
      cerr << "Unknwon type" << endl;
    }
  }
  return ret;
}
  
// simulate a closure
//List<Node>
void
Node::Instantiate(ReplTable table,   // pass this by VALUE
		  ReplList variables,
		  List<Node>& ret)
{
  SList<Sym> varlist = variables.First();

  if (variables.Empty()) {
    ret+=::Instantiate(GetList(), table);
    return;
  }

  // pops the "key": universal/existential variable to be binded
  // which is assumed to be at start of the list
     
  Sym key=varlist.Pop(); 
  SITERATE (constant, varlist, next, Sym);
  Sym pconstant=table.Fetch(key);
  if (pconstant) { // endowned by parent
    SDOLIST (constant, next) {
      if (constant == pconstant) 
	 Instantiate(table, variables.Tail(), ret);
    }
  } else { // was not filled in before
    SDOLIST (constant, next) {
      table.Add(key, constant);
      Instantiate(table, variables.Tail(), ret);
      table.ClearSlot(key);       // allow next variable to be added on
    }
  }
}


SList<Sym>
RemoveDup(SList<Sym> s)
{
  SList<Sym> ret;
  SITERATE(var, s, next, Sym);
  SDOLIST(var, next) {
    if (ret != var) ret += var;
  }
  return ret;
}


List<Node>
InstantiateQuantified(List<Node> tmpl, List<Node> initialConditions)
{
  List<Node> ret;
  ITERATE(node, tmpl, next, Node);
  DOLIST(node, next) {
    switch(node->GetType()) {
    case Ordinary:
      ret += node;
      break;
    case And:
    case Or:
      ret += new Node( InstantiateQuantified(node->GetList(),
					     initialConditions),
		       node->GetType());
      break;
    case Not:
      cerr << "Instantiate: should not have *not* here" << endl;
      break;
    case Universal:
      ret += node->Instantiate(initialConditions);
      break;
    case Existential:
      cerr << "Instantiate: existential not yet supported" << endl;
    default:
      cerr << "Instantiate: unknown type" << endl;
      break;
    }
  }
  return ret;  
}


// in a forall node
Node&
Node::Instantiate(List<Node> initialConditions)
{
  ReplTable dummy;
  ReplList variables;
  SList<Sym> segment;
  List<Node> ret;
  // fill in the variables
  ITERATE(node, GetTypeList(), next, Node);
  // the initial Condition is (:and (real-list))
  ITERATE(init, initialConditions.First()->GetList(), initnext, Node);
  
  DOLIST(node, next) {
    segment.FreeUp();
    initnext.Reset();  // reset the iterator for initial conditions
    
    DOLIST(init, initnext) {
      if (node->GetPredicate()==init->GetPredicate() ||
	  node->GetPredicate()==0)
	 {
	   segment += init->GetVariable();  // get the constant associated
	 }
    }
    // the first value of the list becomes the "key"
    segment.Push(node->GetVariable());
    variables += segment;
//    cerr << "SEGMENT------------------> " << segment << endl;
  }
  
//  cerr << "VARIABLE SUBST=====> " << variables << endl;
  next.Reset();
  DOLIST(node, next) {
    Instantiate(dummy, variables, ret);
  }
  return *new Node(ret, And);
}

// Node::Node(Pred pd, ...)
// : Term(0, pd, NULL), conditionalList()
// {
//   int tmp;
//   va_list al;
//   va_start(al,pd);    
//   Sym bufferSym[VA_BUFSIZE];
// 
//   for(int i=0,j=0;; i++) {
//     j=va_arg(al,int);
//     if (!j) break;
//     bufferSym[i]=j;
//     size++;
//   }
//   Sym* stmp=(size)?new Sym[size]:NULL;
// 
//   for(i=0; i<size;i++)
//      stmp[i]=bufferSym[i];
//   va_end(al);
// 
//   slot()=stmp;
// }

DECLAREPRINT(Node)
     
