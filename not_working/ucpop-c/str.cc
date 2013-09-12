#include "str.h"

#ifdef OUTLINE
#define inline
#include "str.icc"
#undef inline
#endif

String::String(const char* s)
: length(strlen(s))
{
  str=new char[length+1];
  strcpy(str, s);
}


String::String(int len)
: length(len), str(new char[len+1]) {}


String::String()
: length(0), str(NULL) {}


String::String(const String& s)
: length(s.length), str(new char[s.length+1])
{
  strcpy(str, s.str);
}


String::~String()
{//DBG(_DEL_,cerr << "Deleting string: " << str << endl);
  delete [] str;}


ostream& 
operator<<(ostream& os, const String& s)
{os << s.str; return os;}
