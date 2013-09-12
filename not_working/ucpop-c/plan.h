#ifndef _PLAN_H_
#define _PLAN_H_

#include "utility.h"
#include "gc.h"
#include "objects.h"
#include "unsafe.h"
#include "openc.h"
#include "order.h"
#include "step.h"
#include "varset.h"
#include "slist.h"
#include "list.h"


class Plan;

// the first 2 doesn't have to have real step #
#define CWSTEP -2   // step for closed world id
#define INIT   -1   // initial step id
#define GOAL   0    // goal step id
#define INITIAL_CONTEXT 0
class Node;
extern List<Varset>* EmptyList;

class Plan : public GC {
  friend ostream& operator<< (ostream& os, const Plan& plan);
  // to override the default rank function,  set rankPlan to different thing
  friend int rankPlan(const Plan&); // passed to sort
public:
  typedef int (*RankFunc) ();

  Plan(const List<Node>& initialConds, const List<Node>& goals);
  Plan( StepId highstep,
	const List<Step>& stepl,
	const List<Openc>& opencl, 
	const List<Effect>& effectl,
	const List<Link>& linkl, 
	const List<Unsafe>& unsafel,
	const List<Pair>& orderl, 
	const List<Varset>& newCs,
#ifdef DEBUG
	int parent,
#endif
	Context context
	);
  
  Plan*         TweakPlan( StepId highstep,
			   const List<Step>& stepl, 
			   const List<Openc>& opencl,
			   const List<Effect>& effectl, 
			   const List<Link>& linkl,
			   const List<Unsafe>& unsafel, 
			   const List<Pair>& orderl,
			   List<Varset>* newCs,
			   const List<Openc>& addGoal,
			   Context context
			   ) const;

  Plan*         TweakPlan( StepId highstep,
			   const List<Step>& stepl, 
			   const List<Openc>& opencl,
			   const List<Effect>& effectl, 
			   const List<Link>& linkl,
			   const List<Unsafe>& unsafel, 
			   const List<Pair>& orderl,
			   List<Varset>* newCs,
			   Openc* addGoal=NULL
			   ) const;
 
  List<Plan>    NewLink(Openc& oc, Step& step, Context context);
  List<Plan>    NewLink(Openc& oc, const BitString& prior);
  Plan*         NewCWLink(Openc& oc, StepId id, const Effect& effect);

  Plan*         Demote(Unsafe& unsafe);
  Plan*         Promote(Unsafe& unsafe);
  Plan*         Disable(Unsafe& unsafe);

  List<Plan>    Refine();
  List<Plan>    HandleOpen(Openc& oc);
  List<Plan>    HandleUnsafe();
  List<Plan>    HandleOR(Openc& goals);
  List<Plan>    AddStep(Openc& oc);
  List<Plan>    ReuseStep(Openc& oc);
  
  void          TestLink(const Link&);
  void          TestEffects(const List<Effect>& effs, StepId effectId);
  
  // ordering
  BitString     PossiblyAfter(StepId stepId)                const;
  BitString     PossiblyBefore(StepId stepId)               const;
  BitString     PossiblyBetween(StepId step1, StepId step2) const
  {return PossiblyBefore(step2) & PossiblyAfter(step1);}
  
  // checking goals
  bool          NewGoal(Openc& g);
  bool          HandleAnd(Openc& goals);
  bool          HandleAnd(const List<Openc>& goals);

  // misc
  bool          IsComplete() const;
  int           SetRank();
  int           GetRank()    const;
#ifdef DEBUG
  int           GetId() const {return planId;}
#endif

  void PrettyPrint(ostream& os);

public:
  static int planCount;          // special for counting plans
  static ReplTable table;        // ReplTable passed around to save space
private:
  StepId highStep; 		 // highest step number
  List<Pair> ordering;		 // plan ordering
  List<Step> steps;		 // list of steps
  List<Openc> opencs;      	 // list of opencs
  List<Effect> effects;     	 // list of effects
  List<Link> links;		 // list of links
  List<Unsafe> unsafes;         // list of unsafe links
  CS bindings;			 // plan bindings
  Context planContext;
  int planRank; // rank of the plan
#ifdef DEBUG
  int planId;   // plan id for debugging
  int parentId; // parent id
#endif
};

#ifndef OUTLINE
#include "plan.icc"
#endif

#endif
