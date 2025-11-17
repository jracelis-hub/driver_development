# Driver Development

A bare metal driver development for STM32F407 Discovery board. It is written in C and implementing a bare metal driver from scratch without using a HAL (Hardware Abstraction Layer). This is learning process to understand how to configure each hardware peripheral within the microcontroller, without the overhead of abstraction.

## Tools

Software
- STM32CubeIDE - to test code on microcontroller and utilize the debugger to step through registers.
- `arm-none-eabi-gcc` - to compile code ensuring compliance before using in STM32CubeIDE
- `make` - automate build process

Hardware
- STM32F407 Discovery Board
- Micro USB B Cable
- Logic Analyzer (24 MHz)
- Digital Multimeter

## Files

Header Files
- `memory_map_driver.h` - holds the stm32407 memory mapped core and peripheral registers
- `gpio_driver.h` - used to configure gpios and holds structures of gpios
- `nvic_driver.h` - used to configure nvic interrupts and specific functions
- `syscfg_driver.h` - used to configure exti (extended interrupts) for gpios

Source Files
- `gpio_driver.c` - source code of gpios
- `nvic_driver.c` - source code of nvic
- `syscfg_driver.c` - source code of syscfg
