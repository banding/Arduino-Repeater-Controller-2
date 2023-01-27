/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Modified by B. Anding , November 1, 2022
  added tone and CW outputs
  Released into the public domain."AS IS", WITHOUT WARRANTY OF ANY KIND,
*/

#ifndef Morse_h
#define Morse_h
#include "Arduino.h"

class Morse
{
  public:
    Morse(int _pin);
    void dot();
    void dash();
    void Wspace();
    void msg();
    void beep();
    bool msgRunning;

  private:
    int _pin;

};
#endif
