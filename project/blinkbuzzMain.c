#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"

int main(void) {
  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */

  led_init();
  buzzer_init();                /* initialize buzzer */
  switches_init();

  enableWDTInterrupts();	/* enable periodic interrupt */
  or_sr(0x18);			/* CPU off, GIE on */
}

// global state vars that control song and lights
int timeCount = 0; // state var representing repeating time 0…1s
int seconds = 0;  // state var representing repeating time 1…60s
int buttonState = 0; // tracker button press activation
char note = 0; // musical note tracker

void timeChange() {  // track time
  timeCount ++;
  if(timeCount % 50 == 0) seconds++; // increments every 1/5 sec
  if (timeCount >= 250) {  // once every second
    timeCount = 0;
  }
}

// calls necessary 
void playMLL() {
      timeChange();
      MLLNotes();
      MLLLights();
      soundSwitch(); 
}

void __interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  switch_interrupt_handler();
}
