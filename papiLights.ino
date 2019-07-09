#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>

void setup() {
    Timer1.initialize();
    MFS.initialize(&Timer1);
}

//set initial height
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
      }

      
//check if the plane is too low if thats the case sound warning noise + let all 4 leds shine in red
    if(lossOfFeetPerMinute < 50)
    {
      MFS.writeLeds(LED_1, ON);
      MFS.writeLeds(LED_2, ON);
      MFS.writeLeds(LED_3, ON);
      MFS.writeLeds(LED_4, ON);
      MFS.beep(3);
    }
//check if the plane is just slightly to low if so turn on 3 of 4 leds 
    if(lossOfFeetPerMinute > 50 && lossOfFeetPerMinute < 75)
    {
      MFS.writeLeds(LED_1, OFF);
      MFS.writeLeds(LED_2, ON);
      MFS.writeLeds(LED_3, ON);
      MFS.writeLeds(LED_4, ON);
      MFS.beep(OFF);
    }
//check if the plane is on a suitable height turn off 2 leds to represent 2 white and let 2 turned on so that youve got 2 "white" and 2 red to indicate that everything is fine
    if(lossOfFeetPerMinute > 75 && lossOfFeetPerMinute < 125)
    {
      MFS.writeLeds(LED_1, OFF);
      MFS.writeLeds(LED_2, OFF);
      MFS.writeLeds(LED_3, ON);
      MFS.writeLeds(LED_4, ON);
    }
//check if the plane is slightly to high if so show 3 white 1 red
    if(lossOfFeetPerMinute > 125 && lossOfFeetPerMinute < 150)
    {
      MFS.writeLeds(LED_1, OFF);
      MFS.writeLeds(LED_2, OFF);
      MFS.writeLeds(LED_3, OFF);
      MFS.writeLeds(LED_4, ON);
    }
//check if user is way to high turn off all leds to represent 4 white which indicates that the plane is way heigher than its supposed to be
    if(lossOfFeetPerMinute > 150 && lossOfFeetPerMinute < 200)
    {
      MFS.writeLeds(LED_1, OFF);
      MFS.writeLeds(LED_2, OFF);
      MFS.writeLeds(LED_3, OFF);
      MFS.writeLeds(LED_4, OFF);
    }

}
