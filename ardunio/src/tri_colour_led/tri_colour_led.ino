/*
  Experiment with a single led capable of producing multiple colours
  Uses 4 pins to control it
  
  Change colour of led by sending appropriate command via USB
  Command takes the form of either
    R|G|B|O   - to turn on Red/Green/Blue/None at full intensity
  or
    Q|W|E|A # - to control the intensity (#) of the Red/Green/Blue/White component of the current colour
*/

#define RED_pin  4
#define YEL_pin  2
#define BLA_pin  5
#define WHI_pin  3
int RED_bright  = 128;
int YEL_bright  = 128;
int BLA_bright  = 128;
int WHI_bright  = 128;

void setup() {
    pinMode(RED_pin, OUTPUT);
    pinMode(YEL_pin, OUTPUT);
    pinMode(BLA_pin, OUTPUT);
    pinMode(WHI_pin, OUTPUT);
    Serial.begin(9600);
    Serial.setTimeout(100);
    update_leds(RED_bright, 
      YEL_bright,
      BLA_bright,
      WHI_bright);
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
    case 'R': red();      break;
    case 'G': green();      break;
    case 'B': blue();      break;
    case 'O': none();      break;

    case  'Q':
      RED_bright = led_value;
      update_leds(RED_bright, YEL_bright, BLA_bright, WHI_bright);
      break;
    case  'W':
      YEL_bright = led_value;
      update_leds(RED_bright, YEL_bright, BLA_bright, WHI_bright);
      break;
    case  'E':
      BLA_bright = led_value;
      update_leds(RED_bright, YEL_bright, BLA_bright, WHI_bright);
      break;
    case  'A':
      WHI_bright = led_value;
      update_leds(RED_bright, YEL_bright, BLA_bright, WHI_bright);
      break;
  }
}

void update_leds(int R, int Y, int B, int W) {
  analogWrite(RED_pin,R);
  analogWrite(YEL_pin,Y);
  analogWrite(BLA_pin,B);
  analogWrite(WHI_pin,W);
}

void red() {  update_leds(0,255,255,255); }
void green() {  update_leds(255,255,255, 0); }
void blue() {  update_leds(255,255,0,255); }
void none() { update_leds(255,255,255,255); }

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
