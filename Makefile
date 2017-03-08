CC=avr-gcc
OBJCOPY=avr-objcopy
AVRDUDE=avrdude

CFLAGS=-Os -D F_CPU=8000000UL -mmcu=atmega328p

PORT=/dev/cu.usbmodem1411
DEVICE=atmega328p
PROGRAMMER=stk500v1
RATE=19200

main.hex: main.elf
	${OBJCOPY} -O ihex -R .eeprom main.elf main.hex

main.elf: main.o
	${CC} -o main.elf main.o

main.o: main.c
	${CC} ${CFLAGS} -c main.c

install: main.hex
	${AVRDUDE} -v -c ${PROGRAMMER} -p ${DEVICE} -P ${PORT} -b ${RATE} -Uflash:w:main.hex

fuses:
	${AVRDUDE} -v -c ${PROGRAMMER} -p ${DEVICE} -P ${PORT} -b ${RATE} -U lfuse:w:0xe2:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m

clean:
	rm main.hex main.elf main.o