//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int main(void) {
  P1DIR |= LEDS;
  P1OUT &= ~LED_GREEN;
  P1OUT |= LED_RED;

  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
  
  or_sr(0x18);		/* CPU off, GIE on */
}

void greenControl(int on) // toggle green light
{
  if (on) {
    P1OUT |= LED_GREEN;
  } else {
    P1OUT &= ~LED_GREEN;
  }
}

// blink state machine
static int blinkLimit = 5;   // state var representing reciprocal of duty cycle 
void blinkUpdate() // called every 1/250s to blink with duty cycle 1/blinkLimit
{
  static int blinkCount = 0; // state var representing blink state
  blinkCount ++;
  if (blinkCount >= blinkLimit) {
    blinkCount = 0;
    greenControl(1);
  } else
    greenControl(0);
}

void __interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  // handle blinking
  blinkUpdate();
                               // move timeAdvStateMachines
  static int secondCount = 0;  // move secondUpdate
  secondCount++;
  if (secondCount >= 250) {
    secondCount = 0;
    blinkLimit++;              //  move oncePerSecond
    if (blinkLimit >= 8) {
      blinkLimit = 0;
    }
  }
}
