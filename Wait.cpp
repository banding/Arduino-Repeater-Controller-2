/* Singular event Timer
   A simple NO-Blocking delay
    By B. Anding 11-1-2022
*/

#include <Arduino.h>
#include "Wait.h"


Wait::Wait(int _timerID, unsigned long _duration)
{

  unsigned long delayStart; // the timer started
  bool delayRunning = false; // true if still waiting for delay to finish
  timerLength = _duration;
  cnt = _timerID;
}

void Wait::timerStart()
{
  digitalWrite(10, HIGH); // turn led on
  delayStart = millis();   // start delay
  delayRunning = true; // not finished yet
  timerStop();
}


int Wait::timerStop()
{

  // digitalWrite(10, HIGH); // turn led on
  // check if delay has timed out
  if ((delayRunning) && ((millis() - delayStart) >= timerLength))
  {
    delayRunning = false; // // prevent this code being run more then once
    digitalWrite(10, LOW); // turn led off
    return cnt; // returns the timer identifier number
  }

  else
  {
    return 0;
  }
}

int Wait::timerEnd()
{
  delayRunning = false; // // prevent this code being run more then once
  digitalWrite(10, LOW); // turn led off
  return cnt;
}
