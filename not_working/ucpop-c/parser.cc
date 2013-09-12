#include "utility.h"
#include "openc.h"
#include "objects.h"
#include "parser.h"
#include "template.h"
#include "plan.h"
#include "list.h"
#include "planner.h"
#include "order.h"
#include "link.h"
#include "varset.h"
#include "unsafe.h"
#include "slist.h"
#include "step.h"


class DomainTemplate;
extern DomainTemplate templates;

void
Init()
{
#define MAKE_LIST_CLASS(T)   ListNode<T>* List<T>::NilListNode=new ListNode<T>(1);  ListNode<T>* ListNode<T>::free=NULL
#define MAKE_SLIST_CLASS(T) SListNode<T>* SList<T>::NilSListNode=new SListNode<T>(1,1);  SListNode<T>* SListNode<T>::free=NULL
  
  MAKE_LIST_CLASS(Problem);
  MAKE_LIST_CLASS(Node);
  MAKE_LIST_CLASS(TemplateEntry);
  MAKE_LIST_CLASS(Varset);
//  MAKE_LIST_CLASS(Term);
  MAKE_LIST_CLASS(Effect);
  MAKE_LIST_CLASS(Pair);
  MAKE_LIST_CLASS(Step);
  MAKE_LIST_CLASS(Link);
  MAKE_LIST_CLASS(Plan);
  MAKE_LIST_CLASS(Openc);
  MAKE_LIST_CLASS(Unsafe);
  MAKE_SLIST_CLASS(Sym);
  MAKE_SLIST_CLASS(Term);
  MAKE_SLIST_CLASS(SList<Sym>);

#undef MAKE_LIST_CLASS
#undef MAKE_SLIST_CLASS

}


Parser::Parser()
: symtab()
{
  // have to do this to get around g++'s problem
  Init();
}

void
Parser::CreateOperator(Node& stepName,
		       List<Node> precondChain, 
		       List<Node> effectChain,
		       Context scope,
		       Context params)
{
  ReformTree(precondChain);
  ReformTree(effectChain);

//  precondChain=RemoveOrTree(precondChain); // this is buggy & not necessary
  precondChain=RemoveAndTree(precondChain);
  effectChain=RemoveAndTree(effectChain);

  DBG(_TEMPL_, { cerr << endl;
		 cerr << "Forming template for::::";
		 PrintStepName(&stepName);
		 cerr << endl << "OPENC:" << endl;
		 PrintNodes(precondChain);
		 cerr << endl << "EFFECTS: " << endl;
		 PrintNodes(effectChain);
		 cerr << endl;
		 cerr << "Scope :::: " << scope << endl;
		 cerr << "Params ::: " << params << endl;
		 cerr << endl;
	       });

  List<Node>& nonConditionals=*new List<Node>;
  List<Node> newEffChain;
  ITERATE(node, effectChain, next, Node);
  
  DOLIST(node, next) {
    if (node->GetType()==Ordinary)
       nonConditionals += node;
    else newEffChain += node;
  }
  if (nonConditionals.Valid()) newEffChain += new Node(nonConditionals, And);

  // you may not need params and scope here
  rawTemplates+=new TemplateEntry(stepName, precondChain, 
			       newEffChain, params);
  NewScope(); // clean up the name space
}


String
Parser::TranslatePred(Pred p) const
{ return symtab.FetchPredicate(p);}


String
Parser::TranslateSymbol(Sym s) const
{
  ASSERT(IsConst(s) || s==0);
  return symtab.FetchSymName(s);
}


String
Parser::TranslateStepName(const Term& t) const
{
  if (t.GetPredicate()>0) 
     return symtab.FetchOperator(t.GetPredicate());
  else return String("(GoalStep)");
}



void
ReformNode(Node& nod)
{
  switch(nod.GetType()) {
  case Ordinary: 
    break;
  case And:
  case Or:
    ReformTree(nod.GetList()); break;
  case Not:
    nod=nod.GetTerm();
    NegateNode(nod);
    break;
  case Conditional:
    // reform the lists for the two componenets.
    // all things are done during node formation
    break;
  case Universal:
  case Existential:
    ReformTree(nod.GetList());
    break;
  default:
    cerr << "Unknown type\n"; break;
  }
}


void
NegateNode(Node& nod)
{
  switch (nod.GetType()) {
  case Ordinary:
    nod.Negate(); break;
  case And:
  case Or:
    nod.ShiftAndOr(); 
    NegateTree(nod.GetList());
    break;
  case Not:
    nod=nod.GetTerm();
    ReformNode(nod);
    break;
  case Universal:
  case Existential:
    nod.ShiftUnivExist();
    NegateTree(nod.GetList());
  default:
    cerr << "Unknown type!\n"; break;
  }
}


void
ReformTree(List<Node>& nl)
{
  ITERATE(nod, nl, next, Node);
  DOLIST (nod, next)
     ReformNode(*nod);
}


void
NegateTree(List<Node>& nl)
{
  ITERATE(nod, nl, next, Node);
  DOLIST (nod, next)
     NegateNode(*nod);
}


