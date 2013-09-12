#include <iostream.h>
#include "gc.h"
#include "objects.h"
#include "openc.h"
#include "unsafe.h"
#include "parser.h"
#include "template.h"
#include "list.h"
#include "planner.h"
#include "utility.h"
#include "searchqueue.h"
#include "logic.h"
#include "order.h"
#include "step.h"
#include "link.h"
#include "slist.h"
#include "plan.h"
#include "timer.h"
#include <math.h>

extern DomainTemplate templates;
extern FILE* yyin;

extern "C" {
  void yyerror(char*);
  int yyparse(void);
}

Parser parser;
Planner planner;
Timer timer;

//SListNode<int> SList<int>::NilSListNode;
//SListNode<StepId> SList<StepId>::NilSListNode;

     
int
main(int argc, char** argv)
{
#ifdef DEBUG
  if (argc==4) {
    debugFlags+= _ACTION_;
    debugFlags+= _ORDER_;
    debugFlags+= _LINK_;
//   debugFlags+= _PLAN_;
    debugFlags+= _TEMPL_;
//   debugFlags+= _DEL_;
//   debugFlags+= _VAR_;
    debugFlags += _SEARCH_;
  }
#endif
  if ((argc < 2) || !argv[2]) {
     cerr << "Usage: ucpop problem domain-file [limit]" << endl;
     exit(1);
   }
  
  if (!(yyin=fopen(argv[2], "r"))) {
    cerr << argv[2] << ": No such file or directory" << endl;
    exit (1);
  }
  // search limit arg
  if (argv[3]) 
    planner.SetLimit(atoi(argv[3]));
  parser.ParseFile();
  DBG(_ACTION_, cerr << "\n:: Parser finished.\n");
  Plan* result;
  if (result=planner.Solve(argv[1])) result->PrettyPrint(cerr);
  cerr << endl;
  timer.PrintStatistics(cerr);
  return (0);
}



