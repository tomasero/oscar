#include <DistanceGP2Y0A21YK.h>

DistanceGP2Y0A21YK Dist;
int distance;
int red = 4;
int yellow = 3;
int green = 2;

void setup()
{
  Serial.begin(9600);
  Dist.begin(A0);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
}

void loop()
{
  distance = Dist.getDistanceCentimeter();
//  Serial.print("\nDistance in centimeters: ");
  Serial.println(distance);
  turnOffAllLeds();
  if (distance >= 60) {
    digitalWrite(green, HIGH);
  } else if (distance >= 30 && distance < 60) {
    digitalWrite(yellow, HIGH);
  } else {
    digitalWrite(red, HIGH);
  }
  delay(500);                                     //make it readable
}

void turnOffAllLeds()
{
  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);   
}
