#include <Servo.h>

Servo myservo1;
Servo myservo2;
bool running = true;
boolean newData = false;
char receivedChar;


void setup() {
 
  Serial.begin(9600);
  Serial.println("<Arduino is ready>");
 
  myservo1.attach(8);
  myservo2.attach(10);
} 

void recvOneChar() {
 if (Serial.available() > 0) {
 receivedChar = Serial.read();
 newData = true;
 }
}

void showNewData() {
 if (newData == true) {
 Serial.println(receivedChar);
 newData = false;
 }
}

void loop() {
  // put your main code here, to run repeatedly:
  recvOneChar();
  showNewData();

  if(receivedChar == 'w'){ //move forward
    Serial.print("Forwards");
    myservo1.writeMicroseconds(994); 
    myservo2.writeMicroseconds(2014);
    delay(3000);
    
    myservo1.writeMicroseconds(1494); //stop
    myservo2.writeMicroseconds(1494);
    delay(1000);
  }

  else if(receivedChar == 's') { //move backwards
    Serial.print("Backwards");
    myservo1.writeMicroseconds(2014);
    myservo2.writeMicroseconds(994);
    delay(3000);
    
    myservo1.writeMicroseconds(1494); //stop
    myservo2.writeMicroseconds(1494);
    delay(1000);
  }

  else if(receivedChar == 'a') {
    Serial.print("LEFT");
    myservo1.writeMicroseconds(994); //opposite turn, left or right?
    myservo2.writeMicroseconds(994);
    delay(3000);
    
    myservo1.writeMicroseconds(1494); //stop
    myservo2.writeMicroseconds(1494);
  }

  else if(receivedChar == 'd') {
    Serial.print("RIGHT");
    myservo1.writeMicroseconds(2014); //opposite turn as above, right or left?
    myservo2.writeMicroseconds(2014);

    myservo1.writeMicroseconds(1494); //stop
    myservo2.writeMicroseconds(1494);
  }

  else if(receivedChar == 'c') {
    Serial.print("Color Sensor On");
  }
  }