List<Node>
RemoveAndTree(List<Node>& nl)
{
  List<Node> newList;
  ITERATE(nod, nl, next, Node);
  DOLIST (nod, next) {
    switch (nod->GetType()) {
    case Ordinary:
    case Conditional:
      newList += nod; break;
    case And:
      newList += RemoveAndTree(nod->GetList());
      break;
    case Or:
      newList += new Node(RemoveAndInOr(nod->GetList()), Or);
      break;
    case Not:
      cerr << "Should not have not's here!!"; break;
    case Universal:
    case Existential:
      newList += nod; break;
    default:
      cerr << "Should not happen!"; break;
    }
  }
  return newList;
} 


// do things in the Or sublist
List<Node>
RemoveAndInOr(List<Node>& nl)
{
  List<Node> newList;
  ITERATE(nod, nl, next, Node);
  DOLIST (nod, next) {
    switch (nod->GetType()) {
    case Ordinary:
      newList+=nod; break;
    case And:
      // this And is essential
     newList+=new Node(RemoveAndTree(nod->GetList()), And);
      break;
    case Or:
      newList+=new Node(RemoveAndInOr(nod->GetList()), Or);
      break;
    case Not:
      cerr << "Should not have not's here!!"; break;
    case Universal:
    case Existential:
      newList += nod; break;
      break; // ignore
    default:
      cerr << "Should not happen!"; break;
    }
  }
  return newList; 
}


List<Node>
RemoveOrTree(List<Node>& nl)
{
  List<Node> newList;
  ITERATE(nod, nl, next, Node);
  DOLIST (nod, next) {
    switch (nod->GetType()) {
    case Ordinary:
    case Conditional:
      newList+=nod; break;
    case Or:
      newList+=RemoveOrTree(nod->GetList());
      break;
    case And:
      newList+=new Node(RemoveOrInAnd(nod->GetList()), And);
      break;
    case Not:
      cerr << "Should not have not's here!!"; break;
    case Universal:
    case Existential:
      newList += nod; break;
      break;
    default:
      cerr << "Should not happen!"; break;
    }
  }
  return newList;
} 

List<Node>
CopyTree(List<Node>& nl)
{
  List<Node> newList;
  ITERATE(nod, nl, next, Node);
  DOLIST(nod, next) {
    switch(nod->GetType()) {
    case Ordinary:
      newList += new Node(*nod);
      break;
    case And:
    case Or:
    case Not:
      newList += new Node(CopyTree(nod->GetList()), nod->GetType());
      break;
    case Conditional:
    case Universal:
    case Existential:
      newList += new Node(CopyTree(nod->GetList()),  nod->GetTypeList(), nod->GetType());
    default:
      cerr << "Not implemented" << endl;
      break;
    }
  }
  return newList;
}

// do things in the Or sublist
List<Node>
RemoveOrInAnd(List<Node>& nl)
{
  List<Node> newList;
  ITERATE(nod, nl, next, Node);
  DOLIST (nod, next) {
    switch (nod->GetType()) {
    case Ordinary:
      newList+=nod; break;
    case Or:
      // this Or is essential
      newList+=new Node(RemoveOrTree(nod->GetList()), Or);
      break;
    case And:
      newList+=new Node(RemoveOrInAnd(nod->GetList()), And);
      break;
    case Not:
      cerr << "Should not have not's here!!"; break;
    case Universal:
    case Existential:
      newList += nod; break;
      break;
    default:
      cerr << "Should not happen!"; break;
    }
  }
  return newList; 
}


int
Parser::ParseFile()
{
  return yyparse();
}


Context
Parser::NewScope()
{return symtab.NewScope();}



void 
Parser::PrintTerm(Node* nod)
{
  cerr << *nod;
}

void 
Parser::PrintStepName(Node* nod)
{
  if (nod->GetType()==Ordinary){
    cerr << "(";
    cerr << symtab.FetchOperator(nod->GetPredicate()) << " ";
//    for(int i=0;i<nod->size;i++)
//       cerr << symtab.FetchSymName(nod->s[i]) << " ";
    cerr << ")";
  } else {
    List<Node> l;
    l+= *nod;
    PrintNodes(l);
  }
}


void
Parser::PrintNodes(const List<Node>& nl)
{
  ITERATE(nod, nl, next, Node);
  DOLIST (nod, next) {
    switch(nod->GetType()) {
    case Ordinary:
      PrintTerm(nod); break;
    case And:
      cerr << "{:AND "; 
      PrintNodes(nod->GetList());
      cerr << "}";
      break;
    case Or:
      cerr << "{:OR "; 
      PrintNodes(nod->GetList());
      cerr << "}";
      break;
    case Not:
      cerr << "{:NOT ";
      PrintTerm(&(nod->GetTerm()));
      cerr << "}";
      break;
    case Conditional:
      cerr << "{:WHEN ";
      cerr << "{:OPENC";
      PrintNodes(nod->GetConditions());
      cerr << "}";
      cerr << "{:EFF ";
      PrintNodes(nod->GetList());
      cerr << "}";
      cerr << "}";
      break;
    case Universal:
      cerr << "{:FORALL";
//      PrintNodes(nod->GetTypeList());
      PrintNodes(nod->GetList());
      cerr << "}";
      break;
    case Existential:
      cerr << "{:EXISTS";
      PrintNodes(nod->GetTypeList());
      PrintNodes(nod->GetList());
      cerr << "}";
      break;
    default:
      cerr << "Unknown type\n"; break;
    }
  }
}
