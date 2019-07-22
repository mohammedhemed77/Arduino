#include <LiquidCrystal.h>
#include <avr/sleep.h>
static int index = 1 ;
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

const byte MAX_MINUTES = 180  ; 
const byte MAX_BONUS =  59; 

byte pressCount = 0 ;
boolean bonusFlag1 = true;
boolean bonusFlag2 = true;
boolean winnerIsPlayerOne = false ;
boolean winnerIsPlayerTwo = false ;
boolean gameStarted = false ;
/* time variables */
byte minutes = 0 ;
byte minutes2 = 0 ;
byte seconds = 0 ;
byte seconds2 = 0 ;
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
  else minutes = minutes2 = index - 1 ;
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
  /***********************/
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
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print ("Select time");
  lcd.setCursor(0, 1);
  lcd.print(String ("* ") + index + String(" mins"));

  /* while user don't press any button */
  /* ------------------------------------ */
  goToSleep();
}

void loop()
{
  
  
  digitalWrite (backLight, HIGH);
  if (digitalRead(downBtn) == LOW )
  {
    while (digitalRead(downBtn) == LOW);
    if (pressCount == 0)
    {
      lcd.setCursor(0, 1);
      lcd.print("                ");
      if (index == 0) index = MAX_MINUTES+1  ; 
      lcd.setCursor(0, 1);
      lcd.print(String ("* ") + --index + String(" mins"));
      
    }
    else if (pressCount == 1)
    {
      lcd.setCursor(0, 1);
      lcd.print("                ");
      if (bonusTime == 0) bonusTime = MAX_BONUS+1 ;
      lcd.setCursor(0, 1);
      lcd.print(String("* ") + --bonusTime + String(" sec"));
      
    }
  }      
  else if (digitalRead(upBtn) == LOW)
  {
    while (digitalRead(upBtn) == LOW);
    if (pressCount == 0)
    {
      lcd.setCursor(0, 1);
      lcd.print("                ");
      if (index == MAX_MINUTES) index = -1 ;
      lcd.setCursor(0, 1);
      lcd.print(String("* ") + ++index + String(" mins"));
      
    }
    else if (pressCount == 1)
    {
      lcd.setCursor(0, 1);
      lcd.print("                ");
      if (bonusTime == MAX_BONUS) bonusTime = -1 ;
      lcd.setCursor(0, 1);
      lcd.print(String("* ") + ++bonusTime + String(" sec"));
      
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
      //pressCount = 0;
      start();
      gameStarted = true ;
    }

  }



  if ((digitalRead(player1Btn) == LOW) && (gameStarted == true))
  {

    while (digitalRead(player1Btn) == LOW);
    digitalWrite(13, !digitalRead(13));
    stopTime(1);
    while ((digitalRead(player1Btn) == HIGH)&& (digitalRead(player2Btn) == HIGH)&&(winnerIsPlayerTwo == false))
    { 
    updatePlayerTwoBonus();
    startPlayerTwoTime();
       
    }
  }

  else if ((digitalRead(player2Btn) == LOW ) && (gameStarted == true))
  {
    while (digitalRead(player2Btn) == LOW);
    digitalWrite(13, !digitalRead(13));
    stopTime(2);
    while ((digitalRead(player2Btn) == HIGH)&&(digitalRead(player1Btn) == HIGH)&&(winnerIsPlayerOne == false))
    {
    updatePlayerOneBonus();
    startPlayerOneTime();
    }
  }
  

}



void playerTimeOut(byte player) {
  if (player == 1)
  {
    lcd.setCursor(1, 1);
    lcd.print("      ");
    lcd.setCursor(1, 1);
    lcd.print(String("00") + String(":") + String("00") );
    
  }

  else if (player == 2) {
    lcd.setCursor(10, 1);
    lcd.print("      ");
    lcd.setCursor(10, 1);
    lcd.print(String("00") + String(":") + String("00") );
    
  }
}

void whoIsWinner ()
{
  byte winner = 0 ;
  
  if      (winnerIsPlayerOne == true ) winner = 1 ;
  else if (winnerIsPlayerTwo == true ) winner = 2 ;
  
  if (winnerIsPlayerOne|winnerIsPlayerTwo)
  {
  lcd.clear();
  for (byte a = 0 ; a < 10 , ((winner == 1) || (winner == 2)); a++)
  {
    lcd.setCursor(0, 0);
    lcd.print(String("Player(") + winner + String(")Winner!"));
    lcd.flush();
  }
  }
}

void goToSleep(void) {
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

void stopTime (byte player) {
  if (player == 2)
  {
    lcd.setCursor(10, 1);
    lcd.print(minutes2 + String(":") + seconds2 );
    bonusFlag2 = true ;
  }
  else if (player == 1)
  {
    lcd.setCursor(1, 1);
    lcd.print(minutes + String(":") + seconds );
    bonusFlag1 = true ;
  }

}


void updatePlayerOneBonus() {
      if ((bonusFlag1 == true ) && (winnerIsPlayerTwo == false))
      {
        if ((bonusTime + seconds) < 60)
          seconds = ((seconds + bonusTime) % 60) + 1 ;
        else {
          minutes++ ;
          seconds = ((seconds + bonusTime) % 60) + 1;
        }
        bonusFlag1 = false ;
      }
    }

     void updatePlayerTwoBonus() { 
     
     if ((bonusFlag2 == true) && (winnerIsPlayerOne == false)) 
     {
      if ((bonusTime + seconds2) < 60)  
         seconds2 = ((seconds2 + bonusTime) % 60) + 1 ;
      else {
        minutes2++ ;
        seconds2 = ((seconds2 + bonusTime) % 60) + 1;
      }
      bonusFlag2 = false ;
    }
     }
    void startPlayerOneTime()
      {      
      if ((millis()%200 == 0)&&!winnerIsPlayerTwo)
      {
      lcd.setCursor(1, 1);
      lcd.print("      ");
      lcd.setCursor(1, 1);
      lcd.print(minutes + String(":") + --seconds );
      }
      if ((seconds == 0) && (minutes != 0)) {
        minutes--;
        seconds = 60;
      }
      if ((minutes == 1) && (seconds == 0)) seconds = 59;
      if ((minutes == 0) && (seconds == 0)) {winnerIsPlayerTwo = true ; whoIsWinner(); /*delay(100);*/}
      }

 void startPlayerTwoTime()
   {      
    if ((millis()%200 == 0)&&!winnerIsPlayerOne)
    {  
      lcd.setCursor(10, 1);
      lcd.print("      ");
      lcd.setCursor(10, 1);
      lcd.print(minutes2 + String(":") + --seconds2 );
    } 
      if ((seconds2 == 0) && (minutes2 != 0)) {
        minutes2--;
        seconds2 = 60;
      }
      if ((minutes2 == 1) && (seconds2 == 0)) seconds2 = 59;
      if ((minutes2 == 0) && (seconds2 == 0)) {winnerIsPlayerOne = true ; whoIsWinner(); /*delay(100);*/}
   }
