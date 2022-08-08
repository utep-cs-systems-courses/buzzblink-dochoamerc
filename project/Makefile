# makfile configuration
COMMON_OBJECTS  = buzzer.o timer.o switches.o led.o blinkbuzzMain.o 
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -Ih/
LDFLAGS 	= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all:	
	(cd timerLib && make install)
	(make blinkbuzz-c.elf)
	(make blinkbuzz-s.elf)

#additional rules for files
blinkbuzz-c.elf: ${COMMON_OBJECTS} musicPlayer-c.o lib/libTimer.a
	${CC} -s ${CFLAGS} ${LDFLAGS} -o $@ $^

blinkbuzz-s.elf: ${COMMON_OBJECTS} musicPlayer-s.o lib/libTimer.a
	${CC} -s ${CFLAGS} ${LDFLAGS} -o $@ $^

load-c: blinkbuzz-c.elf
	msp430loader.sh $^

load-s: blinkbuzz-s.elf
	msp430loader.sh $^


clean: $^
	rm -f *.o *.elf
	rm -rf h lib

buzzer.o: buzzer.h
led.o: led.h
switches.o: switches.h
timer.o: timer.h
musicPlayer-s.o: musicPlayer.h
blinkbuzzMain.o: buzzer.h led.h switches.h
wdInterruptHandler.o: led.h
