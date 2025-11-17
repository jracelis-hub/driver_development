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
