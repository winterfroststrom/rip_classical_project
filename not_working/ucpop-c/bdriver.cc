#include "bitstring.h"
#include <iostream.h>

main()
{
  BitString b( 100,OFF );
  unsigned int d;
  int e = 1;
  BitString c( 100,OFF );
  b += 99;
   cerr << b << "\n";
   b += 0;
   cerr << b << "\n";
   b -= 99;
   cerr << b << "\n";
   b += 50;
   cerr << b << "\n";
   c += 25;
   cerr << b << "\n";
   cerr << c << "\n";
   c = c & b;
   cerr << "and and or: " << c << "\n";
   c |= b;
   cerr << "and and or: " << c << "\n";
   c = c | b;
 cerr << "and and or: " << c << "\n";
  c &= b;
  d = 0;
  cerr << c;
//  delete &b;
//  delete &c;
  if (c.Empty()) cerr << "HAHA!\n";
  BitString* big=new BitString[4000];
  for (int i=0; i<3000; i++) {
    big[i]=b;
  }
  if (!b.Empty()) cerr << "great\n";
//  if ((b & c).Empty()) cerr << "what?\n"; 
//  if ((b | c).Empty()) cerr << "wrong!\n"; 
  delete &b;
  delete &c;

  BitString a(3,OFF);
  BitString f(4,ON);
  cerr << "Final\n";  
  BitString g(4);
  g |= a|f;
  cerr << "Size:" << g.size << "\n";
  if ((a|f).Empty()) cerr << "inCorrect";
  

  BitString t(2000,ON);
  BitString u(100, OFF);
  BitString v(100);
  v|= t|u;
  BitString vs;			 //(t|u);
  vs= t|u;
  BitString f1;
  cerr << "hello.";
//  cerr << v << "\nSize:" << v.size;
  // seems (t|u) is illegal
//  if (v.Empty()) cerr << "incorrect1\n";
//  if (IsEmpty(v)) cerr << "incorrect2\n";
  if (IsEmpty(t|t)) cerr << "incorrect3" << " " << (t|t).size << "\n";
//  if ((t|t).bs) cerr << "something\n";
  // this doesn\'t work:::
  //  if ((t|u).Empty) cerr << "incorrect4\n";
//  if (vs.Empty()) cerr << "incorrect5\n";
//  if (IsEmpty(vs)) cerr << "incorrect6\n";
//  if (IsEmpty(f1)) cerr << "ok\n";
//  if (IsEmpty(f1|f1)) cerr << "ok2\n";

  return (0);
}
