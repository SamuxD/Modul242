#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>

void setup() {
    Timer1.initialize();
    MFS.initialize(&Timer1);
}

//set the Control state to let the pointometer Control the leds
int pointometerControlsLeds = 1;

void loop() {
    
    byte btn = MFS.getButton();
    int displayValue = analogRead(POT_PIN);
    MFS.write((int)displayValue);
    delay(100);

//check if the pointometer is controling the led state
if(pointometerControlsLeds == 1){
    if(displayValue > 0 && displayValue <= 100)
    {
      MFS.writeLeds(LED_1, ON);
    }
    else{
      MFS.writeLeds(LED_1, OFF);
    }
    if(displayValue > 100 && displayValue <= 200)
    {
      MFS.writeLeds(LED_2, ON);
    }
    else{
      MFS.writeLeds(LED_2, OFF);
    }
    if(displayValue > 200 && displayValue <= 300)
    {
      MFS.writeLeds(LED_3, ON);
    }
    else{
      MFS.writeLeds(LED_3, OFF);
    }
    if(displayValue > 300 && displayValue <= 400)
    {
      MFS.writeLeds(LED_4, ON);
    }
    else{
      MFS.writeLeds(LED_4, OFF);
    }
    //sound an alarm if the value of 400 is exceeded
    if(displayValue > 400)
    {
      MFS.beep(5);
    }

}
//initialize Buttons
    if(btn)
    {
      byte buttonNumber = btn & B00111111;
      byte buttonAction = btn & B11000000;

      if(buttonAction == BUTTON_PRESSED_IND) {
        if(buttonNumber == 1) {
          pointometerControlsLeds = 0;
          MFS.writeLeds(LED_ALL, ON);
        }
        if(buttonNumber == 2) {
          pointometerControlsLeds = 1;        
          MFS.writeLeds(LED_ALL, OFF);  
        }
        //check if the 3rd Button is pressed and if thats the case turn off the beep (used if e.g. the sensor is broken)
        if(buttonNumber == 3) {
          pointometerControlsLeds = 0;
          MFS.write(" ");
          MFS.beep(OFF);
        }
      }
}
}
