/*
  Experiment with 3 pins, each controlling a different colour led
*/
 
int led = 0;
int offset = 2;
int duration_on = 1000;
int duration_off = 100;

void setup() {                
  pinMode(led + offset, OUTPUT);     
  pinMode(led + offset + 1, OUTPUT);     
  pinMode(led + offset + 2, OUTPUT);     
}

void loop() {
  digitalWrite(led+offset, HIGH);   // current led on
  delay(duration_on);               
  digitalWrite(led+offset, LOW);    // current led off
  delay(duration_off);
  led = (led+1)%3;                  // next led
}
