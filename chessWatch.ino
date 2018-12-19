#include <LiquidCrystal.h>
#include <avr/sleep.h>
static unsigned int index = 1 ;
// initialize the library with the numbers of the interface pins
//               (RS-En - D a  t  a )
LiquidCrystal lcd(2, 3  , 4, 5, 6, 7);

int counter1 = 0 ;
int counter2 = 0 ;
/* Buttons */
const byte backLight = 0 ;
const byte enterBtn = 10 ;
const byte upBtn = 8 ;
const byte downBtn = 9 ;
const byte player1Btn = 11 ;
const byte player2Btn = 12 ;
byte pressCount = 0 ;
boolean oneTimePerPress = true;
/* time variables */
byte minutes = 0 ;
byte minutes2 = 0 ;
byte seconds = 59 ;
byte seconds2 = 59 ;
long int timePassed = 0 ;
const long int timeToSleep = 10 ;
byte bonusTime = 0 ;
void start ()
{
  minutes = index ;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Player1  Player2");
  lcd.setCursor(1, 1);
  lcd.print(minutes + String(":") + String("00") );
  lcd.setCursor(10, 1);
  lcd.print(minutes + String(":") + String("00") );
  if (bonusTime != 0)minutes = minutes2 = index ;
  else minutes = minutes2 = index -1 ; 
  //seconds = (bonusTime + seconds) - 60 ; 
  //seconds2 = (bonusTime + seconds2) - 60 ; 
}



void setup()
{
  pinMode(enterBtn , INPUT_PULLUP);
  pinMode(upBtn , INPUT_PULLUP);
  pinMode(downBtn , INPUT_PULLUP);
  pinMode(player1Btn, INPUT_PULLUP);
  pinMode(player2Btn, INPUT_PULLUP);
  pinMode(backLight, OUTPUT);
  pinMode(13, OUTPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  /* initilaization msg */

  for (byte a = 0 ; a < 5 ; a++)
  {
    lcd.setCursor(0, 0);
    lcd.print("Chess Watch");
    lcd.setCursor(0, 1);
    lcd.print(" Hemed - Sherif ");
    lcd.noDisplay();
    delay(100);
    lcd.display();
    delay(100);
  }
  /* clear the screen */
//  lcd.setCursor(0, 0);
//  lcd.print("                ");
//  lcd.setCursor(0, 1);
//  lcd.print("                ");
  lcd.clear(); 
  lcd.setCursor(0, 0);
  lcd.print ("Select time");
  lcd.setCursor(0, 1);
  lcd.print(String ("* ") + index + String(" mins"));

  /* while user don't press any button */
  /* ------------------------------------ */
  while (digitalRead(enterBtn) && digitalRead(upBtn) && digitalRead(downBtn))
  {
    timePassed = millis() / 1000;
    if (timePassed >= timeToSleep)
    {
      /* turn off lcd light */
      digitalWrite(backLight, LOW);
      set_sleep_mode(SLEEP_MODE_PWR_DOWN);   // sleep mode is set here
      sleep_enable();
      sleep_mode();
    }
  }

}

void loop()
{
   
  digitalWrite (backLight, HIGH);
  if (digitalRead(downBtn) == LOW )
  {
    while (digitalRead(downBtn) == LOW);
    if (bonusTime == 0)
    {
      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.print(String ("* ") + --index + String(" mins"));
      if (index == 1) index = 90 ;
    }
    else
    {
      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.print(String("* ") + --bonusTime + String(" sec"));
      if (bonusTime == 0) bonusTime = 60 ;
    }
  }

  else if (digitalRead(upBtn) == LOW)
  {
    while (digitalRead(upBtn) == LOW);
    if (bonusTime == 0)
    {
      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.print(String("* ") + ++index + String(" mins"));
      if (index == 90) index = 1 ;
    }
    else
    {
      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.print(String("* ") + ++bonusTime + String(" sec"));
      if (bonusTime == 60) bonusTime = 1 ;
    }
  }

  else if (digitalRead(enterBtn) == LOW)
  {
    while (digitalRead(enterBtn) == LOW);
    digitalWrite(13, !digitalRead(13)) ;
    if (pressCount == 0)
    {
      minutes = index ;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("bonus time:");
      bonusTime ++ ;
      lcd.setCursor(0, 1);
      lcd.print(String("* ") + bonusTime + String(" sec"));
      //lcd.print("Enter to start");
      pressCount++ ;
    }
    else if (pressCount == 1)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(String("time : ") + minutes + String(" + ") + bonusTime);
      lcd.setCursor(0, 1);
      lcd.print("Enter to start");
      
      pressCount ++ ;
    }
    else if (pressCount == 2)
    {
      pressCount = 0;
      start();

    }

  }



  if (digitalRead(player1Btn) == LOW)
  {
    
    while (digitalRead(player1Btn) == LOW);
    digitalWrite(13, !digitalRead(13));
    if (counter1 == 0 )
    { 
      while (digitalRead(player1Btn) == HIGH)
      {
        if ((seconds == 0) && (minutes == 0))
        {
          lcd.setCursor(1, 1);
          lcd.print("      ");
          lcd.print(String("00") + String(":") + String("00") );
        }
        
        else
        {
          
          while (oneTimePerPress) {
              if ((((bonusTime + seconds)%bonusTime)<60))  seconds =(seconds+bonusTime)%60 ;
              else {minutes++ ;   seconds =(seconds+bonusTime)%60;}
              oneTimePerPress = false ; 
             } 
          
          delay(1000);
          lcd.setCursor(1, 1);
          lcd.print(minutes + String(":") + seconds-- );
          if ((seconds == 0) && (minutes != 0)) {
            minutes--;
            seconds = 59;
          }
          if ((minutes == 1) && (seconds == 0)) seconds = 59;
        }

      }
      counter1 ++ ;
    }
    else if (counter1 == 1)
    {
      counter1 = 0 ;
      lcd.setCursor(1, 1);
      lcd.print(minutes + String(":") + seconds );
      oneTimePerPress = true ; 
    }

  }
  else if (digitalRead(player2Btn) == LOW )
  {
    while (digitalRead(player2Btn) == LOW);
    digitalWrite(13, !digitalRead(13));
    if (counter2 == 0 )
    {
      while (digitalRead(player2Btn) == HIGH)
      {
        if ((seconds2 == 0) && (minutes2 == 0))
        {
          lcd.setCursor(10, 1);
          lcd.print("      ");
          lcd.print(String("00") + String(":") + String("00") );
        }
        else
        {
          delay(1000);
          lcd.setCursor(10, 1);
          lcd.print(minutes2 + String(":") + seconds2-- );
          if ((seconds2 == 0) && (minutes2 != 0)) {
            minutes2--;
            seconds2 = 59;
          }
          if ((minutes2 == 1) && (seconds2 == 0)) seconds2 = 59;
        }

      }
      counter2 ++ ;
    }
    else if (counter2 == 1)
    {
      counter2 = 0 ;
      lcd.setCursor(10, 1);
      lcd.print(minutes2 + String(":") + seconds2 );
    }


  }
}
