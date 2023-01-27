/*
  .cpp - Library for flashing  code.
  Created by David A. Mellis, November 2, 2007.
  Modified by B. Anding , November 1, 2022
  Released into the public domain.With no warranty

  At the end of the listing
  there is an alphabet, numbers and space which can be
  used to copy and paste characters for a call sign,
  add a space between each character
  You can use my example (AA5OY) to construct your own call sign
*/
#include "Arduino.h"
#include "Morse.h"
#include "Wait.h"

Morse::Morse(int _pin)
{
  msgRunning = false;
  int pin;
  pin = _pin;
  pinMode(pin, OUTPUT);

}

void Morse::dot()
{
  digitalWrite(12, HIGH); // turn trx on
  tone( A5, 700, 66);
  digitalWrite(12, LOW); // turn trx on
  delay(120);
}

void Morse::dash()
{
  digitalWrite(12, HIGH); // turn trx on
  tone( A5, 700, 170);
  digitalWrite(12, LOW); // turn trx on
  delay(220);
}

void Morse::Wspace()
{
  digitalWrite(12, LOW); // turn trx off
  delay(220);
}

////////////// CW message  ///////////////

void Morse::msg()
{
  // EXAMPLE CALL SIGN "AA5OY"
  msgRunning = true;

  digitalWrite(10, HIGH); // turn trx on

  ////// Call Sign Begins  //////
  dot(); dash(); //'A'
  Wspace();
  dot(); dash(); //'A'
  Wspace();
  dot(); dot(); dot(); dot(); dot(); // '5'
  Wspace();
  dash(); dash(); dash(); // 'O'
  Wspace();
  dash();  dot();  dash(); dash(); // 'Y'
  Wspace();
  /////// Call Sign Ends  //////

  if (digitalRead(12) == true)
  {
    digitalWrite(10, LOW); // turn trx off
  }
  msgRunning = false;
  delay(2000);
}


void Morse::beep()
{
  // Dual Beeps (CW = 'M')
  
  digitalWrite(10, HIGH); // turn trx on
  dash(); Wspace(); dash();  Wspace(); // sends 2 beeps
  digitalWrite(10, LOW); // turn trx off
  delay(2000);
}
////////////  alphabet and numbers  (COPY AND PASTE TO MAKE A CALL SIGN then place in "void Morse::msg()" )  /////////////
/*
    .Wspace();
    .dot(); .dash(); // 'A'
    .Wspace();
    .dash(); .dot();.dot();.dot(); // 'B'
    .Wspace();
    .dash();.dot();.dash();.dot(); //'C'
    .Wspace();
    .dash();.dot();.dot(); // 'D'
    .Wspace();
    .dot();// 'E'
    .Wspace();
    .dot();.dot();.dash();.dot(); //'F'
    .Wspace();
    .dash();.dash();.dot(); // 'G'
    .Wspace();
    .dot();.dot();.dot();.dot(); //'H'
    .Wspace();
    .dot();.dot(); //'I'
    .Wspace();
    .dot();.dash();.dash();.dash(); //'J'
    .Wspace();
    .dash(); .dot(); .dash(); //'K'
    .Wspace();
    .dot();.dash(); .dot();.dot(); // 'L'
    .Wspace();
    .dash();.dash();// 'M'
    .Wspace();
    .dash();.dot(); //'N'
    .Wspace();
    .dash();.dash();.dash(); // 'O'
    .Wspace();
    .dot();.dash();.dash();.dot(); //'P'
    .Wspace();
    .dash();.dash();.dot();.dash(); // 'Q'
    .Wspace();
    .dot();.dash();.dot(); // 'R'
    .Wspace();
    .dot();.dot(); .dot(); // 'S'
    .Wspace();
    .dash(); // 'T'
    .Wspace();
    .dot();.dot();.dash();// 'U'
    .Wspace();
    .dot();.dot();.dot();.dot(); // 'V'
    .Wspace();
    .dot(); .dash(); .dash(); // 'W'
    .Wspace();
    .dash(); .dot(); .dot(); .dash(); // 'X'
    .Wspace();
    .dash();.dot();.dash();.dash(); // 'Y'
    .Wspace();
    .dash();.dash();.dot();.dot(); // 'Z'
    .Wspace();
    .dot();.dot();.dot();.dot(); .dot(); // '1'
    .Wspace();
    .dot();.dot();.dash();.dash();.dash(); // '2'
    .Wspace();
    .dot();.dot();.dot();.dash();.dash(); // '3'
    .Wspace();
    .dot();.dot();.dot();.dot(); .dash(); // '4'
    .Wspace();
    .dot(); .dot();.dot();.dot();.dot(); // '5'
    .Wspace();
    .dash(); .dot();.dot();.dot();.dot(); // '6'
    .Wspace();
    .dash();.dash();.dot();.dot();.dot(); // '7'
    .Wspace();
    .dash();.dash();.dash();.dot();.dot(); // '8'
    .Wspace();
    .dash();.dash();.dash();.dash();.dot(); // '9'
    .Wspace();
    .dash();.dash();.dash();.dash();.dash(); // '0'
    .Wspace();
    .dash();.dot();.dot().dash();.dot(); // '/'
*/
