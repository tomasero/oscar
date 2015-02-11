#include <Wtv020sd16p.h>


int resetPin = 2;  // The pin number of the reset pin.
int clockPin = 3;  // The pin number of the clock pin.
int dataPin = 4;  // The pin number of the data pin.
int busyPin = 5;  // The pin number of the busy pin.

Wtv020sd16p wtv020sd16p(resetPin,clockPin,dataPin,busyPin);
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int blue = 13;
int green = 12;
int yellow = 11;
int red = 10;

int blue_id = 3;
int green_id = 2;
int yellow_id = 1;
int red_id = 0;

int state = 1;
// 0 = default (idle)
// 1 = measure trash level

boolean motion = false;
int trash_level = 0;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(blue, OUTPUT);     
  pinMode(green, OUTPUT);     
  pinMode(yellow, OUTPUT);     
  pinMode(red, OUTPUT);     
  wtv020sd16p.reset();
}

// the loop routine runs over and over again forever:
void loop() {
  // TODO: set state = 1 if detecting motion.
  state = 1; // later remove this line, added by Sumer to default state to 1 for audio testing
  if(state==1) {
    // Change random() to a call to IR sensor function
    // The function should return
    // - 0 for full
    // - 1 for almost full
    // - 2 for half
    // - 3 for empty
    trash_level = random(0, 4);

    if(trash_level<=blue_id) {
      digitalWrite(blue, HIGH);
    }
    if(trash_level<=green_id) {
      digitalWrite(green, HIGH);
    }
    if(trash_level<=yellow_id) {
      digitalWrite(yellow, HIGH);
    }
    if(trash_level<=red_id) {
      digitalWrite(red, HIGH);
    }
    
    wtv020sd16p.playVoice(0);
    wtv020sd16p.asyncPlayVoice(1);
    delay(40000); // This indicates how long the song will play for 
    wtv020sd16p.pauseVoice();
    delay(2000); 
    wtv020sd16p.asyncPlayVoice(1);
    delay(40000);
    //wtv020sd16p.asyncPlayVoice(2);
    //delay(5000);
    wtv020sd16p.stopVoice();
    
    digitalWrite(blue, LOW);
    digitalWrite(green, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(red, LOW);
    // TODO: set state back to 0 (idle)
  }
  delay(3000);
}

