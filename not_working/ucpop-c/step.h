#ifndef STEP_H
#define STEP_H

#include "objects.h"
#include "openc.h"
#include "effect.h"
#include "gc.h"
#include "list.h"

/* A step doesn\'t really have to know about its effect, except at start up
 * time;  the effects though should know about the step.  
 * Eventually,  the destructive Prepend and Append should have no 
 * hostile effect
 */

class TemplateEntry;

class Step : public GC {
     friend ostream& operator<< ( ostream&, Step& );
public:  
  StepId GetId() const;
  Step(StepId idNum=0);
  Step(const TemplateEntry& entry, Context context, StepId id);
  Step(const List<Openc>&, StepId idNum); 
  Step(const List<Effect>&, StepId idNum);
//  Step(const Step& s, int incontext, int idnum);
  const List<Openc>& GetOpencs() const;
  const List<Effect>& GetEffects() const;
  void PrettyPrint(ostream& os, const CS& cs);
private:
  Term term;			 // "name" of the step
  StepId id;			 // creation id
  List<Effect> effects;		 // list of effects the step adds
  List<Openc> opencs;	       	 // list of open conditions to fulfill
// There is no obvious need for keeping this?
//  int context;			 // context of all variables
};

#ifndef OUTLINE
#include "step.icc"
#endif

#endif
