#ifndef UNSAFE_H
#define UNSAFE_H
// unsafe/threatened links

#include "utility.h"
#include <iostream.h>
#include "objects.h"
#include "link.h"
#include "gc.h"

class Effect;

class Unsafe : public Link {
  friend ostream& operator<< ( ostream&, const Unsafe& );
public:  
  Unsafe(const Link&, const Effect&, const Term&);
  const Effect&   GetCEffect() const;
  const Term&     GetCCondition() const;
private:
  const Effect& clobberEffect;
  Term          clobberCondition;
};


#ifndef OUTLINE
#include "unsafe.icc"
#endif

#endif

