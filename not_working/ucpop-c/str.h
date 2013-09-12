// string class

#ifndef STRING_H
#define STRING_H

#include "utility.h"
#include <string.h>
#include <iostream.h>
#include <stdio.h>

class String {
     friend ostream& operator<< (ostream& os, const String& s);
public:
  String(const String&);
  String(const char*);
  String(int);
  String();
  ~String();
  int Length() const;
  bool operator==(const String&) const;
  bool operator!=(const String&) const;
  bool operator<(const String&) const;
  bool operator>(const String&) const;
  bool operator<=(const String&) const;
  bool operator>=(const String&) const;
  String operator+(const String&) const;
  const String& operator+=(const String&);
  const String& operator=(const String&);
private:
  char* str;
  int length;
};

#ifndef OUTLINE
#include "str.icc"
#endif

#endif
