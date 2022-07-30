#ifndef buzzer_included
#define buzzer_included

void buzzer_init();
void song4Notes();
void song3Notes();
void sirenNotes();
void MLLNotes();
void soundSwitch();
void buzzer_set_period(short cycles);

char note; // musical note tracker

extern int seconds, buttonState;

#endif // included
