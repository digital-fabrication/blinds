#define tinker 3

#ifdef tinker
#include <Servo.h>

#define LED 2 
#define AUTOMAGIC 3 
#define CLOCKWISE 4 
#define ANTICLOCKWISE 5 
#define SERVO 11

#define LIGHT1 A0
#define LIGHT2 A1

#else
#include <ESP32_Servo.h>

#define LED  27
#define AUTOMAGIC 33
#define CLOCKWISE 15
#define ANTICLOCKWISE 32
#define SERVO 14

#define LIGHT1 A0
#define LIGHT2 A1
#endif

Servo servo;
int servoDegrees = 0;
int oldDegrees = servoDegrees;


void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(AUTOMAGIC, INPUT);
  pinMode(CLOCKWISE, INPUT);
  pinMode(ANTICLOCKWISE, INPUT);
  servo.attach(SERVO);
  
  pinMode(LIGHT1, INPUT);
  pinMode(LIGHT2, INPUT);
  
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
  
  delay(10);  
  
}


int lightSensorValue() {
  int x = analogRead(LIGHT1);
  int y = analogRead(LIGHT2);
  return (x+y)/2;
}

int convertedLightSensorValue() {
  float value = lightSensorValue();
  return value / 1024.0 * 180.0;
}

