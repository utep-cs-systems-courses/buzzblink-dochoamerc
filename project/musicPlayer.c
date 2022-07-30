#include <msp430.h>
#include "libTimer.h"
#include "timer.h"
#include "buzzer.h"
#include "led.h"
#include "switches.h"
#include "musicPlayer.h"

// calls necessary 
void playMLL() {
  timeChange();
  MLLNotes();
  MLLLights();
  soundSwitch(); 
}

void playSiren() {
  timeChange();
  sirenNotes();
  sirenLED();
  soundSwitch();
}

void play3() {
  timeChange();
  song3Notes();
  song3LED();
  soundSwitch(); 
}

void play4() {
  timeChange();
  song4Notes();
  song4LED();
  soundSwitch(); 
}

void player() {
switch(buttonState) {
  case 1:
    playMLL();
    break;
  case 2:
    sirenLED();
    break;
  case 3:
    //    superMarioTheme();
    play3();
    break;
  case 4:
    play4();
    break;
  default:
    buttonState = 0;
    buzzer_set_period(0);
    break;
  }
}
