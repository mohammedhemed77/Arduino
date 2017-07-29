#define Right1 4
#define Right2 5
#define Left1  6
#define Left2  7

#include <SoftwareSerial.h>
SoftwareSerial bluetooth (2,3) ;
  

void setup() {

    Serial.begin(9600);
      bluetooth.begin (9600);
      for (char pin = 4 ; pin <= 7 ; pin++)
    {
      pinMode (pin,OUTPUT); 
    }
    
    } 

void loop() {
        
        char bleutooth_data ;
        bleutooth_data = bluetooth.read ();
        int val = Serial.read() ; 
        if (val == 1 ) forward () ;
        if (val == 2 ) backward () ;
        if (val == 3 ) left () ;
        if (val == 4 ) right () ; 
        if (bleutooth_data == 'f' )
        {
        forward(); 
        } 
        
        if (bleutooth_data == 'l' )
        {
        left(); 
        }
        if (bleutooth_data == 'b' )
        {
        backward ();
        }
        if (bleutooth_data == 'r' )
        {
        right();
        }
        if (bleutooth_data == 's' )
        {
        stopp() ;
        }
        
        }
        
        void forward (void){
          digitalWrite (Right1,HIGH) ;
          digitalWrite(Right2,LOW) ;
          digitalWrite (Left1 ,HIGH) ;
          digitalWrite (Left2,LOW);
          }
        void backward (void){
          digitalWrite (Right2,HIGH) ;
          digitalWrite(Right1,LOW) ;
          digitalWrite (Left2 ,HIGH) ;
          digitalWrite (Left1,LOW);
          }
        void right (void){
          digitalWrite (Right1,HIGH) ;
          digitalWrite(Right2,LOW) ;
          digitalWrite (Left2 ,HIGH) ;
          digitalWrite (Left1,LOW);
          }
        void left (void){
          digitalWrite (Right2,HIGH) ;
          digitalWrite(Right1,LOW) ;
          digitalWrite (Left1 ,HIGH) ;
          digitalWrite (Left2,LOW);
          }
        void stopp (void)
        {
          digitalWrite (Right1,LOW);
          digitalWrite (Right2,LOW);
          digitalWrite (Left1,LOW); 
          digitalWrite (Left2,LOW);
        }

//**************************************************************
/*
for (char p=4 ; p<9 ;p++)
  {
  pinMode (p,OUTPUT);
  }
  myservo.attach(9); 
  pinMode (trig,OUTPUT);
  pinMode (echo,INPUT);
}
digitalWrite (trig,LOW);
  delayMicroseconds (2);
  digitalWrite (trig,HIGH); 
  delayMicroseconds (15); 
  digitalWrite (trig,LOW);
  count = pulseIn (echo,HIGH); 
  reading = count/58 ;
#define trig   10  
#define echo   11
**********************************************************/






