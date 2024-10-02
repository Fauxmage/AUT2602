# Set MCU and tools
MCU = AVR128DB48
CC = /Applications/microchip/xc8/v2.41/bin/xc8-cc
PROGRAMMER = pkobn_updi
OBJCOPY = /Applications/microchip/xc8/v2.41/bin/avr-objcopy
DFP_PATH = /Applications/microchip/mplabx/v6.15/packs/Microchip/AVR-Dx_DFP/2.3.272/xc8
CFLAGS = -mcpu=$(MCU) -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem
LDFLAGS = -mcpu=$(MCU) -Wl,--gc-sections -Wl,--defsym=__MPLAB_BUILD=1 -Wl,--start-group -lm -Wl,--end-group
SRC = main.c
OBJ = $(SRC:.c=.o)
ELF = main.elf
HEX = main.hex

# Rules
all: $(HEX)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -mdfp=$(DFP_PATH) -c $< -o $@

$(ELF): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

$(HEX): $(ELF)
	$(OBJCOPY) -O ihex $< $@

flash: $(HEX)
	avrdude -p $(MCU) -c $(PROGRAMMER) -U flash:w:$(HEX):i

clean:
	rm -f $(OBJ) $(ELF) $(HEX)
