#include <msp430.h>
#include "libTimer.h"
#include "led.h" 

// global state vars that control song and lights
int timeCount = 0; // state var representing repeating time 0…1s
int seconds = 0;  // state var representing repeating time 1…60s
int blinkLimit = 5;  // duty cycle = 1/blinkLimit
int blinkCount = 0;  // cycles 0...blinkLimit-1


void timeChange() {  // track time
  timeCount ++;
  if(timeCount % 50 == 0) seconds++; // increments every 1/5 sec
  if(seconds >= 70) seconds = 0;
  if (timeCount >= 250) {  // once every second
    timeCount = 0;
    blinkLimit ++;     // reduce duty cycle
    if (blinkLimit >= 8)     // but don't let duty cycle go below 1/7.
      blinkLimit = 0;
  }
}

void dimmer() {  // handle blinking
  blinkCount ++;
  if (blinkCount >= blinkLimit) { // on for 1 interrupt period
    blinkCount = 0;
    P1OUT |= LED_GREEN;
    P1OUT &= ~LED_RED;
  } else {          // off for blinkLimit - 1 interrupt periods
    P1OUT &= ~LED_GREEN;
    P1OUT |= LED_RED;
  }
 }
