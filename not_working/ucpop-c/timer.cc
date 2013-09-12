#include "timer.h"

#ifdef OUTLINE
#define inline
#include "timer.icc"
#undef inline
#endif

long Timer::clktck=sysconf(_SC_CLK_TCK);
const int Timer::precision=3;

Timer::Timer()
{
  if ((clktck=sysconf(_SC_CLK_TCK)) ==0)
     cerr << ("SysConf Error.");
}

