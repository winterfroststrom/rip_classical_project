#ifndef ORDER_H
#define ORDER_H

#include "bitstring.h"
#include "utility.h"
#include "objects.h"
#include "gc.h"
#include "list.h"

//
// order.h takes care of partial ordering stuff
// $Id: order.h,v 1.3 1993/07/04 05:06:19 ctkwok Exp $
// $Log: order.h,v $
// Revision 1.3  1993/07/04  05:06:19  ctkwok
// snlp
//
// Revision 1.2  1993/02/06  12:13:28  ctkwok
// Change from using templates to new data struct.
//
// Revision 1.1  1993/01/27  03:33:02  ctkwok
// Initial revision
//
//

// Using the above definition,  the first step must be 2

//typedef List<Pair> Ordering;

class Pair : public GC {
     friend ostream& operator<<(ostream& os, const Pair& p);
public:
  Pair(StepId f1, StepId f2);
  Pair(const Pair& p);
  StepId GetFirst() const;
  StepId GetSecond() const;
private:
  StepId first;
  StepId follow;
};

// BitString
// PossiblyAfter(int stepId, int highStep, const List<Pair>& ordering);
// BitString
// PossiblyBefore(int stepId, int highStep, const List<Pair>& ordering);
// BitString 
// PossiblyBetween(int step1, int step2, int highStep, const List<Pair>& ordering);
// 

#ifndef OUTLINE
#include "order.icc"
#endif

#endif
