#include <LiquidCrystal.h>
int input=9;

int high_time;
int low_time;
float time_period;
float frequency;
//LiquidCrystal   (rs, enable, d4, d5, d6, d7) ;
LiquidCrystal lcd (12,   13  ,  7, 6, 5,  4);
void setup()
{

pinMode(11,OUTPUT);  
pinMode(input,INPUT);
lcd.begin(16, 2);

}
void loop()
{

lcd.clear();
lcd.setCursor(0,0);
lcd.print("Freq =");

//tone (11,5);
high_time=pulseIn(input,HIGH);
low_time=pulseIn(input,LOW);

 
time_period=high_time+low_time;
time_period=time_period/1000;
frequency=1000/time_period;
lcd.setCursor(0,1);
lcd.print(frequency);
lcd.print(" Hz");
delay(500);

}


