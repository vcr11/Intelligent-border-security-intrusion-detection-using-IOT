

#include <SoftwareSerial.h>
SoftwareSerial mySerial(2,3);


int m1=4,m2=5,m3=6,m4=7;
const int trigPin = A4; 
const int echoPin = A5;
int v1 = 8;
int v2 = 9;
int fire = 10;
int metal = A0;
int buz = A1;
int relay = 11;
String readvoice;
long duration;
int distance;

 int value = 0;
void serialFlush();
char res[130];
char buff[130];
 char mob[15] = {"8790931022\0"};
 // char mob1[15] = {"8143580564\0"};
 
char gps_location[40];
void gps()
{

  Serial.println("gps activated"); 
   while(1)
   {
    if(mySerial.find("$GPRMC"))
    {
      for(int i=0;i<14;i++)
      {
        while(!mySerial.available());
        char ch = mySerial.read();
      }
      for(int i=0;i<24;i++)
      {
        while(!mySerial.available());
        gps_location[i] = mySerial.read();
        mySerial.println(gps_location[i]);
         Serial.println(gps_location[i]);
      }
       break;      
    }
   }
   
     delay(2000);
   
}
 void sendmsg(char *num,char *msg,char *loc)
{
  mySerial.print("AT+CMGS=\"");
  mySerial.print(num);
  mySerial.println("\"");
  delay(2000);
  mySerial.println(msg);
  mySerial.println(loc);
  delay(1000);
  mySerial.write(0x1a);
  delay(2000);
   Serial.println("msg sent : "); 
}


int sound=A0;

void setup() {  
  

  Serial.begin(9600);
   mySerial.begin(9600); 


 pinMode(trigPin, OUTPUT); 
 pinMode(echoPin, INPUT);
 pinMode(m1,OUTPUT);
 pinMode(m2,OUTPUT);
 pinMode(m3,OUTPUT);
 pinMode(m4,OUTPUT);
 pinMode(v1,OUTPUT);
 pinMode(v2,OUTPUT);
 pinMode(relay,OUTPUT);
 pinMode(buz, OUTPUT); 
 pinMode(metal, INPUT);
 pinMode(fire, INPUT);
 digitalWrite(m1,LOW);
 digitalWrite(m2,LOW);
 digitalWrite(m3,LOW);
 digitalWrite(m4,LOW);
 digitalWrite(buz,HIGH);
 digitalWrite(v1,HIGH);
 digitalWrite(v2,HIGH);
 digitalWrite(relay,LOW);
  mySerial.println("AT");  delay(1000);
  mySerial.println("ATE0");  delay(1000);
  mySerial.println("AT+CMGF=1");  delay(1000);
  mySerial.println("AT+CNMI=1,2,0,0");  delay(1000);
  mySerial.println("AT+CSMP=17,167,0,16");  delay(1000);
                  gps();
  sendmsg(mob," robo at location:",gps_location);delay(1000);
  //sendmsg(mob1," Vechile  Location at:",gps_location);delay(3000);
   Serial.println("welcome "); 
 delay(500);

  
}
void loop() 
{
    digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  

      Serial.print("metal : "); 
    Serial.println(digitalRead(metal)); 
    Serial.print("fire : "); 
    Serial.println(digitalRead(fire)); 
    Serial.print("distance : "); 
    Serial.println(distance); 

                                    delay(500);
     if ( distance < 30)
    {
  
       Serial.println("object detected");
     Serial.println("object detected");
   digitalWrite (m1, LOW);
   digitalWrite (m2, LOW);
   digitalWrite (m3, LOW);
   digitalWrite (m4, LOW);
      delay(1000);
    }
    if ( digitalRead(metal) == 1)
    {
       Serial.println("bomb detected");
   digitalWrite (m1, LOW);
   digitalWrite (m2, LOW);
   digitalWrite (m3, LOW);
   digitalWrite (m4, LOW);
    digitalWrite (buz, LOW);digitalWrite (v1, LOW);delay(1000);digitalWrite (buz, HIGH);delay(1000);digitalWrite (buz, LOW);delay(1000);digitalWrite (buz, HIGH);
    digitalWrite (v1, LOW);delay(1000);gps();
   sendmsg(mob,"Bomb detected at Location:",gps_location);delay(1000);
      delay(1000);
    }

    if ( digitalRead(fire) == 0)
    {
   
       Serial.println("fire detected");
   digitalWrite (m1, LOW);
   digitalWrite (m2, LOW);
   digitalWrite (m3, LOW);
   digitalWrite (m4, LOW); 
    digitalWrite (buz, LOW);digitalWrite (v2, LOW);delay(1000);digitalWrite (buz, HIGH);delay(1000);digitalWrite (buz, LOW);delay(1000);digitalWrite (buz, HIGH);
    digitalWrite (v2, LOW);delay(1000);gps();
   sendmsg(mob,"fire detected at Location:",gps_location);delay(1000);
      delay(1000);
    }
while(Serial.available()){  //Check if there is an available byte to read
  delay(10); //Delay added to make thing stable 
  char c = Serial.read(); //Conduct a serial read
  readvoice += c; //build111 the string- "forward", "reverse", "left" and "right"
  Serial.println(readvoice);
    
           }   
  if(readvoice.length() > 0) {

     //readvoice=0;
    delay(500);
 // if(readvoice == "forward" || "*1") 
  if(readvoice == "*") 
  {
    
 
     Serial.println("Forward");
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
   
  } 
  
  if(readvoice == "#") //*2
  {
    
Serial.println("Backward");
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, LOW);
    digitalWrite(m4, HIGH);
    //delay(100);
  }
  
  
  if(readvoice == "@" ) //"*3")
  {
     
 Serial.println("Right");
      digitalWrite (m1, HIGH);
   digitalWrite (m2, LOW);
   digitalWrite (m3, LOW);
   digitalWrite (m4, HIGH);
   // delay (100);
    
  }
  
 if(readvoice == "%" )//||"*4")
 {
  
   Serial.println("Left");
 

   digitalWrite (m1, LOW);
    digitalWrite (m2, HIGH);
    digitalWrite (m3, HIGH);
    digitalWrite (m4, LOW);
  // delay (100);
 }
 
 if(readvoice == "&") //||"*5")
 {
   Serial.println("Stop");
   digitalWrite (m1, LOW);
   digitalWrite (m2, LOW);
   digitalWrite (m3, LOW);
   digitalWrite (m4, LOW);
  
 }
  if(readvoice == "^") 
 {
   Serial.println("pump on");
   digitalWrite (relay, HIGH);
 }
  if(readvoice == "!") //||"*5")
 {
   Serial.println("pump OFF");
   digitalWrite (relay, LOW);
 }
 }

 readvoice="";


}



void myserialFlush(){
  while(mySerial.available() > 0) {
    char t = mySerial.read();
  }
} 
void serialFlush(){
  while(Serial.available() > 0) {
    char t = Serial.read();
  }
} 
