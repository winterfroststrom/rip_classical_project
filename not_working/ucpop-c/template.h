#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <iostream.h>
#include "gc.h"

// class to generate step templates from the user specs */
// IO between parser and planner
// template slots to be filled in are marked by a dummy number starting
// from -1, constants from 1 to ??,  and variables are -ve
//
// $Log: template.h,v $
// Revision 1.1  1993/07/04  05:06:19  ctkwok
// Initial revision
//
//
#include "symtab.h"
#include "str.h"
#include "logic.h"
#include "list.h"
#include "objects.h"

//
// template entries provide info about the number of variables the step
// needs and the template itself;  also the template knows how many
// constants are there in the universe
//

class TemplateEntry : public GC {
  friend class DomainTemplate;
  friend ostream& operator<< (ostream& os, const TemplateEntry& tmpl);
public:
  TemplateEntry(Term& stepName,
		List<Node> precondChain, 
		List<Node> effectChain,
		Context currentContext
		);

  Context             GetContext()    const;
  const Term&         GetTerm()       const;
  const List<Node>&   GetEffects()    const;
  const List<Node>&   GetPreconds()   const;
  TemplateEntry&      Instantiate(List<Node> InitialConditions);
  
private:
  Term       stepname;    // name of the step
  List<Node> preconds;    // open condition templates
  List<Node> effects;     // effect templates
  Context    context;     // size of the name space
};


class DomainTemplate : public List<TemplateEntry> {
public:
  DomainTemplate();
  void                 SaveSymbolTable(UCPOPSymTab& symtab);
  List<TemplateEntry>  Instantiate(List<Node> initialConditions); 
  DomainTemplate&      operator=(List<TemplateEntry> l);
private:
  SelectStep(Term& e);
  // instantiate the universals
private:
//  String domainName; // name of the domain
  UCPOPSymTab* symbolTable;
  Sym currentContext;
};

extern DomainTemplate templates;
extern DomainTemplate rawTemplates;

List<Node> InstantiateQuantified(List<Node> tmpl,
				 List<Node> initialConditions);


#ifndef OUTLINE
#include "template.icc"
#endif


#endif

