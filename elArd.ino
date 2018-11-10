const byte motor1 = 9; 
const byte motor2 = 11 ;
const byte awama  = 13 ;


void setup() {
  pinMode(motor1,OUTPUT);  
  pinMode(motor2,OUTPUT);
  pinMode(awama,INPUT_PULLUP); 
}

void loop() {
    /* if tank is embty */   /*turn of motor2 */  
    while (digitalRead(awama)) 
    {
    digitalWrite(motor2,HIGH);
    
    /* turn on Motor1 */  
    digitalWrite(motor1,LOW); 
    /* wait 5 minutes = 300 sec*/
    for(int a = 0 ; a<300 && (digitalRead (awama) == HIGH) ; a++)
    delay(1000);
    /* turn off motor 2 */
    digitalWrite(motor1,HIGH);
    /* wait 10 minutes = 600 sec */ 
    for(int a = 0 ; a<600 && (digitalRead (awama) == HIGH) ; a++) 
    delay(1000);
    }
    
    /* if tank is not empty*/
    while (!digitalRead(awama))
    {
    /* make sure last state of motor1 is off*/  
    digitalWrite(motor1 ,HIGH);   
    /* turn on motor2 */ 
    digitalWrite(motor2 ,LOW);  
    
    }

    
}
