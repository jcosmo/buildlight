Buildlight 
==========
Arduino Uno based build light for Jenkins.

Arduino Uno has:
 - 6 PWM pins - 3,5,6,9,10,11
 - 6 Digital pins - 2,4,7,8,12,13
 - 6 Analog pins
   
   
Intend to support lights:
 - RGB: 3,5,6 + 5V
 - RGB: 9,10,11 + 5V
 - Shiftbrite: 7,8,12,13 + Pwr + Gnd
 - 8 * single colour led: 3xR, 2xG, 3xY: 2,4, A0->A5
   
   
Possible that digital pins 0 & 1 might be usable, but if you can't work with 11 lights then you're stuffed.
  
Specs for lights
  - Common Anode 4 pin Tri Colour
     Red: 2 -> 2.2 V
     Green: 3 -> 3.2 V
     Blue: 3 -> 3.2 V
  
  - Red led: No details, so presuming 2V -> 3.2V
  - Green led: No details, so presuming 2V -> 3.2V
  - Yellow led: No details, so presuming 2V -> 3.2V


Aim to pull about 20mA:  R = (5-Vl)/0.02
  3/0.02 => 150 Ohm
  1.8/0.02 => 90 Ohm
  
If we use 100Ohm, then current will be: I = (5-Vl/R)
  3/100 => 30mA
  1.8/100 => 18mA.
Both within tolerance of the Arduino pins (40mA max)
Concern? of drawing too much from one set of pins, or too much to the ground pin if multiple lights are on.

Experimentation in comparing 100 and 200 ohm resistors showed not enough difference to warrant 100Ohm for yellow and green.
So will go 200 and lower the current.  Red is notably dimmer than the others in all cases so will use a 100Ohm for it to increase brightness.

 
  