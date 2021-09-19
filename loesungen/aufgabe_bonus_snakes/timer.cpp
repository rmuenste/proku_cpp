#include "timer.hpp"

#ifdef _WIN32
extern "C"
{
  void __stdcall Sleep(unsigned long dwMilliseconds);
  int __stdcall QueryPerformanceCounter(long long* ll);
  int __stdcall QueryPerformanceFrequency(long long* ll);
}
#elif defined(__linux) || defined(__unix__)
#  include <sys/time.h>
#  include <unistd.h>
#endif

Timer::Timer() :
  last_time(0)
{
}

void Timer::sync(long long _millis)
{
  // Mikrosekunden
  long long _micros = 1000ll * _millis;

  // check and wait
  if(last_time > 0)
  {
    // verstrichene Zeit seit dem letzten Aufruf
    long long elapsed =  tick() - last_time;

    // muessen wir noch warten?
    if(elapsed < _micros)
    {
      wait(_micros - elapsed);
    }
  }

  // Zeitstempel aktualisieren
  last_time = tick();
}

#ifdef _WIN32
long long Timer::tick()
{
  long long llc(0), llf(0);
  QueryPerformanceCounter(&llc);
  QueryPerformanceFrequency(&llf);
  return (1000000ll * llc) / llf;
}

void Timer::wait(long long _micros)
{
  if(_micros > 0ll)
    Sleep(static_cast<unsigned long>(_micros / 1000ll));
}

#else

long long Timer::tick()
{
  timeval tv;
  gettimeofday(&tv, 0);
  return 1000000ll*(long long)tv.tv_sec + (long long)tv.tv_usec;
}

void Timer::wait(long long _micros)
{
  if(_micros > 0ll)
    usleep((useconds_t)_micros);
}
#endif
