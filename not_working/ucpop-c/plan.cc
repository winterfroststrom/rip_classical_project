#include "bitstring.h"
#include "openc.h"
#include "effect.h"
#include "order.h"
#include "logic.h"
#include "link.h"
#include "unsafe.h"
#include "plan.h"
#include "step.h"
#include "template.h"
#include "list.h"

//
// Plan.cc defines the main routines for ucpop
// $Id: plan.cc,v 1.3 1993/07/04 05:06:19 ctkwok Exp $
// $Log: plan.cc,v $
// Revision 1.3  1993/07/04  05:06:19  ctkwok
// snlp
//
// Revision 1.2  1993/06/26  11:02:57  ctkwok
// unseparated version
//
// Revision 1.1  1993/06/25  06:04:04  ctkwok
// Initial revision
//
// Revision 1.1  1993/02/08  11:33:12  ctkwok
// Initial revision

// initial plan constructor


Context Plan::planCount=0;
List<Varset>* EmptyList=new List<Varset>;
ReplTable Plan::table;

#ifdef OUTLINE 
#define inline
#include "plan.icc"
#undef inline
#endif

// default ranking function


Plan::Plan(const List<Node>& initialConds, const List<Node>& goals)
: highStep(0), 
  opencs(),
  effects(InstantiateEffect(initialConds, INIT, INITIAL_CONTEXT)),
  ordering(),
  steps(),
  links(),
  unsafes(),
  bindings(),
  planContext(INITIAL_CONTEXT),
  planRank(0)
#ifdef DEBUG
     ,parentId(0),
   planId(planCount++)
#endif
{
  Step* goal=new Step(InstantiateOpenc(goals, GOAL, INITIAL_CONTEXT), GOAL);
  steps += goal;
  opencs += goal->GetOpencs();
}


Plan::Plan( StepId highstep, 
	    const List<Step>& stepl, 
	    const List<Openc>& opencl,
	    const List<Effect>& effectl, 
	    const List<Link>& linkl, 
	    const List<Unsafe>& unsafel, 
	    const List<Pair>& orderl,
	    const List<Varset>& newCS,
	    Context context
#ifdef DEBUG
	    ,int parent
#endif
	    )
: highStep( highstep ), 
  ordering( orderl ), 
  steps( stepl ),
  opencs( opencl ), 
  effects( effectl ), 
  links( linkl ),
  unsafes( unsafel ), 
  bindings( newCS ),
  planContext( context ),
  planRank(0)
#ifdef DEBUG
  ,planId(planCount++),
  parentId(parent)
#endif
{
#ifndef DEBUG
  planCount++;
#endif;
}


ostream&
operator<<(ostream& os, const Plan& plan)
{
#ifdef DEBUG
  os << "Plan #" << plan.planId << "=>\n";
  os << "p" << plan.parentId << ":::::::::" << endl;
#endif
  os << "Steps::=    " << endl << plan.steps << endl;
  os << "Ordering::= " << endl << plan.ordering << endl;
  os << "Links::=    " << endl << plan.links << endl;
  os << "Opencs::=   " << endl << plan.opencs << endl;
  os << "Effects::=  " << endl << plan.effects << endl;
  os << "Unsafes::=  " << endl << plan.unsafes << endl;
  os << "Bindings::= " << endl << plan.bindings << endl;
  os << "Context::= "  << plan.planContext << endl;
  os << "Rank::= " << rankPlan(plan) << endl;
  return os;
}
     
#define HERE cerr << "HERE!!!!!!!!!!!!!!!!!!!" << endl

void
Plan::TestLink(const Link& link)
{
  DBG(_ACTION_, cerr << "Testing Link: " << link << endl);
  StepId producer=link.GetProducer();
  BitString betweenIds(PossiblyBetween(producer,
				       link.GetConsumer()));
  DBG(_LINK_, cerr << "Between Ids: " << betweenIds << endl);

  SITERATE_NO_INIT(addCond, aptr, Term);
  StepId effectId;
  Ustatus ustatus;
  // INIT will not normally affect a link except for CW steps
  ITERATE(effect, effects, next, Effect);
  DOLIST (effect, next) {
    effectId=effect->GetOwner();
    if ((effectId!=INIT) ? (betweenIds==effectId) : (producer==CWSTEP))
       {
	 aptr=effect->GetAdd();
	 SDOLIST (addCond, aptr) {
	   ustatus=bindings.Affects(addCond, link, effect->GetBase());
	   if (ustatus!=CannotU) { // IsU or MayU
	     unsafes.Push(new Unsafe(link, *effect, addCond));
	   }
	 }
       }
  }
}


