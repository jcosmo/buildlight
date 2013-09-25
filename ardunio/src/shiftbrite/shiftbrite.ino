/*
  Control a ShiftBrite 
  
  Change colour of led by sending appropriate command via USB
  Command takes the form of either
    R|G|B|O   - to turn on Red/Green/Blue/None at full intensity
  or
    Q|W|E|A # - to control the intensity (#) of the Red/Green/Blue/White component of the current colour
*/

#include "HughesyShiftBrite.h"

#define ORIENTATION 1
#define POWER_pin 2
#define CLOCK_pin  (POWER_pin + ORIENTATION)
#define ENABLE_pin   (CLOCK_pin + ORIENTATION)
#define LATCH_pin   (ENABLE_pin + ORIENTATION)
#define DATA_pin   (LATCH_pin + ORIENTATION)
#define GND_pin  (DATA_pin + ORIENTATION)

#define INTENSITY 1023

HughesyShiftBrite led;
int flash_r;
int flash_g;
int flash_b;
boolean flash;

void setup() {
  pinMode(POWER_pin, OUTPUT);     
  pinMode(GND_pin, OUTPUT);     

  digitalWrite(GND_pin, LOW); 
  digitalWrite(POWER_pin, HIGH); 

  led = HughesyShiftBrite( DATA_pin, LATCH_pin, ENABLE_pin, CLOCK_pin );
  off();
  
  Serial.begin(9600);
  Serial.setTimeout(100);
}

void loop() {
  if ( flash ) {
    delay(500);
    led.sendColour(0,0,0);
    delay(500);    
    led.sendColour(flash_r,flash_g,flash_b);
  }
}

void serialEvent() {  
  char   cmd_str[80];
  int    cmd_length;
  int    led_value;
  cmd_length =   Serial.readBytesUntil('\n', cmd_str, 80);
  cmd_str[cmd_length] = '\0';
  switch(cmd_str[0]) {
    case 'R': red();      break;
    case 'G': green();   break;
    case 'B': blue();     break;
    case 'Y': yellow();  break;
    case 'O': off();      break;
    case 'F': toggle_flash();      break;
  }
}

void update_led(int R, int G, int B) {
  led.sendColour(R, G, B);
  flash_r = R;
  flash_g = G;
  flash_b = B;
}



// Translate a value from rgb (0->255) to shiftbrite (0->1023)
int SCALE = 1023/255;
unsigned int x( unsigned int rgb ) {
  return rgb * SCALE;
}

void red() {  update_led(INTENSITY,0,0); }
void green() {  update_led(0,INTENSITY,0); }
void blue() {  update_led(0,0,INTENSITY); }
void yellow() {  update_led(x(255),x(128),0); }
void off() { flash = false; update_led(0,0,0); }

void toggle_flash() { flash = !flash; }
