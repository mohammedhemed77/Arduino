/* When you want to increase No. interrupts in uC   
  you can use interrupt change pin , there are three banks 
  each of them contain a group of pins , if you Enable Int_change 
  for any - or all of them , when state of any of them changed :
  ISR will occure . 
  So Arduino Uno interrupts = 2 + 3 = 5   
   by : Mohammed Sayed hemed 
*/
const byte led = 4 ; 
void setup() {
 pinMode (led,OUTPUT); 
 Serial.begin(9600);
 bitSet (PCICR, PCIE2);       // enable pin change interrupt bank 2
 bitSet (PCMSK2, PCINT20);   // enable pin change interrupt on PCINT20/D4
 
}

void loop() {
  digitalWrite(led,!digitalRead(4)) ; 
  delay (500) ;
  }
/* Every bank has ISR 0:2 = 3 banks */
ISR(PCINT2_vect) {
if(digitalRead(led) == HIGH) {
Serial.println("LED is on");
} else {
Serial.println("LED is off");
}
}
