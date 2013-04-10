Buildlight 
==========
Arduino Uno based build light for Jenkins.

Arduino Uno has:
 - 6 PWM pins - 3,5,6,9,10,11
 - 6 Digital pins - 2,4,7,8,12,13
 - 6 Analog pins
   
   
Intend to support lights:
 - RGB: 3,5,6 + Gnd
 - RGB: 9,10,11 + Gnd
 - Shiftbrite: 2,4,7,8 + Pwr + Gnd
 - 8 * single colour led
   
   
Possible that digital pins 0 & 1 might be usable, but if you can't work with 11 light then you're stuffed.
  
