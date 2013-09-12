#ifndef LINK_H
#define LINK_H

#include "objects.h"
#include <iostream.h>
#include "gc.h"
// link class

class Link : public Term, public GC {
     friend ostream& operator<< ( ostream&, const Link& );
public:
  Link(StepId id1, const Term& term, StepId id2);
  StepId GetProducer() const;
  StepId GetConsumer() const;
private:
  StepId consumer;
  StepId producer;
};

#ifndef OUTLINE
#include "link.icc"
#endif

#endif // LINK_H
