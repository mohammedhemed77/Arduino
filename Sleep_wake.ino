// How to make arduino sleep 
// ---------------------------
#include <avr/sleep.h>
#include <avr/power.h>

int int_pin = 2 ; 

void SleepNow (void)
{
digitalWrite (13,LOW);
set_sleep_mode (SLEEP_MODE_PWR_DOWN);
sleep_enable (); 
attachInterrupt (0,WakeUp,LOW);
sleep_mode ();
sleep_disable ();         // program will continue from here 
detachInterrupt (0);
}

void WakeUp(void){
digitalWrite (3,HIGH) ; 

}
void setup (){
pinMode (13,OUTPUT); 
pinMode (3,OUTPUT); 
pinMode (int_pin , INPUT) ; 

}
void loop(){
for (int a = 0; a<10 ; a++) 
{
digitalWrite (13,HIGH);
delay (500); 
digitalWrite (13,LOW);
delay (500);
}
digitalWrite (3,LOW);
delay (20); 
SleepNow ();

}










