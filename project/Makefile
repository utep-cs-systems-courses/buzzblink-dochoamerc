# makfile configuration
COMMON_OBJECTS  = buzzer.o switches.o led.o blinkbuzzMain.o 
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -Ih/
LDFLAGS 	= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all:	
	(cd timerLib && make install)
	(make blinkbuzz.elf)

#additional rules for files
blinkbuzz.elf: ${COMMON_OBJECTS} lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: blinkbuzz.elf
	msp430loader.sh  $^

clean: $^
	rm -f *.o *.elf
	rm -rf h lib

buzzer.c: buzzer.h
led.c: led.h
switches.c: switches.h
blinkbuzzMain.c: buzzer.h led.h switches.h
wdInterruptHandler.o: led.h
