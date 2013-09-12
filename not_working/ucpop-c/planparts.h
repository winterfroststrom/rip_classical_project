#ifndef _PLAN_H_
#define _PLAN_H_

#include "utility.h"
#include "objects.h"
#include "varset.h"
#include "BitString.h"
#include "order.h"
#include "list.h"
#include "table.h"
#include "template.h"
#include <iostream.h>

/* va-arg list */
		       
#define NULL          0
#define PlanSteps     1
#define PlanLinks     2
#define PlanEffects   3
#define PlanUnsafe    4
#define PlanOpen      5
#define PlanOrdering  6
#define PlanBindings  7
#define PlanHighStep  8
#define PlanAddGoal   9
#define MaxArgTypes  10

/* 
 * $Id: planparts.h,v 1.1 1993/04/22 23:23:19 ctkwok Exp $ 
 * $Log: planparts.h,v $
 * Revision 1.1  1993/04/22  23:23:19  ctkwok
 * Initial revision
 *
 * Components of a plan.
 */

/* Many Lists could be implemented as inheritence, but.... */

/* doesn\'t handle OR */

class Plan;

// Table for forall is not associated with Effect
class Effect {
     friend ostream& operator<< ( ostream&, Effect&);
public:
  Effect(Term *t, int ow) {term = new Term(*t); owner = ow;}
  List *Test(Plan *plan); 	 // test if this effect threatens
  OpencDataNode* PeelGoal(Term*,Term*); // for binding
  
  int owner;			 // step-id of owner
  List* preconds;		 // precond list
  List* terms;			 // add-conds
  FSet* forall;			 // forall variables in the list
};


class Openc {
     friend ostream& operator<< ( ostream&, Openc& );
public:
  Openc(Term* t, int s) {term=t;owner=s;} // uses the pointer

  Term *term;
  int owner;			 // owner\'s id
};

class Link {
     friend ostream& operator<< ( ostream&, Link& );
public:
  Link(int id1, Term* term, int id2) {consumer=id1;producer=id2;t=term;}
  List* Test(Plan *plan);

  Term *t;
  int consumer;
  int producer;
};

class Unsafe {
     friend ostream& operator<< ( ostream&, Unsafe& );
public:  
  Unsafe( Link*, Effect*, Openc* );
  Link *ln;
  Effect *clobberEffect;
  Openc *clobberCondition;
};


// Is there need to copy the terms or can I just use ptrs?
inline 				 
Unsafe::Unsafe( Link *l, Effect *e, Openc *oc )
{
  link = l;
  clobberEffect = e;
  clobberCondition = oc;
}

/* A step doesn\'t really have to know about its effect, except at start up
 * time;  the effects though should know about the step.  
 * Eventually,  the destructive Prepend and Append should have no 
 * hostile effect
 */

class Step {
     friend ostream& operator<< ( ostream&, Step& );
public:  
  Step(Term *t, int stepID..??)

  Term *term;			 // "name" of the step
  int id;			 // creation id

  EffectList* effects;		 // list of effects the step adds
  List* opencs;	        	 // list of open conditions to fulfill
  int context;			 // context of all variables
};

// inherited from List to provide openc handling
class OpencList : public List {
public:
  OpencList(const OpencList &olist) {List((List&)olist);}
  void Add(Step *s);
  void Add(OpencDateNode* odn){ol->Prepend((void*)odn)};
  Openc GetNextOpenCond();
};


inline void
OpencList::Add(Step *s)
{
  // s should already been instantiated!
  if (s) Add((void*) new OpencDateNode(s->opencList,s,NULL));
}


class OpencDataNode {
  OpencDataNode (List *l, Step *s, Table *t=NULL) {opencs=new List(l); owner=s;
					      forallTable=t;}

  void *GetNextOpenc(int *flag); // flag is for denoting the type

  Instantiate(Openc* oc);	 // instantiate 

  Step *owner;			 // remembering step is more useful 
private:
  Table* forallTable;		 // an array of terms to interpret as special
  List *opencs;
  Openc *GetOpenc();		 // get uninstantiated
};  

class EffectList {
public:
  EffectList(const EffectList &elist) {ef=new List(elist.ef);t=elist.t;
				       e=elist.e;}
  Add(...);
  Test(Link*);			 // test if the link is threatened by anyone
  EffectList () {ef=new List;Reset();}
  Effect *GetNextUnify(Openc *oc);
  Term *GetNextAddCond();	 // this will return a Non-null,  if null means 				 // no more
private:
  List *ef;
  Term *t;			 // cache
  Effect *e;			 // cache
};

class UnsafeList : public : List {
public:
  void Add(Unsafe *unsafe-ln) {Prepend(unsafe-ln);}
  Unsafe *PopUnsafe {(Unsafe*)ul->Pop();}
};


class StepsList : public List {
public:
  void Add(Step *s) {Prepend(s);} // prepend for sharing
  Step *GetStep(int id);
};


// get a step with name id
inline Step*
StepList::GetStep (int id)
{
  Reset();
  Step *s;
  for(Reset();NotAtEnd();s=++(*this)) 
     if (s->id==id) return s;
  return NULL;
}

class LinkList : public List {
public:
  LinkList(const LinkList &, Link*);
  void Add (Link *li) {ll->Prepend(li);}
  Test (Effect* e);
};
