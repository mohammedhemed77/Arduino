/****************************************************** 
* Play with arduino to make RTC in breadboard using   * 
* 4 digits seven segments using multplexing           * 
* 4 transistors 2n222A                                *
* DS1307 RTC                                          *
* But the hardware has issue RTC IC is not accurate   *
********************************************************/

#include <Wire.h>
#include <I2C_RTC.h>

#define D1   12
#define D2   3 
#define D3   4 
#define D4   5 
#define a    6
#define b    7
#define c    8
#define d    9
#define e    10 
#define f    11
#define g    13

#define btn 2

void turn_off_all_digits()
{
digitalWrite(D1,LOW);
digitalWrite(D2,LOW);
digitalWrite(D3,LOW);
digitalWrite(D4,LOW);
}
void display_digit(uint8_t num){
switch (num){
        case 0 :
            digitalWrite(a,HIGH);
            digitalWrite(b,HIGH);
            digitalWrite(c,HIGH);
            digitalWrite(d,HIGH);
            digitalWrite(e,HIGH);
            digitalWrite(f,HIGH);
            digitalWrite(g,LOW); 
            break; 
        case 1 :
            digitalWrite(b,HIGH);
            digitalWrite(c,HIGH);
            digitalWrite(a,LOW);
            digitalWrite(d,LOW);
            digitalWrite(e,LOW);
            digitalWrite(f,LOW);
            digitalWrite(g,LOW); 
            break;
        case 2 :
            digitalWrite(a,HIGH);
            digitalWrite(b,HIGH);
            digitalWrite(g,HIGH);
            digitalWrite(e,HIGH);
            digitalWrite(d,HIGH);
            digitalWrite(c,LOW);
            digitalWrite(f,LOW); 
            break;
        case 3 :
            digitalWrite(a,HIGH);
            digitalWrite(b,HIGH);
            digitalWrite(c,HIGH);
            digitalWrite(d,HIGH);
            digitalWrite(e,LOW);
            digitalWrite(f,LOW);
            digitalWrite(g,HIGH); 
            break;
        case 4 :
            digitalWrite(a,LOW);
            digitalWrite(b,HIGH);
            digitalWrite(c,HIGH);
            digitalWrite(d,LOW);
            digitalWrite(e,LOW);
            digitalWrite(f,HIGH);
            digitalWrite(g,HIGH); 
            break;
        case 5 :
            digitalWrite(a,HIGH);
            digitalWrite(b,LOW);
            digitalWrite(c,HIGH);
            digitalWrite(d,HIGH);
            digitalWrite(e,LOW);
            digitalWrite(f,HIGH);
            digitalWrite(g,HIGH); 
            break;
        case 6 :
            digitalWrite(a,HIGH);
            digitalWrite(b,LOW);
            digitalWrite(c,HIGH);
            digitalWrite(d,HIGH);
            digitalWrite(e,HIGH);
            digitalWrite(f,HIGH);
            digitalWrite(g,HIGH);
            break;
        case 7 :
            digitalWrite(a,HIGH);
            digitalWrite(b,HIGH);
            digitalWrite(c,HIGH);
            digitalWrite(d,LOW);
            digitalWrite(e,LOW);
            digitalWrite(f,LOW);
            digitalWrite(g,LOW);  
            break;
        case 8 :
            digitalWrite(a,HIGH);
            digitalWrite(b,HIGH);
            digitalWrite(c,HIGH);
            digitalWrite(d,HIGH);
            digitalWrite(e,HIGH);
            digitalWrite(f,HIGH);
            digitalWrite(g,HIGH);
            break;
        case 9 :  
            digitalWrite(a,HIGH);
            digitalWrite(b,HIGH);
            digitalWrite(c,HIGH);
            digitalWrite(d,HIGH);
            digitalWrite(e,LOW);
            digitalWrite(f,HIGH);
            digitalWrite(g,HIGH);
            break;
}
}




static DS1307 RTC;
unsigned long interval = 0;
void setup() {
for (int i = 3 ; i <=13; i++)  {pinMode(i,OUTPUT);}

 pinMode(btn,INPUT_PULLUP);
 //attachInterrupt(digitalPinToInterrupt(btn), set_time, LOW);
 RTC.begin();
 //RTC.setOutPin(SQW001Hz);
 //Serial.begin(9600);
  
}

void loop() {

  if (!digitalRead(btn))
  {
  RTC.setHours(map(analogRead(A2),0,1023,1,13));
  RTC.setMinutes(map(analogRead(A3),0,1023,0,60));  
  }
  /*
  Serial.print(RTC.getHours());
  Serial.print(":");
  Serial.print(RTC.getMinutes());
  Serial.print(":");
  Serial.println(RTC.getSeconds());
*/
// disalble all digits except digit 1 
digitalWrite(D1,HIGH);
digitalWrite(D2,LOW);
digitalWrite(D3,LOW);
digitalWrite(D4,LOW);
display_digit((RTC.getMinutes()%10));
delay(5);
turn_off_all_digits();
// disalble all digits except digit 2 

digitalWrite(D1,LOW);
digitalWrite(D2,HIGH);
digitalWrite(D3,LOW);
digitalWrite(D4,LOW);
display_digit((RTC.getMinutes()/10));
delay(5);
turn_off_all_digits();
// disalble all digits except digit 3 
digitalWrite(D1,LOW);
digitalWrite(D2,LOW);
digitalWrite(D3,HIGH);
digitalWrite(D4,LOW);
display_digit((RTC.getHours()%10));
delay(5);
turn_off_all_digits();

if ((RTC.getHours()/10) == 0) digitalWrite(D4,LOW);
else {
// disalble all digits except digit 4 
digitalWrite(D1,LOW);
digitalWrite(D2,LOW);
digitalWrite(D3,LOW);
digitalWrite(D4,HIGH);
display_digit((RTC.getHours()/10));
delay(5);
turn_off_all_digits();
}
}
