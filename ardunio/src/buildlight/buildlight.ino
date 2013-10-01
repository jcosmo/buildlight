/*
  Buildlight controller.

  Buildlight has RGB1, RGB2, Shiftbrite, 2xR + 3xG + 3xY led

  Commands:
      [light] ON/OFF/FLASH [Colour]?

  [light]: T0, T1, S0, R0, R1, G0, G1, G2, Y0, Y1, Y2  (T => TriColour, S => ShiftBrite)
  [colour]: R,G,B optional, only used on RGB0, RGB1, SB0
*/

#include "HughesyShiftBrite.h"

//#define DEBUG

typedef struct colour { unsigned int r; unsigned int g; unsigned int b; } Colour;
typedef struct { Colour colour; unsigned int pins[3]; bool on; bool flash; } RGBLed;
typedef struct { Colour colour;
                 unsigned int enable; unsigned int latch; unsigned int data; unsigned int clock;
                 bool on; bool flash; HughesyShiftBrite hsb; } ShiftBrite;

RGBLed rgb_leds[2];
ShiftBrite shiftBrite[1];

unsigned int led_pins[] = {2,4,A0,A1,A2,A3,A4,A5};
bool led_on[8];
bool led_flash[8];
int RED_OFFSET = 0;
int GRN_OFFSET = RED_OFFSET + 3;
int YEL_OFFSET = GRN_OFFSET + 2;
int flash_speed = 250;

// RGB led colours for convienence
Colour RED = {0,255,255};
Colour GREEN = {255,0,255};
Colour BLUE = {255,255,0};
Colour YELLOW = {0,0,255};
Colour PURPLE = {0,255,0};
Colour CYAN = {255,0,0};
Colour WHITE = {0,0,0};
Colour SB_BLACK = {0,0,0};

void update_led( unsigned int idx )
{
  digitalWrite( led_pins[idx], led_on[idx] ? HIGH : LOW );
}

void set_led_flash( unsigned int idx )
{
  led_flash[idx] = true;
}

void toggle_led_state( unsigned int idx )
{
  led_on[idx] = !led_on[idx];
  update_led( idx );
}

void set_led_on( unsigned int idx )
{
  led_flash[idx] = false;
  if ( !led_on[idx] )
  {
    led_on[idx] = true;
    update_led(idx);
  }
}

void set_led_off( unsigned int idx )
{
  led_flash[idx] = false;
  if ( led_on[idx] )
  {
    led_on[idx] = false;
    update_led(idx);
  }
}

void update_rgb( unsigned int idx )
{
  if ( rgb_leds[idx].on )
  {
    analogWrite(rgb_leds[idx].pins[0],rgb_leds[idx].colour.r);
    analogWrite(rgb_leds[idx].pins[1],rgb_leds[idx].colour.g);
    analogWrite(rgb_leds[idx].pins[2],rgb_leds[idx].colour.b);
  }
  else
  {
    analogWrite(rgb_leds[idx].pins[0],255);
    analogWrite(rgb_leds[idx].pins[1],255);
    analogWrite(rgb_leds[idx].pins[2],255);
  }
}

void set_rgb_colour_rgb( unsigned int idx, unsigned int r, unsigned int g, unsigned int b )
{
  rgb_leds[idx].colour.r = r;
  rgb_leds[idx].colour.g = g;
  rgb_leds[idx].colour.b = b;
  update_rgb(idx);
}

void set_rgb_colour( unsigned int idx, struct colour c )
{
  rgb_leds[idx].colour.r = c.r;
  rgb_leds[idx].colour.g = c.g;
  rgb_leds[idx].colour.b = c.b;
  update_rgb(idx);
}

void set_rgb_on( unsigned int idx )
{
  rgb_leds[idx].on = true;
  update_rgb(idx);
}

void set_rgb_off( unsigned int idx )
{
  rgb_leds[idx].on = false;
  update_rgb(idx);
}

void set_rgb_flash( unsigned int idx )
{
  rgb_leds[idx].flash = true;
}

void toggle_rgb_state( unsigned int idx )
{
  rgb_leds[idx].on = !rgb_leds[idx].on;
  update_rgb( idx );
}

void update_shiftBrite( unsigned int idx )
{
  if ( shiftBrite[idx].on )
    shiftBrite[idx].hsb.sendColour(shiftBrite[idx].colour.r,shiftBrite[idx].colour.g,shiftBrite[idx].colour.b);
  else
    shiftBrite[idx].hsb.sendColour(SB_BLACK.r, SB_BLACK.g, SB_BLACK.b);
}

float SB_RGB_SCALE = 1023/255;
void set_shiftBrite_colour( unsigned int idx, struct colour c )
{
  shiftBrite[idx].colour.r = (int)((255-c.r) * SB_RGB_SCALE);
  shiftBrite[idx].colour.g = (int)((255-c.g) * SB_RGB_SCALE);
  shiftBrite[idx].colour.b = (int)((255-c.b) * SB_RGB_SCALE);
  update_shiftBrite(idx);
}

void set_shiftBrite_flash( unsigned int idx )
{
  shiftBrite[idx].flash = true;
}

void toggle_shiftBrite_state( unsigned int idx )
{
  shiftBrite[idx].on = !shiftBrite[idx].on;
  update_shiftBrite(idx);
}

void set_shiftBrite_on( unsigned int idx )
{
  shiftBrite[idx].flash = false;
  if ( !shiftBrite[idx].on )
  {
    shiftBrite[idx].on = true;
    update_shiftBrite(idx);
  }
}

