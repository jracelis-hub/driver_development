CC=arm-none-eabi-gcc 
STD=-std=gnu11
WFLAGS=-Wall
INC=-I./Include
FLAGS=$(STD) $(WFLAGS) $(INC)

SRC= gpio_driver.c syscfg_driver.c nvic_driver.c
OBJ= gpio_driver.o syscfg_driver.o nvic_driver.o

.PHONY = clean

all: $(OBJ)

%.o:%.c
	$(CC) -c $< -o $@ $(FLAGS)

clean:
	rm $(OBJ)	
