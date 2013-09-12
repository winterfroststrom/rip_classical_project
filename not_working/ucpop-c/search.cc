#include "utility.h"
#include "plan.h"
#include "searchqueue.h"

// return a plan,  if any
// use a non-generic one first
//#pragma define_template SearchQueue<Plan>

int
rankPlan(const Plan& plan)
{
  return plan.unsafes.Length() + plan.steps.Length() + plan.opencs.Length();
}



int
comparePlans(const void* p1, const void* p2)
{
  static int rank1;
  static int rank2;
  return ((rank1=(**(Plan**)p1).GetRank()) >
	  (rank2=(**(Plan**)p2).GetRank())) ? 1 : ((rank1<rank2)?-1:0);
}
  
Plan*
BestFirstSearch(Plan& initialPlan, int limit)
{
  Plan* currentState;
  // CHILDREN LIST can be elimiated later!
  List<Plan> childrenList;
  SearchQueue<Plan> queue(&initialPlan);
  int nodesVisited=0;
  
  while ((currentState=queue.GetFirst()) &&
	 (!currentState->IsComplete()) && (limit>=0))
     {
       nodesVisited++;
       
       DBG(_SEARCH_,
	   cerr << endl << endl << "Node ##################### " \
	   << nodesVisited << " ** Has Rank of===> " << \
	   rankPlan(*currentState) << endl << \
	   endl << *currentState << endl << endl);
       
       childrenList=currentState->Refine();
       
       DBG(_SEARCH_,
	   cerr << "This has " << childrenList.Length() << \
	   " children." << endl);
       limit-=(queue.Merge(childrenList));
       delete currentState;
     }
  cerr << "nodes searched: " << nodesVisited << " with " << \
     Plan::planCount << " plans created. " << endl;
  if (currentState && currentState->IsComplete())
     return currentState;
  else return NULL;
}

