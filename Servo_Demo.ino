#include <Servo.h>

Servo myservo1;
Servo myservo2;
bool running = true;


void setup() {
  // put your setup code here, to run once:
  myservo1.attach(8);
  myservo2.attach(10);
} 

void loop() {
  // put your main code here, to run repeatedly:
  if(running){
    myservo1.writeMicroseconds(994);
    myservo2.writeMicroseconds(2014);
    delay(3000);
    myservo1.writeMicroseconds(1494);
    myservo2.writeMicroseconds(1494);
    delay(1000);
    myservo1.writeMicroseconds(2014);
    myservo2.writeMicroseconds(994);
    delay(3000);
    myservo1.writeMicroseconds(1494);
    myservo2.writeMicroseconds(1494);
    delay(1000);
    myservo1.writeMicroseconds(994);
    myservo2.writeMicroseconds(994);
    delay(3000);
    myservo1.writeMicroseconds(1494);
    myservo2.writeMicroseconds(1494);
    running = false;
  }}
