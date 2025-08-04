CC=arm-none-eabi-gcc
COMPILE_FLAGS= -c -Wall -Werror -Wno-unused-function
CORTEX_M4=-mcpu=cortex-m4 -mthumb
SRC= $(wildcard \
    src/kernel/*.c \
	src/libs/*.c)

INC= \
    -Isrc \
	-Isrc/kernel \
	-Isrc/libs \
	-Isrc/targets/arm

build-kernel:
	$(CC) $(COMPILE_FLAGS) $(INC) $(SRC) $(CORTEX_M4)

clean:
	rm -rf *.o
	rm -rf *.elf
	rm -rf *.hex

flash-stm:
	@echo "Flashing STM32..."

