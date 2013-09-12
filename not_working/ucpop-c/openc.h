#ifndef OPENC_H
#define OPENC_H

#include <iostream.h>
#include "gc.h"
#include "objects.h"
class Node;
//
// $Id: openc.h,v 1.1 1993/08/08 06:10:35 ctkwok Exp ctkwok $
//

// openc IS A term!

template <class T> class List;

class Openc : public Term, public GC {
     friend ostream& operator<< ( ostream&, const Openc& );
public:
//  Openc();
//  Openc(const Openc& oc);
  Openc(Term& t, StepId own, Context context);
  Openc(Term& t, StepId own, Context context, const ReplTable& table);
  Openc(const Openc &oc, StepId owner, Context context=0);
  Openc(const List<Openc>& l, LogicPrimitive prim); // make a dummy OR node
//  bool operator==(const Openc& oc) const;
  StepId             GetOwner() const;
  const List<Openc>& GetList()  const;
private:
  StepId owner;			 // owner\'s id
};



List<Openc> InstantiateOpenc(const List<Node>& l,
			     StepId owner,
			     Context context);
List<Openc> InstantiateOpenc(const List<Node>& l,
			     StepId owner,
			     Context context,
			     const ReplTable& table
			      );

#ifndef OUTLINE
#include "openc.icc"
#endif

#endif // OPENC_H

