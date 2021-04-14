# makfile configuration
COMMON_OBJECTS  = 
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../../demos/h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: toy.elf 

#additional rules for files
toy.elf: ${COMMON_OBJECTS} p1_interrupt_handler.o led.o switches.o buttonMain.o buzzer.o wdInterruptHandler.o stateMachines.o function.o ../../demos/lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: toy.elf
	msp430loader.sh toy.elf

clean:
	rm -f *.o *.elf *~ *#

function.o: stateMachines.h
buttonMain.o: buttonMain.c

led.o: led.c led.h

buzzer.o: buzzer.c buzzer.h

switches.o: switches.c switches.h

stateMachines.o: stateMachines.c stateMachines.h

p1_interrupt_handler.o: p1_interrupt_handler.c

wdInterruptHandler.o: wdInterruptHandler.c buzzer.h led.h switches.h stateMachines.h


