#include <ESP32Servo.h>

#define LED           27
#define AUTOMAGIC     33
#define CLOCKWISE     15
#define ANTICLOCKWISE 32
#define SERVO         14

#define PHOTORESISTOR1 A0
#define PHOTORESISTOR2 A1

Servo servo;
int servoDegrees = 90;
int oldDegrees = servoDegrees;


void setup()
{
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(AUTOMAGIC, INPUT);
  pinMode(CLOCKWISE, INPUT);
  pinMode(ANTICLOCKWISE, INPUT);
  servo.attach(SERVO);
  
  pinMode(PHOTORESISTOR1, INPUT);
  pinMode(PHOTORESISTOR2, INPUT);
  
  servo.write(servoDegrees);
  
}

bool automagic=false;

void loop() {
  
  if(digitalRead(AUTOMAGIC) == HIGH ){
    automagic=true;
  }
   
  if(digitalRead(CLOCKWISE) == HIGH ){
    automagic=false;
    servoDegrees += 1;
  }
  
  if(digitalRead(ANTICLOCKWISE) == HIGH ){
    automagic=false;
    servoDegrees -= 1;
  }
  
  if(automagic){
    digitalWrite(LED, HIGH);
    servoDegrees = convertedLightSensorValue();
  } else {
    digitalWrite(LED, LOW);
  }
  
  servoDegrees = 0 < servoDegrees ? servoDegrees : 0;
  servoDegrees = 180 > servoDegrees ? servoDegrees : 180;

  if (oldDegrees != servoDegrees) {
    servo.write(servoDegrees);
    oldDegrees = servoDegrees;
  }
  
  delay(20);

  Serial.print("\n");
  Serial.print(servoDegrees);
}


int lightSensorValue() {
  int x = analogRead(PHOTORESISTOR1);
  int y = analogRead(PHOTORESISTOR2);
  Serial.print("X:");
  Serial.print(x);
  Serial.print("Y:");
  Serial.print(y);
  Serial.print("\n");
  return (x+y)/2;
}

int convertedLightSensorValue() {
  float value = lightSensorValue();
  float result = value / 1024.0 * 180.0;
  Serial.print(result);
  return result;
}
