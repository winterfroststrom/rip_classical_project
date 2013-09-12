#ifndef PARSER_H
#define PARSER_H

#include <iostream.h>
#include "symtab.h"
//#include "template.h"
#include "list.h"
#include "objects.h"
#include "logic.h"
#include "symtab.h"

extern "C" {
  int yyparse(void);
}

class Parser {
     friend int yyparse(void);
     friend class Problem;
public:
  Parser();
//  DomainTemplate& GenerateTemplateFromParse();
  int       ParseFile();
  void      CreateOperator(Node& stepName,
		      List<Node> precondChain, 
		      List<Node> effectChain,
		      Context scope,
		      Context params);
  Context   NewScope();
  void      PrintTerm(Node* nod);
  void      PrintStepName(Node* nod);
  void      PrintNodes(const List<Node>& nl);
  String    TranslatePred(Pred p) const;
  String    TranslateSymbol(Sym s) const;
  String    TranslateStepName(const Term& t) const;
private:
  // reformation of logic statement into conjunctive normal form
  // and have extra 'and' stripped off
  friend void ReformTree(List<Node>& nl);
  friend void ReformNode(Node& nod);
  friend void NegateTree(List<Node>& nl);
  friend void NegateNode(Node& nod);

  // they are easier to write if separated.
  friend List<Node> RemoveAndTree(List<Node>&nl);
  friend List<Node> RemoveAndInOr(List<Node>& nod);
  friend List<Node> RemoveOrTree(List<Node>& nl);
  friend List<Node> RemoveOrInAnd(List<Node>& nod);
  friend List<Node> CopyTree(List<Node>& nod);
private:
  UCPOPSymTab symtab;
//  DomainTemplate& templates;
};

//#ifndef OUTLINE
//#include "parser.icc"
//#endif
  
#endif
