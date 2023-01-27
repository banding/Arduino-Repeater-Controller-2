/*Interrupt Class PTT & Class Morse Msg
  By B.Anding
  10-30-22
  updated 11-1-22, 11-3-22, 11-12-22
  Copyright (c) <2022> <B.Anding>

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#include "Morse.h"
#include "Wait.h"

Morse morse(13); // creates a Morse code generator

/////////////////////  TIMERS  ////////////////////////////////////////////////////////
/*  Below are the three Timers: Timeout timer (TOT), Morse code Identifier timer (ID) and Squalch tail timer (SQT)
    The first parameter is the timer's ID number the program uses it to keep track of the timers. DO NOT change ID number.
    The second parameter is the Timer's Length in milli seconds, 1000 per second or 60,000 = minute, use it to adjust the timer length
*/
Wait TOT(1, 180000); // Timeout timer = first timer 1, (180000 = 3 minutes)
Wait ID(2, 600000); // Ider time = second timer 2, (600000 = 10 minutes)
Wait SQT(3, 2000); // Squalch tail timer = third timer 3, (2000 = 2 seconds)
/////////////////////////////////////////////////////////////////////////////////////////

const int pinISR = 3; // carrier detected
const int pinCOS = 12; // turn on trx and unsqualch
const int pinCW = 10; // turn on trx for CW Ider
int returnTOT = 0;
int returnID = 0;
bool idRunning = false;

void setup()
{
  pinMode(pinCOS, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(pinCW, OUTPUT);
  pinMode(pinISR, INPUT_PULLUP);
  attachInterrupt(1, isr, CHANGE); // Each Arduino board uses different pins for interrupts,  on Nano-board: 0 = pin 2 ,  1  = pin 3

}

void loop()
{

  returnTOT = TOT.timerStop();
  returnID = ID.timerStop();


  if (returnTOT == 1)
  {
    returnTOT = 0;
    timeOut();
  }

  if (returnID == 2)
  {
    returnID = 0;
    idRunning = false;
    morse.msg(); // morse code message is in Morse.cpp module in the "void Morse::msg()" method, enter your own CW message there
    digitalWrite(10, LOW);
  }
}
// short interrupt functions
void isr()
{
  if (digitalRead(pinISR) == LOW)
  {
    doRising();
  }

  else
  {
    doFalling();
  }
}

// open squalch and turn on PTT

void doRising()
{

  digitalWrite(pinCOS, HIGH); // pin 12
  TOT.timerStart();

  if (idRunning == false)
  {
    idRunning = true;
    ID.timerStart();
  }

}

// close squalch, send a beep and turn off PTT

void doFalling()
{
  
  if (morse.msgRunning == false)
  {
    morse.dash();
    digitalWrite(13, LOW); // pin13
  }

  SQT.timerStart();
  TOT.timerEnd();

}

// Timeout locks repeater: turns off transmitter until carrier drops
void  timeOut()
{
  while (digitalRead(3))
  {
    digitalWrite(pinCOS, LOW);
    digitalWrite(13, LOW);
   
  }
  morse.beep(); // sends twin beeps for Timeout
}
