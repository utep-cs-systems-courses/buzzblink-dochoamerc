#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "buzzer.h"
#include "musicPlayer.h"
#include "libTimer.h"
int buttonState = 0;     // tracker button press activation

static char
switch_update_interrupt_sense()
{
  char p2val = P2IN;  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);/* if switch down, sense up */
  return p2val;
}

void
switches_init()/* setup switch */
{
  P2REN |= SWITCHES;/* enables resistors for switches */
  P2IE = SWITCHES;/* enable interrupts from switches delete |=*/
  P2OUT |= SWITCHES;/* pull-ups for switches */
  P2DIR &= ~SWITCHES;/* set switches' bits for input */
}

void switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();		/* switch is in P2 */
  
/* up=red, down=green */
  if(buttonState == 0 && p2val & SW1 && p2val & SW2 && p2val & SW3 && p2val & SW4){
    buzzer_set_period(0);
    buttonState = 0;
  }
  else if (!(p2val & SW1)) {          /* 1 button pressed  */
    seconds = 0;
    buttonState = 1;
  }
  else if (!(p2val & SW2)) {          /* 2 button pressed  */
    seconds = 0;
    buttonState = 2;
  }
  else if (!(p2val & SW3)) {          /* 3 button pressed  */
    seconds = 0;
    buttonState = 3;
  }
  else if (!(p2val & SW4)) {          /* 4 button pressed  */
    seconds = 0;
    buttonState = 4;
  }  
  player();
}

/* Switch on P2 */
void
__interrupt_vec(PORT2_VECTOR) Port_2(){
if (P2IFG & SWITCHES) {      /* did a button cause this interrupt? */ 
  P2IFG &= ~SWITCHES;      /* clear pending sw interrupts */
    switch_interrupt_handler();/* single handler for all switches */
  }
}