void
Plan::TestEffects(const List<Effect>& effs, StepId effId)
{
  DBG(_ACTION_, cerr << "Testing Effects...." << endl);
  BitString prior(PossiblyBefore(effId));
  BitString after(PossiblyAfter(effId));
  ITERATE(effect, effs, eptr, Effect);
  SITERATE_NO_INIT(addCond, aptr, Term);
  StepId producer, consumer;

  ITERATE(link, links, next, Link)
  DOLIST (link, next) {
//    DBG(_LINK_,cerr << "Looking at :::::: " << *link << endl);
    producer=link->GetProducer();
    consumer=link->GetConsumer();
    if ((producer==INIT || producer==CWSTEP || prior==producer) &&
	(after==consumer))
       {
	 eptr.Reset();
	 DOLIST (effect, eptr) {
	   aptr=effect->GetAdd();
	   SDOLIST (addCond, aptr) {
	     if (bindings.Affects(addCond, *link, effect->GetBase()))
		unsafes.Push(new Unsafe(*link, *effect, addCond));
	   }
	 }
       }
  }
}




List<Plan>
Plan::NewLink(Openc& oc, Step& s, Context context)
{

  SITERATE_NO_INIT(term, tptr, Term);

  StepId            id=oc.GetOwner();
  StepId            stepId=s.GetId();
  List<Varset>*     vs;
  List<Plan>        newPlans;
  Plan*             newPlan;
  Link*             newLink;
  List<Pair>        tmpOrder;
  
  DBG(_ACTION_, cerr << "New Link I for " << oc << ":" << endl);

  ITERATE (effect, s.GetEffects(), next, Effect)
  DOLIST (effect, next) {
    tptr=effect->GetAdd();

    SDOLIST (term, tptr) {
      if (vs=(effect->IsQuantified()) ?
	  bindings.Unify(term, oc, table, effect->GetBase()) :
	  bindings.Unify(term, oc))
	 {
	   newLink=new Link(stepId, oc, id);	   
	   DBG(_ACTION_, cerr << table << endl << "==== ===== === PEEL GOAL: " << effect->PeelGoal(table) << endl);
	   
	   DBG(_LINK_, cerr << "New Link: " << *newLink << endl);

	   if (id==GOAL) tmpOrder=ordering;
	   else tmpOrder=ordering + new Pair(stepId, id);

	   newPlan=TweakPlan( stepId,
			      steps + s,
			      opencs - oc,
			      effects + s.GetEffects(),
			      (links + newLink),
			      unsafes,
			      tmpOrder,
			      vs,
			      s.GetOpencs() + effect->PeelGoal(table),
			      context + planContext );
	   DBG(_ORDER_, cerr << "Adding order: (" << stepId << "," << id << ")" << endl);
	   if (newPlan) {
	     DBG(_PLAN_, cerr << "new plan :::::::::::::::: " << endl << *newPlan);
	     newPlan->TestLink(*newLink);
	     newPlan->TestEffects(s.GetEffects(), stepId);
	     DBG(_ACTION_, cerr << "Done Checking." << endl);
	     newPlans += newPlan;
	   }
	 }
    }
  }
  return newPlans;
}


