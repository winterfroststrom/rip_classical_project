#include "bitstring.h"
#include "plan.h"
#include "list.h"
#include "slist.h"
#include "order.h"

#ifdef OUTLINE
#define inline
#include "order.icc"
#undef inline
#endif

ostream&
operator<<(ostream& os, const Pair& p)
{
  os << "[" << p.first << "," << p.follow << "]";
  return os;
}

// ostream&
// operator<<(ostream& os, const List<Pair>& l)
// {
//   ITERATE(p, pptr, l, Pair);
//   os << "[" << p.first << "," << p.follow << "]";
//   return os;
// }

//DECLAREPRINT(Pair)

BitString
Plan::PossiblyAfter(StepId stepId) const //, int highStep, const List<Pair>& ordering)
{
  BitString ret(highStep+1, (stepId!=GOAL)?ON:OFF);
  // return all +ve steps if CWSTEP or INIT
  if (stepId>0) {
   
    SList<StepId>* table=new SList<StepId>[highStep+1];
    ITERATE(ord, ordering, next, Pair);
    DOLIST (ord, next)
       table[ord->GetSecond()]+=ord->GetFirst();
    
    SList<StepId> c;
    int tmp;
    c += stepId;
    while(!c.Empty()) {
      tmp=c.Pop();
      if (ret==tmp) {
	c += table[tmp];
	ret -= tmp;
      }
    }
    delete [] table;
  }
  return ret;
}


BitString
Plan::PossiblyBefore(StepId stepId) const //, int highStep, const List<Pair>& ordering)
{
  // 1+ due to 0
  BitString ret(highStep+1, (stepId!=INIT && stepId!=CWSTEP)?ON:OFF); 
  ret-=GOAL; // goal cannot be possibly before any step.
//  cerr << "For step: " << stepId << " initially " << ret << endl;
  if (stepId>0) {
   
    
    SList<StepId> *table=new SList<StepId>[highStep+1];
    ITERATE(ord, ordering, next, Pair);
    DOLIST (ord, next)
      table[ord->GetFirst()]+=ord->GetSecond();

    SList<StepId> c;
    int tmp;
    c += stepId;
    while(!c.Empty()) {
      tmp=c.Pop();
      if (ret==tmp) {
	c += table[tmp];
	ret -= tmp;
      }
    }
    delete [] table;
  }
  return ret;
}


//, int highStep, const List<Pair>& ordering)
// 
// // the first 2 doesn't have to have real step #
// #define CWSTEP -2   // step for closed world id
// #define INIT   -1   // initial step id
// #define GOAL   0    // goal step id
// #define INITIAL_CONTEXT 0
// 
// BitString
// PossiblyAfter(int stepId, int highStep, const List<Pair>& ordering)
// {
//   BitString ret(highStep+1, (stepId!=GOAL)?ON:OFF);
//   // return all +ve steps if CWSTEP or INIT
//   if (stepId>0) {
//    
//     ITERATE(ord, ordptr, ordering, Pair);
//     SList<int>* table=new SList<int>[highStep];
//     
//     while(ord=ordptr()) 
//        table[ord->GetSecond()]+=ord->GetFirst();
//     
//     SList<int> c;
//     int tmp;
//     c += stepId;
//     while(!c.Empty()) {
//       tmp=c.Pop();
//       if (ret==tmp) {
// 	c += table[tmp];
// 	ret -= tmp;
//       }
//     }
//     delete [] table;
//   }
//   return ret;
// }
// 
// 
// BitString
// PossiblyBefore(int stepId, int highStep, const List<Pair>& ordering)
// {
//   // 1+ due to 0
//   BitString ret(highStep+1, (stepId!=INIT && stepId!=CWSTEP)?ON:OFF); 
//   ret-=GOAL; // goal cannot be possibly before any step.
//   cerr << "For step: " << stepId << " initially " << ret << endl;
//   if (stepId>0) {
//    
//     ITERATE(ord, ordptr, ordering, Pair);
//     SList<int> *table=new SList<int>[highStep];
//     
//     while(ord=ordptr()) 
//        table[ord->GetFirst()]+=ord->GetSecond();
//     
//     SList<int> c;
//     int tmp;
//     c += stepId;
//     while(!c.Empty()) {
//       tmp=c.Pop();
//       if (ret==tmp) {
// 	c += table[tmp];
// 	ret -= tmp;
//       }
//     }
//     delete [] table;
//   }
//   return ret;
// }
// 
// 
// BitString 
// PossiblyBetween(int step1, int step2, int highStep, const List<Pair>& ordering)
// {return PossiblyBefore(step2, highStep, ordering) & PossiblyAfter(step1, highStep, ordering);}
// 
// //
// 
DECLAREPRINT(Pair)
     
