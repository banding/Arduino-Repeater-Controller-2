# Repeater-Controller-2
Arduino Repeater Controller version 2
       
A few basic functions for a Repeater Controller: 

    1. Needs to monitor the receiver for a carrier. If a carrier is detected open the squelch and connect the  
    receiver’s audio to the transmitter’s input and lastly turn on the transmitter.
    
    2. At the end it needs to close the squelch, perhaps add a short squelch tail and turn off the transmitter.
    
    3. There's a need to Identify the repeater usually with a CW message. A CW Identifier can be added 
    with either internal or external module.  
       

All for this can be done with a few logic gates and transistors. On Today's  low cost microcontroller  boards these resources are included. Arduino UNO or Nano boards only needs a sketch to run their hardware. I chose to include the CW identifier in the Repeater Controller thereby eliminating the need for a external module.

A Repeater Controller scenario: 
At initial contact Repeater Controller, (RC)  needs to start a time out timer and the Identifier (IDer) timer. The two timers will run independently. The (RC) monitors the receiver for carrier lose. If the incoming  carrier drops it closes the squelch and next starts the Squelch tail timer. Which sends a beep and turns off the transmitter when the Squelch tail timer expires. 

If the conversation on the repeater runs past the Timeout timers length. The (RC) turns off the transmitter and locks out the repeater until  the receiver detects a carrier drop. At which time the RC resets, sends a dual beep (CW = ‘M’ ) and returns to normal operations.

This is a simple Arduino Repeater Controller version 2. My first version the code got very busy and thought it was time to make the code easier to read. With this in mind I decided to use the Object Originated Programming  (OOP) approach and rewrote the sketch. 

The (RC) sketch consists of three modules main sketch, Wait and Morse. All these need to be placed in the same directory. The main sketch keeps track of the repeaters receiver through an interrupt service routine. It also controls the transmitter, squelch and sends CW to transmitter to accomplish all this the main sketch make calls to the timers and the morse code generator. 

The wait module is a basic one shot timer. At the end of the timer cycle it returns a value to main sketch. The main sketch uses the return value to preforms appropriate actions. The millis() function uses the Arduino clock which should be fairly accurate, but be sure to test for proper results. By using the non-blocking millis() function the Arduino is allowed to multi task. Currently the ID timer is set for 10 minutes, the TOT is set for 3 minutes and the SQT timer is set for 2 seconds. The millis() function counts in milliseconds. Therefore millis(1000 ) = one second and millis(60000) = one minute. Looking at top of the main sketch where the timers are initialized, we see the following comments. 

Below are the three Timers: Timeout timer (TOT), Morse code Identifier timer (ID) and Squelch tail timer (SQT). The first parameter is the timer's ID number the program uses it to keep track of the timers. DO NOT change ID number.
The second parameter is the Timer's Length in milliseconds, 1000 per second or 60,000 = minute, use it to adjust the timer length

Wait TOT(1, 180000); // Timeout timer = first timer 1, (180000 = 3 minutes)
Wait ID(2, 600000); // Ider time = second timer 2, (600000 = 10 minutes)
Wait SQT(3, 2000); // Squelch tail timer = third timer 3, (2000 = 2 seconds)

Here’s the instantiation of the Wait class from which is creates three objects: TOT(1, 180000), ID(2, 600000) and SQT(3, 2000) each timer is independent of each other. Each timer uses the first parameter when it returns to main sketch for additional processing. Don’t change the first number. The second parameter is the timer length in milliseconds and can be change as needed.

The morse code class is described at Arduino site in “Writing a Library for Arduino”
Docs webpage.  https://docs.arduino.cc/learn/contributions/arduino-creating-library-guide

  Morse module is a basic CW Identifier. 
  Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Modified by B. Anding , November 1, 2022
  added tone, CW outputs and transmitter control.

At the end of the ID timer cycle it returns a value to main sketch. The main sketch uses the return value to call Morse.msg() method. Morse.msg() turns on transmitter and plays the CW message and then turns off the transmitter. 
Morse.msg() contains a call sign (AA5OY). Please use the Alpha-numeric list at the end of Morse.cpp file to copy and past your call sign in between 

////// Call Sign Begins  //////
                
                
/////// Call Sign Ends  //////

For best results add a Wspace(); in between each letter/number following the example message.
Below is the listing of CW message method, void Morse::msg()

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

The Morse class also has a Beep() method which the RC uses for signaling at the end of a time out. 

Beside the conventional repeater and duplexer combo.  Using Arduino controller and two handhelds could be a simple way to active area temporarily or in an emergency. The two handhelds would be to be separated either by bands or distance (vertical or horizontal). Doing so would prevent the transmitter from  desensitizing the receiver.
