#include "utility.h"
#include "objects.h"
#include "openc.h"
#include "effect.h"


#ifdef OUTLINE
#define inline
#include "effect.icc"
#undef inline
#endif


ostream& 
operator<<(ostream& os, const Effect& e)
{
  os << "[effect=> ";

  SITERATE(t, e.add, next, Term);
  SDOLIST (t, next) {
    switch (t.GetType()) {
    case Ordinary: os << t; break;
    case And: os << t.GetList(); break;
    default:
      cerr << "ERROR";
    }
  }
  if (e.preconds.Valid()) cerr << " precond: " << e.preconds << " ";
  os << " own:" << e.owner;
  if (e.base) os << " base:" << e.base;
  os << " ]";
  return os;
}

  
DECLAREPRINT(Effect)
