#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>

void setup() {
    Timer1.initialize();
    MFS.initialize(&Timer1);
}

int lossOfFeetPerMinute = 100;

void loop() {

    byte btn = MFS.getButton();
    MFS.write(lossOfFeetPerMinute);

//initializing Button if it exists + adding Button functionality 
    if(btn)
    {
      byte buttonNumber = btn & B00111111;
      byte buttonAction = btn & B11000000;

      if(buttonAction == BUTTON_PRESSED_IND) {
        if(buttonNumber == 1) {
          //minus Feet per minute to represent a descent
          lossOfFeetPerMinute = lossOfFeetPerMinute - 10;
        }
        if(buttonNumber == 2) {
          //Add Feet per minute to represent a climb in altitude
          lossOfFeetPerMinute = lossOfFeetPerMinute + 10;
        }
        if(buttonNumber == 3) {
          //reset Button
          lossOfFeetPerMinute = 100;
        }
      }

      

    if(lossOfFeetPerMinute < 50)
    {
      MFS.writeLeds(LED_1, ON);
      MFS.writeLeds(LED_2, ON);
      MFS.writeLeds(LED_3, ON);
      MFS.writeLeds(LED_4, ON);
      MFS.beep(1);
    }
    if(lossOfFeetPerMinute > 50 && lossOfFeetPerMinute < 75)
    {
      MFS.writeLeds(LED_1, OFF);
      MFS.writeLeds(LED_2, ON);
      MFS.writeLeds(LED_3, ON);
      MFS.writeLeds(LED_4, ON);
      MFS.beep(OFF);
    }
    if(lossOfFeetPerMinute > 75 && lossOfFeetPerMinute < 125)
    {
      MFS.writeLeds(LED_1, OFF);
      MFS.writeLeds(LED_2, OFF);
      MFS.writeLeds(LED_3, ON);
      MFS.writeLeds(LED_4, ON);
    }
    if(lossOfFeetPerMinute > 125 && lossOfFeetPerMinute < 150)
    {
      MFS.writeLeds(LED_1, OFF);
      MFS.writeLeds(LED_2, OFF);
      MFS.writeLeds(LED_3, OFF);
      MFS.writeLeds(LED_4, ON);
    }
    if(lossOfFeetPerMinute > 150 && lossOfFeetPerMinute < 200)
    {
      MFS.writeLeds(LED_1, OFF);
      MFS.writeLeds(LED_2, OFF);
      MFS.writeLeds(LED_3, OFF);
      MFS.writeLeds(LED_4, OFF);
    }
}
}
