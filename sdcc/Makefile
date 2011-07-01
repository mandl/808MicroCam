# Usually SDCC's small memory model is the best choice.  If
# you run out of internal RAM, you will need to declare
# variables as "xdata", or switch to large model

SDCCCFLAGS = --model-small

ASLINKFLAGS = --data-loc 0x30 --xram-loc 0x6000


# file) to build the .rel file.

%.rel : %.c %.h
	sdcc $(SDCCCFLAGS) -c $<


all: blink.hex



blink.hex: blink.c delay_ms.rel
	sdcc $(SDCCCFLAGS) $(ASLINKFLAGS) $^
	packihx blink.ihx > blink.hex
	avr-objcopy  -I ihex -O binary blink.hex blink.bin


clean:
	rm -f blink.asm delay_ms.asm
	rm -f *.hex *.ihx *.lnk *.lst *.map *.rel *.rst *.sym *.mem

upload:all
	./ISP808 blink.bin
	
