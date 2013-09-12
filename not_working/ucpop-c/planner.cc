#include "timer.h"
// plan.h has to precede list.h (or "list.h" cannot precede is more appro)
#include "plan.h"
#include "list.h"
#include "logic.h"
#include "parser.h"
#include "planner.h"


#ifdef OUTLINE
#define inline
#include "planner.icc"
#undef inline
#endif

Plan*
BestFirstSearch(Plan& initialPlan, int limit);

extern Parser parser;
extern Timer timer;

#include "template.h"
DECLAREPRINT(TemplateEntry);

Problem::Problem(char* nm, Node& init, Node& goal)
: name(nm), inits(), goals() 
{
  // have to do this,  since Node takes in a ref
  List<Node>& tmp=*new List<Node>;
  tmp += init;
  goals += goal;
  ReformTree(tmp); // clean up the user defined list
  ReformTree(goals);
  tmp=RemoveAndTree(tmp); 
  goals=RemoveAndTree(goals);
  inits += new Node(tmp, And); // conform to the InstantiateEffect semantics
}


Planner::Planner(int limit)
: name("UCPOP beta"), problems(), searchLimit(limit)
{}

// fail return null plan (?)
Plan*
Planner::Solve(const String& name)
{
  Plan* result;
  ITERATE(p, problems, next, Problem);
  
  DOLIST (p, next) {
     if (p->GetName()==name) break;
     DBG(_PROBLEM_, cerr << p->GetName() << endl);
   }
  // handle errors here.
 if (!p) {
    cerr << "Error: Problem not found." << endl;
    return NULL;
  }

  templates = rawTemplates.Instantiate(p->GetInitConds());
  
  DBG(_TEMPL_, cerr << "FINAL templates :: " << endl << templates << endl);
  cerr << endl <<  "Solving " << p->GetName() << " ...\n";
  timer.StartRecording();

  List<Node> goals=InstantiateQuantified(p->GetGoals(), p->GetInitConds());
  Plan& initialPlan = *new Plan(p->GetInitConds(), 
				goals);

  if (result=BestFirstSearch(initialPlan, searchLimit))
     cerr << "Complete!" << endl;
  else cerr << "Fail." << endl;
  timer.EndRecording();
  
  return result;
  
//  if (initialPlan.IsComplete()) cerr << "ERROR1\n";
//   cerr << "Result:: " << endl << initialPlan.Refine();
//   cerr << endl << initialPlan << endl;
//   return NULL;
}


void
Planner::AddProblem(Problem& problem)
{
  problems += problem;
}

void
Planner::SetLimit(int limit)
{
  searchLimit=limit;
}
