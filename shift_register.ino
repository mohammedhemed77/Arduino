    /*
     Shift Register 74Hc595                
    */
     
    int latchPin = 5;   // 12 Rclk in shift register
    int clockPin = 6;   // 11 in shift register 
    int dataPin = 4;    // Output Enable OE 13
     
    byte leds = 0;
     
    void setup()
    {
    pinMode(latchPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    }
     
    void loop()
    {
    leds = 0;
    updateShiftRegister();
    delay(500);
    for (int i = 0; i < 8; i++)
    {
    bitSet(leds, i);
    updateShiftRegister();
    delay(500);
    }
    }
     
    void updateShiftRegister()
    {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, leds);
    digitalWrite(latchPin, HIGH);
    }
