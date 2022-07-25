#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "led.h"

int main() {
  P1DIR |= LEDS;
  P1OUT &= ~LED_GREEN;
  P1OUT |= LED_RED;
  configureClocks();
  buzzer_init();
 //  buzzer_set_period(3000);	/* start buzzing!!! 2MHz/1000 = 2kHz*/
  
  //  configureClocks();/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();/* enable periodic interrupt */
  
  or_sr(0x18);          // CPU off, GIE on
}

int secondCount = 0;
int note = 0;

void
__interrupt_vec(WDT_VECTOR) WDT()/* 250 interrupts/sec */
{
  secondCount ++;
 
  switch(note){
  case 0:
    buzzer_set_period(1000);/* start buzzing!!! 2MHz/1000 = 2kHz*/
    break;
  case 1:
    buzzer_set_period(3000);/* start buzzing!!! 2MHz/1000 = 2kHz*/
    break;
  default:
    if(secondCount >= 125)
      note |= 1;
    if(secondCount >= 250) {
      secondCount = 0;
      P1OUT ^= LED_GREEN;
    }
  }
  
 }
