#include <iostream.h>

void f()
{
  static int a=0;
  cerr << "F";
  cerr << a++;
}

int
main()
{
  for(int i=0;i<10;i++) f();

  int j=20;
  cerr << endl;
  cerr << ++j;
  cerr << j;
  cerr << j++;
  cerr << "NEW" << endl;
  int k=4;

}

