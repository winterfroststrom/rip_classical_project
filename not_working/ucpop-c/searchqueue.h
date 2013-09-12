#include "utility.h"
#include "list.h"
// 
// typedef bool (*GoalFunc) (const Plan&);
// typedef int (*RankFunc) (const Plan&);
// typedef List<Plan>& (*ChildrenFunc) (const Plan&);
// typedef int (*ComprFunc) (const void*, const void*);
// typedef Plan& (*SearchFunc) (Plan&        /*init-state*/, 
// 			     ChildrenFunc /*children*/,
// 			     GoalFunc     /*goal-p*/, 
// 			     RankFunc     /*rank*/, 
// 			     int          /*limit*/);

template <class T>
class SearchQueue {
public:
  SearchQueue(T* initialElem); //int (*compfunc) (const void*, const void*));
  int Merge(List<T> l);
  ~SearchQueue();
  T* GetFirst() const;
private:
  List<T>* queue;
  int upperboundRank;
};


#ifndef OUTLINE
#include "searchqueue.icc"
#endif

#include "searchqueue.cc"
