/* programmable arduino frequency
   reduce power consumption  
*/
/* divide freqency by programmable factor */
/*
void setup ()
{
 
 pinMode(13,OUTPUT) ;  
 noInterrupts() ; 
 CLKPR |= 1<<CLKPCE ;       //enable clk prescaller   
 CLKPR = 8  ;               //select cock divisor 256 now clk = 62.5 Khz 
 interrupts() ; 
  
}

void loop (){
digitalWrite(13,HIGH) ;
delay(10);                  // time delay = 2.56
digitalWrite(13,LOW) ;  
delay(10);
}
*/
/*using sleep modes */
#include <avr/sleep.h>
extern volatile unsigned long timer0_millis ; 
void setup ()
{
pinMode (13,OUTPUT);  
}

void loop ()
{
while(timer0_millis < 1000) {
  set_sleep_mode (SLEEP_MODE_IDLE) ;
  sleep_mode() ; 
  }
timer0_millis = 0 ; 
bitSet(PINB,5) ;  

}















