#include "MQ135.h"
#define ANALOGPIN A0    //  Define Analog PIN on Arduino Board
#define RZERO 174.02    //  Define RZERO Calibration Value
/*********************
pin configuration 
-------------------------
white  -> 5v
Black  -> Gnd 
violet -> A0 
grey   -> not Connected 
*************************/

/* غيري الكاليبرشن فاليو من السطر دا  */
/*---------------------------------------*/
#define CaliberationFactor 1999.0
/**************************************** */
MQ135 gasSensor = MQ135(ANALOGPIN);

void setup()
{
  Serial.begin(9600);
  float rzero = gasSensor.getRZero();
  delay(3000);
  Serial.print("MQ135 RZERO Calibration Value : ");
  Serial.println(rzero);
}

void loop() { 
  float ppm = CaliberationFactor*gasSensor.getPPM();
  delay(100);
  digitalWrite(13,HIGH);
  Serial.print("CO2 ppm value : ");
  Serial.println(ppm);
}
