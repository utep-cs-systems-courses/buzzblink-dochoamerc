#include <msp430.h>
#include "stateMachines.h"
#include "led.h"

char toggle_red()		/* always toggle! */
{
  static char state = 0;

  switch (state) {
  case 0:
    red_on = 1;
    state = 1;
    break;
  case 1:
    red_on = 0;
    state = 0;
    break;
    } 
  return 1;			/* always changes an led */
}

char toggle_green()	/* only toggle green if red is on!  */
{
  char changed = 0;
  //if (red_on) {
    green_on ^= 1;
    changed = 1;
    //}
  return changed;
}

void switchState()
{
  static char state = 0;

  switch(state) {
  case 0:
    state = 1;
    if(green_on) toggle_green();
    if(red_on) toggle_red();
    break;
  case 1:
    state = 2;
    //    toggle_green();
    toggle_red();
    break;
  case 2:
    state = 3;
    toggle_green();
    toggle_red();
    break;
  case 3:
    state = 0;
    //toggle_green();
    toggle_red();
    break;
  }
}

void state_advance()		/* alternate between toggling red & green */
{
  /*  char changed = 0;  

  static enum {R=0, G=1} color = G;
  switch (color) {
  case R: changed = toggle_red(); color = G; break;
  case G: changed = toggle_green(); color = R; break;
  }
  */
  switchState();
  led_changed =1;// changed;
  led_update();
}



