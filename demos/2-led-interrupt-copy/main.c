//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

short second_count = 0;
short led_state = 0;
char led_change() {
  switch (led_state) {
  case 0:
    led_state = 1;
    P1OUT |= LED_GREEN;
    P1OUT &= ~LED_RED;
    break;
  case 1:
    led_state = 0;
    P1OUT |= LED_RED;
    P1OUT &= ~LED_GREEN;
    break;
  }
}

int main(void) {
  P1DIR |= LEDS;
  P1OUT &= ~LED_GREEN;
  P1OUT |= LED_RED;

  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
  
  or_sr(0x18);		/* CPU off, GIE on */
}

void
__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  second_count++;
  if ((second_count%125) == 0) {
    led_change();
  }
} 

