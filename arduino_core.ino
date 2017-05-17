/*
 * Arduino core learning
 * mohammed sayed hemed
*/
extern volatile unsigned long timer0_millis  ;
void setup() {
  DDRB |= 1<<5 ; 
   
}

void loop() {
  
/*simple blink led 13 code - size = 486 bytes*/  
volatile unsigned int x = 60000 ;   // write volatile to prevent optimization  
bitSet (PINB , 5) ;       // use PIN register to flip the state of output 
/* delay manually */
for (;--x;) ;      
// another way to dalay : 
while (timer0_millis < 1000) ;  // wait 1 sec
timer0_millis =  0 ;           // reset timer 0 

}
