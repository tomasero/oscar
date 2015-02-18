#include <Wtv020sd16p.h>
#include <DistanceGP2Y0A21YK.h>


int resetPin = 2;  // The pin number of the reset pin.
int clockPin = 3;  // The pin number of the clock pin.
int dataPin = 4;  // The pin number of the data pin.
int busyPin = 5;  // The pin number of the busy pin.

Wtv020sd16p wtv020sd16p(resetPin,clockPin,dataPin,busyPin);
 
int blue = 13;
int green = 12;
int yellow = 11;
int red = 10;

int blueId = 3;
int greenId = 2;
int yellowId = 1;
int redId = 0;

//SENSORS//
//Distance
DistanceGP2Y0A21YK Dist;
int infraRed = A0;
int distance;
int maxDistance = 30;

//Motion
int calibrationTime = 30;   
int motionSensor = 9;

int state = 1;
// 0 = default (idle)
// 1 = measure trash level

int trashLevel = 0;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(blue, OUTPUT);     
  pinMode(green, OUTPUT);     
  pinMode(yellow, OUTPUT);     
  pinMode(red, OUTPUT);     
  wtv020sd16p.reset();
  
  Serial.begin(9600);
  Dist.begin(A0);
  pinMode(motionSensor, INPUT);
  digitalWrite(motionSensor, LOW);

  //give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
  for(int i = 0; i < calibrationTime; i++){
    Serial.print(".");
    delay(1000);
  }
  Serial.println(" done");
  Serial.println("SENSOR ACTIVE");
  delay(50);
}

// the loop routine runs over and over again forever:
void loop() {
  // state = 1 if detecting motion.
  state = digitalRead(motionSensor);
  if(state==1) {
    Serial.println("motion detected");
    // The function should return
    // - 0 for full
    // - 1 for almost full
    // - 2 for half
    // - 3 for empty
    trashLevel = getTrashLevel();
    Serial.print("trash level: ");
    Serial.println(trashLevel);

    if(trashLevel<=blueId) {
      digitalWrite(blue, HIGH);
    }
    if(trashLevel<=greenId) {
      digitalWrite(green, HIGH);
    }
    if(trashLevel<=yellowId) {
      digitalWrite(yellow, HIGH);
    }
    if(trashLevel<=redId) {
      digitalWrite(red, HIGH);
      playSound(22000);
    }
    delay(3000);
 
    digitalWrite(blue, LOW);
    digitalWrite(green, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(red, LOW); 
  } 
}

int getTrashLevel() {
  int distance = Dist.getDistanceCentimeter();
  Serial.println(distance);
  distance = map(distance, 0, maxDistance, 0, 3);
  return distance;
}

void playSound(int time) {
  wtv020sd16p.asyncPlayVoice(4);
  delay(time); // This indicates how long the song will play for 
  wtv020sd16p.stopVoice();
  Serial.println("Music done");  
}


