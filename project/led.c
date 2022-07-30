#include <msp430.h>
#include "led.h"
#include "timer.h"

void led_init() {
    P1DIR |= LEDS;
    P1OUT &= ~LEDS; // start off
}

// lights for Mary had a Little Lamb
void MLLLights() {
  switch(note) {
  case 'a':
    P1OUT |= LED_GREEN;
    P1OUT &= ~LED_RED;
    break;
  case 'c':
    P1OUT ^= LED_GREEN;
    P1OUT ^= LED_RED;
    break;
  case 'f':
    P1OUT ^= LED_GREEN;
    P1OUT ^= LED_RED;
    break;
  case 'g':
    P1OUT |= LED_RED;
    P1OUT &= ~LED_GREEN;
    break;
  default:
    P1OUT &= ~LED_GREEN;
    P1OUT &= ~LED_RED;
    break;
  }
}

// lights for Siren
void sirenLED() {
  switch(seconds){
  case 0:
    P1OUT &= ~LED_GREEN;
    P1OUT &= ~LED_RED;
    break;
  case 10:
    P1OUT &= ~LED_GREEN;
    P1OUT |= LED_RED;
    break;
  case 20:
    P1OUT |= LED_GREEN;
    P1OUT &= ~LED_RED;
    break;
  case 30:
    P1OUT &= ~LED_GREEN;
    P1OUT &= ~LED_RED;
    break;
  default:
    note = 0;
    break;
  }  
}

// lights for 
void song3LED() {
  switch(note) {
  case 'a':
    P1OUT |= LED_GREEN;
    P1OUT &= ~LED_RED;
    break;
  case 'b':
    P1OUT |= LED_GREEN;
    P1OUT |= LED_RED;
    break;
  case 'c':
    P1OUT &= ~LED_GREEN;
    P1OUT |= LED_RED;
    break;
  default:
    P1OUT &= ~LED_GREEN;
    P1OUT &= ~LED_RED;
    break;
  }
}

// lights for 
void song4LED() {
  dimmer();
}
