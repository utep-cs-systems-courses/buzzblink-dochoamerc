#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"

int main(void) {
  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */

  switches_init();              /* initialize switches */
  buzzer_init();                /* initialize buzzer */
  led_init();                   /* initialize LEDs */

  enableWDTInterrupts();	/* enable periodic interrupt */
  or_sr(0x18);			/* CPU off, GIE on */
}


void __interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  switch_interrupt_handler();
}
