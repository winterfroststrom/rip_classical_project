#include "link.h"
#include "list.h"

#ifdef OUTLINE
#define inline
#include "link.icc"
#undef inline
#endif

ostream&
operator<<(ostream& os, const Link& l)
{
  os << "[link=> ";
  os << "p:" << l.producer << " ";
  os << "c:" << l.consumer << " ";
  os << (Term&)l;
  os << "]";
  return os;
}

DECLAREPRINT(Link)
