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
  
  or_sr(0x18);			/* CPU off, GIE on */
}

// global state var to count time
int secondCount = 0;

int led_switch_DT() //DT = double time
{
  if(secondCount % 125 == 0){ //twice per second
    P1OUT ^= LED_GREEN;
    P1OUT ^= LED_RED;
  }
}
int countSlow = 0;
int led_switch_ES() //ES = extra slow
{
  if(secondCount == 250) countSlow++;
  if(countSlow == 2) {
    countSlow = 0;
    P1OUT ^= LED_GREEN;
    P1OUT ^= LED_RED;
  }
}

int swap=0;
void
__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  secondCount ++;
  if(swap <= 4) {
  led_switch_DT();
  }else{
    led_switch_ES();
    if(swap > 10) swap = 0;
  }
  
  if (secondCount >= 250) { 	/* once each sec... */
    secondCount = 0;            /* reset count */
    swap++;
  }
} 

