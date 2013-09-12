#include "openc.h"
#include "utility.h"
#include "objects.h"
#include "logic.h"

#ifdef OUTLINE
#define inline
#include "openc.icc"
#undef inline
#endif
//Openc::Openc(List<int>& l)
//: Term(l) {}


ostream&
operator<< (ostream &os, const Openc& oc)
{
  switch(oc.GetType()) {
  case Ordinary:
    os << (Term)oc;// cast upwards
    break;
  case And:
    os << " (AND " << oc.GetList() << ")"; break;
  case Or: 
    os << " (OR " << oc.GetList() << ")"; break;
  default:
    os << "ERROR"; break;
  }
  return os;
}



List<Openc>
InstantiateOpenc(const List<Node>& l, StepId owner, Context context)
{
  List<Openc> ret;

  ITERATE(node, l, next, Node);
  DOLIST (node, next) {    
    ret += ((node->GetType()==Ordinary)?
	    new Openc(*node, owner, context):
	    new Openc(InstantiateOpenc(node->GetList(), owner, context), 
			      node->GetType()));
  }
  return ret;
}


List<Openc>
InstantiateOpenc(const List<Node>& l,
		 StepId owner,
		 Context context,
		 const ReplTable& table)
{
  List<Openc> ret;

  ITERATE(node, l, next, Node);
  DOLIST (node, next) {
    ret += ((node->GetType()==Ordinary)?
	    new Openc(*node, owner, context, table):
	    new Openc(InstantiateOpenc(node->GetList(),
				       owner,
				       context,
				       table), 
		      node->GetType()));
  }
  return ret;
}


DECLAREPRINT(Openc)
     
