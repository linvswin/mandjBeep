#ifndef _MJClock_H_
#define _MJClock_H_

#include <RtcDS3231.h>

#include "pin.h"

class Clock {
public:
  RtcDS3231 RTC;
  RtcDateTime now;

  void inizializza();
  String getDate();
  String printDigit(int digits);
};
 
#endif