List<Plan>
Plan::NewLink(Openc& oc, const BitString& prior)
{
  DBG(_ACTION_, cerr << "New Link II for " << oc << ":" << endl);
  StepId         id=oc.GetOwner();
  StepId         effectId;
  List<Varset>*  vs;
  List<Plan>     newPlans;
  Plan*          newPlan;
  Link*          newLink;
  List<Pair>     tmpOrder;
  
  SITERATE_NO_INIT(term, tptr, Term);  

  ITERATE(effect, effects, next, Effect);
  DOLIST (effect, next) {
    tptr=effect->GetAdd();
    effectId=effect->GetOwner();

    if ((effectId==INIT) && (oc.IsNegation()) &&
	(newPlan=NewCWLink(oc, id, *effect)))
       newPlans.Push(newPlan);

    SDOLIST (term, tptr) {
      if ((effectId==INIT || effectId==CWSTEP || prior==effectId) &&
	  (vs=(effect->IsQuantified()) ?
	   bindings.Unify(term, oc, table, effect->GetBase()) :
	   bindings.Unify(term, oc)))
	  {
	   DBG(_ACTION_, cerr << table << endl << "==== ===== === PEEL GOAL: " << effect->PeelGoal(table) << "  FOR BASE:::: " << effect->GetBase() << endl);

	    newLink=new Link(effectId, oc, id);
	    
	    DBG(_LINK_, cerr << "New Link: " << *newLink << endl);

	    if (effectId==CWSTEP ||effectId==INIT ||id==GOAL)
	       tmpOrder=ordering;
	    else tmpOrder=ordering + new Pair(effectId, id);

	    newPlan=TweakPlan( highStep,
			       steps,
			       (opencs - oc) + effect->PeelGoal(table),
			       effects,
			       (links + newLink),
			       unsafes,
			       tmpOrder,
			       vs
			       ); // <- add goal here when peel goal
	    DBG(_ORDER_, cerr << "Adding order: (" << effectId << "," << id << ")" << endl);
	    if (newPlan) {
	      newPlan->TestLink(*newLink);
	      DBG(_PLAN_, cerr << "new plan :::::::::::::::: " << endl << *newPlan << endl);
	      newPlans += newPlan;
	    }
	  }
    }
  }
  return newPlans;
}


//because may not get a plan,  you better return a pointer
Plan*
Plan::NewCWLink(Openc& oc, StepId id, const Effect& effect)
{// effect is one of the initial conditions; oc is a negation
  // this fails iff an initial cond truly affects the link, in which case
  // the threat is unresolvable.
  DBG(_ACTION_, cerr << "Forming CW Link for: " << oc << endl);

  List<Unsafe> bindGoals;
  Ustatus unifResult;
  Link* newLink=new Link(CWSTEP, oc, id);
  Plan* newPlan;

  DBG(_LINK_, cerr << "CW link " << *newLink << endl);
  // look for potential threats
  SITERATE(addCond, effect.GetAdd(), next, Term);
	  
  SDOLIST(addCond, next) {
    if (!addCond.IsNegation() &&
	(unifResult=bindings.Affects(addCond, oc, effect.GetBase())))
       {
	 if (unifResult==IsU) {
	   delete newLink; // collect garbage in bindGoals here too.
	   return NULL;
	 } else { // MayU
	   bindGoals+=new Unsafe(*newLink, effect, addCond);
	 }
       }
  }

  newPlan=TweakPlan( highStep, steps,
		     opencs - oc,  effects,
		     links + newLink,
		     unsafes + bindGoals,
		     ordering,  EmptyList );

  if (newPlan) newPlan->TestLink(*newLink);
  DBG(_PLAN_, if (newPlan) cerr << "CW Plan::::: " << endl << *newPlan << endl);
  return newPlan;
}


// // I suspect you can actually resolve all the threats at one shot?
List<Plan>
Plan::Refine()
{
  List<Plan> newPlans;
  StepId effectId;

  ITERATE(unsafe, unsafes, next, Unsafe);
  DOLIST (unsafe, next) {
    DBG(_ACTION_, cerr << "Looking at threat: " << unsafe << endl);
    effectId = unsafe->GetCEffect().GetOwner();

    if ((effects==unsafe->GetCEffect()) &&
	(effectId==INIT ||
	(PossiblyBetween(unsafe->GetProducer(),
			 unsafe->GetConsumer())==effectId)))
       {
	 switch (bindings.Affects(unsafe->GetCCondition(),
				  *unsafe,
				  unsafe->GetCEffect().GetBase()))
	    {
	    case CannotU: // bogus unsafe
	      DBG(_ACTION_, cerr << "Remove BOGUS..............." << endl);
	      return newPlans += TweakPlan( highStep, steps,  opencs,
					    effects, links,
					    (unsafes - unsafe),
					    ordering,  EmptyList );
	      break;
	    case MayU:
	      continue;
	      break; // not reached
	    case IsU: // must solve
	      DBG(_ACTION_, cerr << "Resolving threat: " << unsafe << endl);
	      newPlans+=Promote(*unsafe);
	      newPlans+=Demote(*unsafe);
	      newPlans+=Disable(*unsafe);
	      return newPlans;
	    }
       } else {
	 // elimitate this threat
	 DBG(_ACTION_, cerr << "Remove BOGUS..............." << endl);
	 return newPlans += TweakPlan( highStep, steps,  opencs,
				       effects, links,
				       (unsafes - unsafe),
				       ordering,  EmptyList );
       }
  }
  // newPlans is empty,  nothing was resolved
  return HandleOpen(*opencs.First()); // is empty here
}

