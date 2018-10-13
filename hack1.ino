int trig=4;
  int echo=2;
  int distance;
  long duration;
int s;
  volatile int NbTopsFan; //measuring the rising edges of the signal
int Calc;                               
int hallsensor=9;
void rpm ()     //This is the function that the interupt calls 
{ 
 NbTopsFan++;  //This function measures the rising and falling edge of thehall effect sensors signal
} 
void setup() {
  // put your setup code here, to run once:
 pinMode(A0,INPUT);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
   //pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  Serial.begin(115200);
 pinMode(hallsensor, INPUT); //initializes digital pin 2 as an input
 //Serial.begin(9600); //This is the setup function where the serial port isinitialised,
 attachInterrupt(0, rpm, RISING);
   //Serial.begin(115200); 
  Serial.println("AT+CIPMUX=0");
  delay(1000); 

}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(trig,LOW);
delayMicroseconds(2);
digitalWrite(trig,HIGH);\
delayMicroseconds(10);
digitalWrite(trig,LOW);
duration=pulseIn(echo,HIGH);
distance=0.034*duration;
 NbTopsFan = 0;      //Set NbTops to 0 ready for calculations
 sei();            //Enables interrupts
 delay (1000);      //Wait 1 second
 cli();            //Disable interrupts
 Calc = (NbTopsFan * 60 / 7.5); //(Pulse frequency x 60) / 7.5Q, = flow rate in L/hour 
 Serial.println(Calc, DEC); //Prints the number calculated above
 Serial.println(" L/hour\r\n");
Serial.println(distance);
  int s=analogRead(A0);
  Serial.println(s);
  if (s<200)
  {
    digitalWrite(9,HIGH);
  }
  else
  {
    digitalWrite(9,LOW);
  }
Serial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80");
delay(100);
if (Serial.find("Error")){return;}
String cmd="GET /update?api_key=WGL105A39JX7SUZ1&field1="+String(distance);
cmd=cmd+"&field2="+String(Calc);
cmd=cmd+"\r\n\r\n";

Serial.println("AT+CIPSEND="+String(cmd.length()));
if (Serial.find(">")){Serial.println(cmd);}
else {Serial.println("AT+CIPCLOSE");}
delay(80);
if(distance<40)
{
  //digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
}
else {
   //digitalWrite(8,LOW);
  digitalWrite(9,LOW);
}

  
}
