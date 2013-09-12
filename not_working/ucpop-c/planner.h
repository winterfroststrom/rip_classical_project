#ifndef PLANNER_H
#define PLANNER_H
// the ucpop planner class

#include "str.h"
#include "gc.h"
#include "list.h"

class DomainTemplate;
class Node;
class Plan;


// class Domain {
//   String name;			 // I think this is optional
//   DomainTemplate *template;		 // a template of functions
// };


class Problem : public GC {
public:
  Problem(char*, Node& init, Node& goals);
  const String& GetName() const;
  const List<Node>& GetInitConds() const;
  const List<Node>& GetGoals() const;
private:
  String name;			 // optional name
  List<Node> inits;	 // initial conditions (Effects really)
  List<Node> goals;		 // List of openc
//  Domain domain;		 // domain where the problem belongs
};

// A planner takes a domain and a problem a solve it

class Planner {
public:
  Planner(int limit=2000);
//  Planner(SearchFunc searchfunc);        // use the search func for the planner
  Plan* Solve(const String& name);	 // returns a plan if any
  void AddProblem(Problem& problem);
  void SetLimit(int limit);
private:
  String name;
//  SearchFunc searchFunc;
  List<Problem> problems;
  int searchLimit;
};
  
#ifndef OUTLINE
#include "planner.icc"
#endif

#endif

