/*By B.Anding , 11-1-2022
   Released into the public domain."AS IS", WITHOUT WARRANTY OF ANY KIND,
*/

#ifndef Wait_h
#define Wait_h
#include <Arduino.h>


class Wait {

    //Class members init at startup
  public:
    Wait(int _timerID, unsigned long _duration);
    int cnt;
    void timerStart();
    int timerStop();
    int timerEnd();
    unsigned long timerLength;
    bool delayRunning = false; // true if still waiting for delay to finish

  private:
    int _timerID;
    unsigned long _duration;
    unsigned long delayStart; // the time the delay started


};

#endif
