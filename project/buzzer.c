#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
extern int seconds;
extern char note;
extern int buttonState;

void buzzer_init()
{
  /* 
       Direct timer A output "TA0.1" to P2.6.  
        According to table 21 from data sheet:
          P2SEL2.6, P2SEL2.7, anmd P2SEL.7 must be zero
          P2SEL.6 must be 1
        Also: P2.6 direction must be output
  */
  timerAUpmode();/* used to drive speaker */
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  P2DIR = BIT6;/* enable output to speaker (P2.6) */
}

void soundSwitch() { // calls buzzer_set_period with value per musical note
  switch(note){
  case 'a':
    buzzer_set_period(560);
    break;
  case 'c':
    buzzer_set_period(475);
    break;
  case 'g':
    buzzer_set_period(630);
    break;
  case 'f': 
    buzzer_set_period(750);
    break;
  default:
    buzzer_set_period(0);
  }
}

// Mary had a little lamb switch of note per time
void MLLNotes() {
  switch(seconds) {
  case 0: case 8: case 10: case 12: case 24: case 32: case 40: case 42: case 44: case 48: case 54:
    note = 'a';
    break;
  case 2: case 6: case 16: case 18: case 20: case 34: case 38: case 50: case 52: case 56:
    note = 'g';
    break;
  case 4: case 36: case 58: case 59: case 60:
    note = 'f';
    break;
  case 26: case 28:
    note = 'c';
    break;
  case 65: // song over: resets button, note, and time
    buttonState = 0;
    note = 0;
    seconds = 0;
    break;
  default:
    note = 0;
    break;
  }
}

void buzzer_set_period(short cycles) /* buzzer clock = 2MHz.  (period of 1k results in 2kHz tone) */
{
  CCR0 = cycles;
  CCR1 = cycles >> 1;/* one half cycle */
}
