/*interrupt change pin */
const byte led = 4 ; 
void setup() {
 pinMode (led,OUTPUT); 
 Serial.begin(9600);
 bitSet(PCICR, PCIE2); // enable pin change interrupt bank 0
 bitSet (PCMSK2, PCINT20); // enable pin change interrupt on PCINT5/D13
 
}

void loop() {
  digitalWrite(led,!digitalRead(4)) ; 
  delay (500) ;
  }

ISR(PCINT2_vect) {
if(digitalRead(led) == HIGH) {
Serial.println("LED is on");
} else {
Serial.println("LED is off");
}
}
