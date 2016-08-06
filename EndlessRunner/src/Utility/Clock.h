#ifndef CLOCK_H
#define CLOCK_H

#include <chrono>
#include <ratio>

namespace fhl
{

using Seconds = std::chrono::duration<float>;
using Milliseconds = std::chrono::duration<float, std::milli>;
using Microseconds = std::chrono::duration<float, std::micro>;

class Clock
{
   using TimePoint = std::chrono::time_point<std::chrono::system_clock>;
   using SystemClock = std::chrono::system_clock;

public:
   Clock();

   template<typename T = Seconds>
      float getElapsedTime();
   template<typename T = Seconds>
      float restart();
private:
   TimePoint m_start;
};

} // ns

#endif // CLOCK_H
