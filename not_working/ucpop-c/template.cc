#include "template.h"

#ifdef OUTLINE
#define inline
#include "template.icc"
#undef inline
#endif 

// is ensured a copy that will not be deallocated
// :i.e. directly given objects

TemplateEntry::TemplateEntry(Term& stepName,
			     List<Node> precondChain, 
			     List<Node> effectChain,
			     Context currentContext)
: context(currentContext),
  stepname(stepName),
  preconds(precondChain),
  effects(effectChain)
{}


DomainTemplate::DomainTemplate()
: currentContext(0),
  symbolTable(NULL)
{}


DomainTemplate templates;
DomainTemplate rawTemplates;


DomainTemplate&
DomainTemplate::operator=(List<TemplateEntry> l)
{
  List<TemplateEntry>::operator=(l);
  return *this;
}


TemplateEntry&
TemplateEntry::Instantiate(List<Node> initialConditions)
{
  Context newContext=context; // for existentials
  return *new TemplateEntry(stepname,
			    InstantiateQuantified(preconds,
						  initialConditions),
			    effects,
			    newContext );
}


List<TemplateEntry>
DomainTemplate::Instantiate(List<Node> initialConditions)
{
  List<TemplateEntry> ret;
  ITERATE(entry, *this, next, TemplateEntry);

  DOLIST(entry, next) {
     ret += entry->Instantiate(initialConditions);
  }

  return ret;
}


ostream&
operator<< (ostream& os, const TemplateEntry& tmpl)
{
  cerr << "-------------- Template for::::";
//  parser.PrintStepName(&tmpl.stepname);
  cerr << endl << "OPENC:" << endl;
  parser.PrintNodes(tmpl.preconds);
  cerr << endl << "EFFECTS: " << endl;
  parser.PrintNodes(tmpl.effects);
  cerr << endl;
  cerr << "Scope :::: " << tmpl.context << endl;
  cerr << endl;
  return os;
}




