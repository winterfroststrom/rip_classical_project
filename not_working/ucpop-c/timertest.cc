#include "timer.h"

Timer timer;

int
main()
{
  timer.StartRecording();
  system("ucpop monkey-test3 domains/monkey.u");
  timer.EndRecording();

  timer.PrintStatistics(cerr);
}
