int s0=3,s1=4,s2=5,s3=6;
int out=2;
int flag=0;
byte counter=0;
byte countR=0,countG=0,countB=0;
void setup()
{
  Serial.begin(9600);
  pinMode(s0,OUTPUT);
  pinMode(s1,OUTPUT);
  pinMode(s2,OUTPUT);
  pinMode(s3,OUTPUT);
  pinMode(7,OUTPUT);
}
void TCS()
{
  flag=0;
  digitalWrite(s1,HIGH);
  digitalWrite(s0,HIGH);
  digitalWrite(s2,LOW);
  digitalWrite(s3,LOW);
  digitalWrite(7,LOW);
  attachInterrupt(digitalPinToInterrupt(2), ISR_INTO, CHANGE);
  timer0_init();
}
void ISR_INTO()
{
  counter++;
}
void timer0_init(void)
{
  //TCCR2A=0x00;
  //TCA0_SINGLE_CTRLC=0x00;
  //TCCR2B=0x07;   //the clock frequency source 1024 points (for accuracy)
  TCA0_SINGLE_CTRLA = 0x0f; // RTC_CTRLA=0x51;
  //TCNT2= 100;    //10 ms overflow again
  TCA0_SINGLE_CTRLC = 100;
  TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
  //TIMSK2 = 0x01; //allow interrupt
  TCA0_SINGLE_INTCTRL =  TCA_SINGLE_OVF_bm; //allow interrupt
}
int i=0;
//ISR(TIMER2_OVF_vect)//the timer 2, 10ms interrupt overflow again. Internal overflow interrupt executive function
ISR(TCA0_OVF_vect)//the timer 2, 10ms interrupt overflow again. Internal overflow interrupt executive function
{
  //TCNT2=100;
  TCA0_SINGLE_CTRLC = 100;
  TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
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
void loop()
{
  TCS();
  while(1);
}
