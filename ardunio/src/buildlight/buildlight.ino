/*
  Buildlight controller.

  Buildlight has RGB1, RGB2, Shiftbrite, 2xR + 3xG + 3xY led

  Commands:
      [light] ON/OFF/FLASH [Colour]?

  [light]: RGB0, RGB1, SB0, R0, R1, G0, G1, G2, Y0, Y1, Y2
  [colour]: R,G,B optional, only used on RGB0, RGB1, SB0
*/

bool flash_RGB[] = {false,false};
bool flash_SB[] = {false};
bool led_flash[] = {false,false,false,false,false,false,false,false};

typedef struct Colour { unsigned int R; unsigned int G; unsigned int B; };
Colour white = {255,255,255};

Colour colour_RGB[] = {white, white};
Colour colour_SB[] = {white};

bool on_RGB[] = {false, false};
bool on_SB[] = {false};
bool led_on[] = {false,false,false,false,false,false,false,false};

unsigned int led_pins[] = {2,4,A0,A1,A2,A3,A4,A5};
int RED_OFFSET = 0;
int GRN_OFFSET = RED_OFFSET + 3;
int YEL_OFFSET = GRN_OFFSET + 2;

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

void setup()
{
  for( unsigned int i = 0; i < sizeof(led_pins); i++)
  {
    pinMode(led_pins[i], OUTPUT);
    digitalWrite(led_pins[i], LOW);
  }
/*
  Serial.begin(9600);
  Serial.setTimeout(100);
*/


  /* Debugging */
  toggle_led_flash( RED_OFFSET + 0 );
  toggle_led_flash( RED_OFFSET + 1 );
  toggle_led_flash( RED_OFFSET + 2 );
  toggle_led_flash( GRN_OFFSET + 0 );
  toggle_led_flash( GRN_OFFSET + 1 );
  toggle_led_flash( YEL_OFFSET + 0 );
  toggle_led_flash( YEL_OFFSET + 1 );
  toggle_led_flash( YEL_OFFSET + 2 );

  set_led_on( RED_OFFSET + 1 );
  set_led_on( GRN_OFFSET + 1 );
  set_led_on( YEL_OFFSET + 1 );
}

void loop()
{
  for( unsigned int i = 0; i < sizeof(led_flash); i++)
    if ( led_flash[i] )
      toggle_led_state( i );

  delay(500);
}

