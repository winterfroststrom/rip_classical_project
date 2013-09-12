#include "openc.h"
#include "effect.h"
#include "step.h"
#include "template.h"
#include "parser.h"
#include "varset.h"

#ifdef OUTLINE
#define inline
#include "step.icc"
#undef inline
#endif

List<Effect> InstantiateEffect(const List<Node>& l, StepId owner, Context context);
List<Openc> InstantiateOpenc(const List<Node>& l, StepId owner, Context context);



ostream& 
operator<< (ostream& os, Step& s)
{
  os << "[Step: " << parser.TranslateStepName(s.term);

  for (int i=0; i<s.term.rep->size; i++) {
    if (IsConst(s.term.rep->s[i])) os << parser.TranslateSymbol(s.term.rep->s[i]) << " ";
    else os << s.term.rep->s[i] << " ";
  }
  os << " id=> " << s.id << "]";
//  os << s.opencs <<  endl;
//  os << s.effects << endl;
  return os;
}

void
Step::PrettyPrint(ostream& os, const CS& cs)
{
  os << "(" << parser.TranslateStepName(term);

  for (int i=0; i<term.rep->size; i++) {
    os << parser.TranslateSymbol(cs.GetConstant(term.rep->s[i])) << " ";
  }
  os << ")";
    os << "           Created " << id << endl;
}




DECLAREPRINT(Step)
     
