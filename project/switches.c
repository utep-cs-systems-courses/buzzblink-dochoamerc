#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "buzzer.h"
#include "libTimer.h"
extern int buttonState;
extern void playMLL(void);

void switches_init() {
  P1REN |= SWITCHES;		/* enables resistors for switches */
  P1IE |= SWITCHES;		/* enable interrupts from switches */
  P1OUT |= SWITCHES;		/* pull-ups for switches */
  P1DIR &= ~SWITCHES;		/* set switches' bits for input */
}

void switch_interrupt_handler()
{
  char p1val = P1IN;		/* switch is in P1 */
  
/* update switch interrupt sense to detect changes from current buttons */
  P1IES |= (p1val & SWITCHES);	/* if switch up, sense down */
  P1IES &= (p1val | ~SWITCHES);	/* if switch down, sense up */

/* up=red, down=green */
  if (!(p1val & SW1)) {          /* button pressed  */
    buttonState = 1;
  }

  switch(buttonState){
  case 0:
    break;
  case 1:
    playMLL();
    break;
  }
}

/* Switch on P1 (S2) */
void __interrupt_vec(PORT1_VECTOR) Port_1(){
  if (P1IFG & SWITCHES) {	      /* did a button cause this interrupt? */
    P1IFG &= ~SWITCHES;		      /* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */
  }
}

