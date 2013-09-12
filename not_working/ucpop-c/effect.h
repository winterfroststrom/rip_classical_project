#ifndef EFFECT_H
#define EFFECT_H

#include "list.h"
#include "logic.h"
#include <iostream.h>
#include "gc.h"
// 
// $Id: effect.h,v 1.1 1993/08/08 06:08:04 ctkwok Exp ctkwok $
// $Log: effect.h,v $
// Revision 1.1  1993/08/08  06:08:04  ctkwok
// Initial revision
//
// Defines Effects structures of the plan
//

typedef SList<Term> AddList;

// how this works: 

//want: put something down,  at parsing,  indicative of being univ.
// but wouldn't occupy variable name space during runtime

class Effect : public GC  {
     friend ostream& operator<< ( ostream&, const Effect&);
public:
  Effect();
  Effect(const Node& addlist, StepId own, Context ctx);

  StepId             GetOwner()                             const;
  const AddList&     GetAdd()                               const;
  const List<Openc>& GetPrecond()                           const;
  Context            GetBase()                              const;
  List<Openc>        PeelGoal(const ReplTable& table)       const;
  List<Openc>        PeelNegGoal(const ReplTable& table)    const;
  bool               IsConditional()                        const;
  bool               IsQuantified()                         const;
  
private:
  StepId owner;			 // step-id of owner
  AddList add;                   // list of effect terms
  List<Node> preconds;	         // raw template for conditional clauses
  List<Node> negPreconds;        // raw template for negation of above
  Context context;               // context of the effect
  Context base;                  // exact name space: for universals
};

List<Openc> InstantiateOpenc(const List<Node>& l, StepId owner, Context context);
List<Effect> InstantiateEffect(const List<Node>& l, StepId owner, Context context);

#ifndef OUTLINE
#include "effect.icc"
#endif

#endif // EFFECT_H