Plan*
Plan::Demote(Unsafe& unsafe)//, const List<Unsafe>& newUnsafes)
{
  StepId clobberId=unsafe.GetCEffect().GetOwner();
  StepId id=unsafe.GetProducer();
//  DBG(_ORDER_, cerr << PossiblyBefore(id));
  if (PossiblyBefore(id)==clobberId) {
    DBG(_ACTION_, cerr << "demoting to: " << clobberId << "," << id << endl);
    return TweakPlan( highStep, steps, opencs, effects, links,
		      unsafes - unsafe,
//		      newUnsafes,
		      (ordering + new Pair(clobberId, id)),
		      EmptyList );
  } else return NULL;
}		       


Plan*
Plan::Promote(Unsafe& unsafe)//, const List<Unsafe>& newUnsafes)
{
  StepId clobberId=unsafe.GetCEffect().GetOwner();
  StepId id=unsafe.GetConsumer();
  if (PossiblyBefore(clobberId)==id) {
    DBG(_ACTION_, cerr << "promoting to: " << id << "," << clobberId << endl);
    return TweakPlan( highStep, steps, opencs, effects, links,
		      unsafes - unsafe,
//		      newUnsafes,
		      (ordering + new Pair(id, clobberId)),
		      EmptyList );
  } else return NULL;
}		       


Plan*
Plan::Disable(Unsafe& unsafe)
{
  DBG(_ACTION_, cerr << "Disabling " << unsafe << endl);
  const Effect& eff=unsafe.GetCEffect();
  // no point in doing disabling when the effect is not conditional
  if (!eff.IsConditional()) return NULL;
  StepId effectId=eff.GetOwner();
  List<Pair> ord=ordering;
  table.AddBind(unsafe.GetCCondition(), (Term)unsafe, eff.GetBase());
  
  if (unsafe.GetProducer()>0)
     ord += new Pair(unsafe.GetProducer(), effectId);
  if (unsafe.GetConsumer()>0)
     ord += new Pair(effectId, unsafe.GetConsumer());

  return TweakPlan( highStep, steps, opencs, effects, links,
		    unsafes - unsafe,
		    ord,
		    // hack the following for the moment
		    EmptyList,
		    eff.PeelNegGoal(table), // this is wrong
		    planContext
		    ); 
}



List<Plan>
Plan::HandleOpen(Openc& oc) 
{
  if (!opencs.Empty()) {	 // safety check
    DBG(_ACTION_, cerr << "handling openc: " << oc << endl);
    // I shouldn't handle And here?!
    ASSERT(oc.GetType()==Or || oc.GetType()==Ordinary); 
    return (oc.GetType()==Ordinary) ?  
       (AddStep(oc) + ReuseStep(oc)) : HandleOR(oc);
  } else {
    List<Plan> noPlans;
    return noPlans;
  }
}



// pass openc,  because you want to delete oc from the opencs.
List<Plan>
Plan::HandleOR(Openc& openc)
{
  DBG(_ACTION_, cerr << "Handling or: " << openc << endl);
  List<Plan> newPlans;
  List<Openc> tmp(opencs - openc);
  Plan* plan1;
  ITERATE(oc, openc.GetList(), ocptr, Openc);
  
  DOLIST (oc, ocptr) {
    plan1=TweakPlan( highStep,
		     steps,
		     tmp,
		     effects,
		     links,
		     unsafes,
		     ordering,
		     EmptyList,
		     oc );
    newPlans+=plan1;
  }
  return newPlans;
}


void
Plan::PrettyPrint(ostream& os)
{
  ITERATE(s, steps, nextstep, Step);
  ITERATE(l, links, nextlink, Link);
  DOLIST(s, nextstep) {
    s->PrettyPrint(os, bindings);
    nextlink.Reset();
    DOLIST(l, nextlink) {
      if (l->GetConsumer() == s->GetId())
	 os << "\t" << l->GetProducer() << " -> " << (Term)*l << endl;
    }
  }
  os << endl << "ORDER: " << ordering << endl;
}


//DECLAREPRINT(Plan)
