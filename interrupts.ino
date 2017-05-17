/* When you enable interrupt and don't write 
it's handler the cpu reset 
so in this case you can change this action
*/
const char int_pin = 2 ; 
const byte led = 13 ;   
volatile byte led_now = LOW ; 
void setup() {
pinMode (led,OUTPUT) ;  
pinMode ( int_pin , INPUT_PULLUP) ; 
attachInterrupt (digitalPinToInterrupt(int_pin),int_fun,CHANGE) ; 
byte a = 10; 
for (;--a;) 
{
bitSet(PINB,5) ; 
delay(500);   
}

}

void loop() {
digitalWrite(led , led_now) ; 
}
void int_fun(){
led_now = ! led_now ; 
  }
  
ISR (BADISR_vect) {
  
  }