void set_shiftBrite_off( unsigned int idx )
{
  shiftBrite[idx].flash = false;
  if ( shiftBrite[idx].on )
  {
    shiftBrite[idx].on = false;
    update_shiftBrite(idx);
  }
}

#ifdef DEBUG
void debug_pattern()
{
  /* Debugging */
  set_led_on( RED_OFFSET + 0 );
  toggle_led_flash( RED_OFFSET + 0 );
  toggle_led_flash( RED_OFFSET + 1 );
  toggle_led_flash( RED_OFFSET + 2 );
  set_led_on( GRN_OFFSET + 0 );
  toggle_led_flash( GRN_OFFSET + 0 );
  toggle_led_flash( GRN_OFFSET + 1 );
  toggle_led_flash( YEL_OFFSET + 0 );
  set_led_on( YEL_OFFSET + 1 );
  toggle_led_flash( YEL_OFFSET + 1 );
  toggle_led_flash( YEL_OFFSET + 2 );

  set_led_on( RED_OFFSET + 1 );
  set_led_on( GRN_OFFSET + 1 );

  set_rgb_colour(0, WHITE );
  set_rgb_colour(1, PURPLE );
  set_rgb_on(1);
  toggle_rgb_flash(0);

  set_shiftBrite_colour(0, GREEN);
  toggle_shiftBrite_flash(0);
}
#endif

void setup()
{
  rgb_leds[0] = (RGBLed){{255,255,255}, {6,3,5}, false, false};
  rgb_leds[1] = (RGBLed){{255,255,255}, {11,9,10}, false, false};
  shiftBrite[0] = (ShiftBrite){SB_BLACK, 7,8,12,13, false, false};

  for( unsigned int i = 0; i < sizeof(led_pins)/sizeof(led_pins[0]); i++)
  {
    led_on[i] = false;
    led_flash[i] = false;
    pinMode(led_pins[i], OUTPUT);
    update_led(i);
  }

  for( unsigned int i = 0; i < sizeof(rgb_leds)/sizeof(rgb_leds[0]); i++)
  {
    pinMode(rgb_leds[i].pins[0], OUTPUT);
    pinMode(rgb_leds[i].pins[1], OUTPUT);
    pinMode(rgb_leds[i].pins[2], OUTPUT);
    update_rgb(i);
  }

  for( unsigned int i = 0; i < sizeof(shiftBrite)/sizeof(shiftBrite[0]); i++)
  {
    pinMode(shiftBrite[i].enable, OUTPUT);
    pinMode(shiftBrite[i].clock, OUTPUT);
    pinMode(shiftBrite[i].data, OUTPUT);
    pinMode(shiftBrite[i].latch, OUTPUT);
    shiftBrite[i].hsb = HughesyShiftBrite( shiftBrite[i].data, shiftBrite[i].latch, shiftBrite[i].enable, shiftBrite[i].clock );
    update_shiftBrite(i);
  }  
  
  Serial.begin(9600);
  Serial.setTimeout(100);

#ifdef DEBUG
  debug_pattern();
#endif
}

void loop()
{
  for( unsigned int i = 0; i < sizeof(led_pins)/sizeof(led_pins[0]); i++)
    if ( led_flash[i] )
      toggle_led_state( i );

  for( unsigned int i = 0; i < sizeof(rgb_leds)/sizeof(rgb_leds[0]); i++)
    if ( rgb_leds[i].flash )
      toggle_rgb_state( i );

  for( unsigned int i = 0; i < sizeof(shiftBrite)/sizeof(shiftBrite[0]); i++)
    if ( shiftBrite[i].flash )
      toggle_shiftBrite_state( i );

  delay(flash_speed);
}

void led_cmd( unsigned int offset, char *cmd )
{
  int idx;
  char op[80];
  if ( 2 == sscanf(cmd + sizeof(char), "%d %s", &idx, op))
  {
    if ( idx + offset >= sizeof(led_pins)/sizeof(led_pins[0]))
    {
      Serial.println(String("Invalid led pin index: [") + idx + "]");
      return;
    }
    if ( String("ON").equalsIgnoreCase(op) )
      set_led_on( idx + offset );
    else if ( String("OFF").equalsIgnoreCase(op) )
      set_led_off( idx + offset );
    else if ( String("FLASH").equalsIgnoreCase(op) )
      set_led_flash( idx + offset );
    else
      Serial.println(String("Invalid led pin command: [") + op + "]");
  }
  else
    Serial.println(String("Invalid LED command structure: ") + cmd);
}

void serialEvent() {
  char   cmd_str[80];
  int    cmd_length;
  int    led_value;
  cmd_length =   Serial.readBytesUntil('\n', cmd_str, 80);
  cmd_str[cmd_length] = '\0';

  /*
    Commands:
        [light] ON/OFF/FLASH [Colour]?

    [light]: T0, T1, S0, R0, R1, G0, G1, G2, Y0, Y1, Y2  (T => TriColour, S => ShiftBrite)
    [colour]: R,G,B optional, only used on RGB0, RGB1, SB0
  */
  if ( 'R' == cmd_str[0] || 'r' == cmd_str[0] )
    led_cmd( RED_OFFSET, cmd_str );
  else if ( 'G' == cmd_str[0] || 'g' == cmd_str[0])
    led_cmd( GRN_OFFSET, cmd_str );
  else if ( 'Y' == cmd_str[0] || 'y' == cmd_str[0])
    led_cmd( YEL_OFFSET, cmd_str );
  else
    Serial.println(String("Unrecognised command: ") + cmd_str);
}

