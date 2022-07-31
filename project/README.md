This program can be compiled with the "make" instruction. 

To clean - "make clean"
To run - "make load"

It will notice button presses.

S1 - plays Mary had a Little Lamb and flashes lights with each new tone. If the button is pressed in the middle of the song, it will restart the song. 
S2 - should play its own tone, however on my MSP430, it gets stuck on the beginning tone with this button. I am unsure what is wrong, I can tell that the machine notices other button presses, but only changes to the other songs after pressing those buttons several times. 
S3 - plays another song, has the lights flash appropriately, just a short tune. 
S4 - plays another random tune. The LEDs slowly dim green and brighten red.

To stop music, press top reset button. (This only works for buttons S1, S3, and S4).
