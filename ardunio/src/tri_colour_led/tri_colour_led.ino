/*
  Experiment with a single led capable of producing multiple colours
  Uses 3 pins to control it, and a +5.  
  
  Change colour of led by sending appropriate command via USB
  Command takes the form of either
    R|G|B|O   - to turn on Red/Green/Blue/None at full intensity
  or
    Q|W|E # - to control the intensity (#) of the Red/Green/Blue component of the current colour
    
  NOTE: for the intensity to work you have to connect the R/G/B to pins capable of PWM.  On 
  the Nano and Uno these are 3,5,6,9,10,11.  If you connect to anything else then this colour will be
  either on or off.  On being <128, Off being >127.
  
  RGB led I'm using has a common Anode, thus tied to +5, and thus intensities go from 255=off to 0=full.
  Pins on it are R/A/G/B, with A being the long pin.
*/


#define RED_pin  11
#define GREEN_pin  3
#define BLUE_pin  5
int RED_bright = 100;
int BLUE_bright = 100;
int GREEN_bright = 100;

void setup() {
    pinMode(RED_pin, OUTPUT);
    pinMode(BLUE_pin, OUTPUT);
    pinMode(GREEN_pin, OUTPUT);
    Serial.begin(9600);
    Serial.setTimeout(100);
    update_leds();
}

void loop() {
  delay(100); // milliseconds
}

void serialEvent() {  
  char   cmd_str[80];
  int    cmd_length;
  int    led_value;
  cmd_length =   Serial.readBytesUntil('\n', cmd_str, 80);
  cmd_str[cmd_length] = '\0';
  led_value = get_value(cmd_str);
  
  switch(cmd_str[0]) {
    case 'R': case 'r': red();      break;
    case 'G': case 'g': green();    break;
    case 'B': case 'b': blue();     break;
    case 'O': case 'o': off();      break;
    case 'Q': case 'q': RED_bright = led_value;   break;
    case 'W': case 'w': GREEN_bright = led_value; break;
    case 'E': case 'e': BLUE_bright = led_value;  break;
  }
  update_leds();
}

void update_leds() {
  analogWrite(RED_pin,RED_bright);
  analogWrite(BLUE_pin,BLUE_bright);
  analogWrite(GREEN_pin,GREEN_bright);
}

void set_all( int R, int B, int G ) {
  RED_bright = R;
  BLUE_bright = B;
  GREEN_bright = G;
}

void red() {  set_all(0,255,255); }
void green() {  set_all(255,255,0); }
void blue() {  set_all(255,0,255); }
void off() { set_all(255,255,255); }

int get_value(char *s) {
  int value=0;
  while ( ( *s < '0' || *s > '9' ) && *s != '\0' ) {
    s++;
  }
  while(*s) {
    if ( *s >= '0' && *s <= '9' ) {
      value = value * 10;
      value = value + int( *s - '0' );
    } else {
      break;
    }
    s++;  
  }
  return value;
}
