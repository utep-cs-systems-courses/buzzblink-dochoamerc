#ifndef timer_included
#define timer_included

// global state vars that control song and lights
int timeCount; // state var representing repeating time 0…1s
int seconds;  // state var representing repeating time 1…60s
int blinkLimit;
int blinkCount;

void timeChange();
void dimmer();

#endif
