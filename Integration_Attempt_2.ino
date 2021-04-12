#include <Servo.h>
int s0=3,s1=4,s2=5,s3=6;
int out=2;
int flag=0;
byte counter=0;
byte countR=0,countG=0,countB=0;

Servo myservo1;
Servo myservo2;
bool running = true;
boolean newData = false;
char receivedChar;

void setup() {
 
  Serial.begin(9600);
  Serial.println("<Arduino is ready>");
  pinMode(s0,OUTPUT);
  pinMode(s1,OUTPUT);
  pinMode(s2,OUTPUT);
  pinMode(s3,OUTPUT);
  pinMode(7,OUTPUT);
  myservo1.attach(8);
  myservo2.attach(10);
} 

void TCS()
{
  flag=0;
  digitalWrite(s1,HIGH);
  digitalWrite(s0,HIGH);
  digitalWrite(s2,LOW);
  digitalWrite(s3,LOW);
  digitalWrite(7,HIGH);
  attachInterrupt(digitalPinToInterrupt(2), ISR_INTO, CHANGE);
  timer0_init();

  delay(5000);
  digitalWrite(s1,LOW);
  digitalWrite(s0,LOW);
  digitalWrite(s2,LOW);
  digitalWrite(s3,LOW);
  digitalWrite(7,LOW);
  return;
}

void ISR_INTO()
{
  counter++;
}
void timer0_init(void)
{
  TCCR2A=0x00;
  //TCA0_SINGLE_CTRLC=0x00;
  TCCR2B=0x07;   //the clock frequency source 1024 points (for accuracy)
  //TCA0_SINGLE_CTRLA = 0x0f; // RTC_CTRLA=0x51;
  TCNT2= 100;    //10 ms overflow again
  //TCA0_SINGLE_CTRLC = 100;
  //TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
  TIMSK2 = 0x01; //allow interrupt
  //TCA0_SINGLE_INTCTRL =  TCA_SINGLE_OVF_bm; //allow interrupt
}
int i=0;
ISR(TIMER2_OVF_vect)//the timer 2, 10ms interrupt overflow again. Internal overflow interrupt executive function
//ISR(TCA0_OVF_vect)//the timer 2, 10ms interrupt overflow again. Internal overflow interrupt executive function
{
  TCNT2=100;
  //TCA0_SINGLE_CTRLC = 100;
  //TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
  flag++;
  if(flag==1)
  {
    countR=counter;
    Serial.print("red=");
    Serial.println(countR,DEC);
    digitalWrite(s2,HIGH);
    digitalWrite(s3,HIGH);
  }
  else if(flag==2)
  {
    countG=counter;
    Serial.print("green=");
    Serial.println(countG,DEC);
    digitalWrite(s2,LOW);
    digitalWrite(s3,HIGH);
  }
  else if(flag==3)
  {
    countB=counter;
    Serial.print("blue=");
    Serial.println(countB,DEC);
    Serial.println("\n");
    digitalWrite(s2,LOW);
    digitalWrite(s3,LOW);
  }
  else if(flag==4)
  {
    flag=0;
  }
  counter=0;
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
    Serial.print("FORWARDS");
    myservo1.writeMicroseconds(994); 
    myservo2.writeMicroseconds(2014);
    delay(1000);
    
  }

  else if(receivedChar == 's') { //move backwards
    Serial.print("BACKWARDS");
    myservo1.writeMicroseconds(2014);
    myservo2.writeMicroseconds(994);
    delay(1000);
    
  }

  else if(receivedChar == 'a') {
    Serial.print("LEFT");
    myservo1.writeMicroseconds(994); //opposite turn, left or right?
    myservo2.writeMicroseconds(994);
    delay(1000);
    
    //myservo1.write(91); //stop
    //myservo2.write(91);
    //delay(500);
  }

  else if(receivedChar == 'd') {
    Serial.print("RIGHT");
    myservo1.writeMicroseconds(2014); //opposite turn as above, right or left?
    myservo2.writeMicroseconds(2014);
    delay(1000);
    
    //myservo1.write(91); //stop
    //myservo2.write(91);
    //delay(500);
  }

  else if(receivedChar == 'z') {
    Serial.print("STOP");
    myservo1.write(91); //trial and error found 91 to correlate with stop
    myservo2.write(91);
    delay(500);
  }

  else if(receivedChar == 'c') {
    TCS();
  }


  else{
    myservo1.write(91); //trial and error found 91 to correlate with stop
    myservo2.write(91);
  }
}
