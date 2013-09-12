#ifndef TIMER_H
#define TIMER_H

#include <sys/times.h>
#include <iostream.h>
// timer class for calculating process times

class Timer {
public:
  Timer();
  void       StartRecording();
  void       EndRecording();
  void       Reset();
  float      GetElapsed();
  float      GetCPUTime();
  void       PrintStatistics(ostream& os);
  
private:
  static const int precision; // precision of printing time
  static long      clktck;
  struct tms       startTime;
  struct tms       endTime;
  clock_t          startRTime;
  clock_t          endRTime;
};


#ifndef OUTLINE
#include "timer.icc"
#endif

#endif
