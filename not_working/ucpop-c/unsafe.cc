#include "openc.h"
#include "effect.h"
#include "unsafe.h"


#ifdef OUTLINE
#define inline
#include "unsafe.icc"
#undef inline
#endif


ostream&
operator<< ( ostream& os, const Unsafe& u)
{
  os << "[unsafe=> " ;
  os << (Link)u ;
  os << " CEff:: ";
  os << u.clobberEffect;
  os << " CCond:: " << u.clobberCondition << "]";
  return os;
}


DECLAREPRINT(Unsafe)
