PROJECT=Frobit

SOURCES=main.c src/adc.c src/buffer.c src/control.c  src/frobit.c src/hall.c src/led.c src/nmea.c src/RCOS.c src/timer0.c src/timer2.c src/uart.c 

MMCU=atmega168p

CC=avr-gcc



CFLAGS= -mmcu=$(MMCU) -Wall -g2 -DF_CPU=16000000UL -MMD -MP -gstabs -O0 -std=gnu99 -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields



default:

	@echo ""

	@echo "make clean......delete object & hex files"

	@echo "make hex........build the $(PROJECT).hex file"

	@echo "make flash......copy $(PROJECT).hex to RoboCard flash"

	@echo ""



hex: $(PROJECT).elf

#	avr-objcopy -j .text -O ihex $(PROJECT).elf $(PROJECT).hex
	avr-objcopy -R .eeprom -O ihex Frobit.elf  "Frobit.hex"



$(PROJECT).elf: $(SOURCES)

#$(CC) $(CFLAGS) -I./ -o $(PROJECT).elf $(SOURCES) 
	avr-gcc -Wl,-Map,Frobit.map -mmcu=atmega168p -o "Frobit.elf"  $(SOURCES)

flash: $(PROJECT).hex

	sudo avrdude -p m168 -c avrispmkII -P usb -F -v -U flash:w:$(PROJECT).hex



# The following lines are a few examples of parameters for avrdude

# when using an ISP programmer. Remember that some of them need a

# -P option to define the serial port they use.

#       avrdude -p m88 -c avrisp2 -P /dev/tty.PL2303-00001004 -F -U flash:w:$(PROJECT).hex

#       avrdude -p m88 -c usbtiny -F -U flash:w:$(PROJECT).hex



clean:

	rm -f $(PROJECT).elf $(PROJECT).hex