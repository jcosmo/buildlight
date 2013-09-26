/*
  Buildlight controller.

  Buildlight has RGB1, RGB2, Shiftbrite, 2xR + 3xG + 3xY led

  Commands:
      [light] ON/OFF/FLASH [Colour]?

  [light]: RGB0, RGB1, SB0, R0, R1, G0, G1, G2, Y0, Y1, Y2
  [colour]: R,G,B optional, only used on RGB0, RGB1, SB0
*/

#define DEBUG

typedef struct colour { unsigned int r; unsigned int g; unsigned int b; } Colour;
typedef struct { Colour colour; unsigned int pins[3]; bool on; bool flash; } RGBLed;


RGBLed rgb_leds[2];

unsigned int led_pins[] = {2,4,A0,A1,A2,A3,A4,A5};
bool led_on[8];
bool led_flash[8];
int RED_OFFSET = 0;
int GRN_OFFSET = RED_OFFSET + 3;
int YEL_OFFSET = GRN_OFFSET + 2;

// RGB led colours for convienence
Colour RED = {0,255,255};
Colour GREEN = {255,0,255};
Colour BLUE = {255,255,0};
Colour YELLOW = {0,0,255};
Colour PURPLE = {0,255,0};
Colour CYAN = {255,0,0};
Colour WHITE = {0,0,0};

void update_led( unsigned int idx )
{
  digitalWrite( led_pins[idx], led_on[idx] ? HIGH : LOW );
}

void toggle_led_flash( unsigned int idx )
{
  led_flash[idx] = !led_flash[idx];
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

void toggle_rgb_flash( unsigned int idx )
{
  rgb_leds[idx].flash = !rgb_leds[idx].flash;
}

void toggle_rgb_state( unsigned int idx )
{
  rgb_leds[idx].on = !rgb_leds[idx].on;
  update_rgb( idx );
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
}
#endif

void setup()
{
  rgb_leds[0] = (RGBLed){{255,255,255}, {6,3,5}, false, false};
  rgb_leds[1] = (RGBLed){{255,255,255}, {11,9,10}, false, false};

  for( unsigned int i = 0; i < sizeof(led_pins)/sizeof(led_pins[0]); i++)
  {
    led_on[i] = false;
    led_flash[i] = false;
    pinMode(led_pins[i], OUTPUT);
    digitalWrite(led_pins[i], LOW);
  }

  for( unsigned int i = 0; i < sizeof(rgb_leds)/sizeof(rgb_leds[0]); i++)
  {
    pinMode(rgb_leds[i].pins[0], OUTPUT);
    pinMode(rgb_leds[i].pins[1], OUTPUT);
    pinMode(rgb_leds[i].pins[2], OUTPUT);
    analogWrite(rgb_leds[i].pins[0], 255);
    analogWrite(rgb_leds[i].pins[1], 255);
    analogWrite(rgb_leds[i].pins[2], 255);
  }

/*
  Serial.begin(9600);
  Serial.setTimeout(100);
*/

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

  delay(500);
}

