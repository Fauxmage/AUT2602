# Set MCU and tools
MCU = AVR128DB48
CC = /Applications/microchip/xc8/v2.41/bin/xc8-cc
PROGRAMMER = pkobn_updi
OBJCOPY = /Applications/microchip/xc8/v2.41/bin/avr-objcopy
DFP_PATH = /Applications/microchip/mplabx/v6.15/packs/Microchip/AVR-Dx_DFP/2.3.272/xc8
#CFLAGS = -mcpu=$(MCU) -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem

# Compiler and linker flags
CFLAGS = -mcpu=$(MCU) -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common \
         -funsigned-char -funsigned-bitfields -Wall -mconst-data-in-progmem \
         -mno-const-data-in-config-mapped-progmem -mdfp=$(DFP_PATH)

LDFLAGS = -mcpu=$(MCU) -Wl,--gc-sections -Wl,--defsym=__MPLAB_BUILD=1 -Wl,--start-group \
          -lm -Wl,--end-group

# Source files
SRC = main.c usart.c adc.c

# Object files
OBJ = $(SRC:.c=.o)

# Output files
ELF = main.elf
HEX = main.hex

# Default target
all: $(HEX)

# Compile each .c file into .o object file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files into the final .elf executable
$(ELF): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $@

# Convert the .elf file to .hex format for flashing
$(HEX): $(ELF)
	$(OBJCOPY) -O ihex $< $@

# Flash the microcontroller using avrdude
flash: $(HEX)
	avrdude -p $(MCU) -c $(PROGRAMMER) -U flash:w:$(HEX):i
# Clean up generated files
clean:
	rm -f $(OBJ) $(ELF) $(HEX)

