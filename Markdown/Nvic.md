# Vector Table

The vector table is broken into two different exceptions
1. System exceptions 0 - 15
2. Interrupts (IRQs) 16 - 240

IRQn (Interrupt Request Numbers) start at 0

> Total 256

Two configurations for priority:
1. Settable priority
	- 4 - 240
2. Unsettable priority 
	- 0 - 3

Startup file defines Reset_Handler
- Written in .c C inline
- Written in .s Assembly 

Vector Table (Global Array)

Written in Assembly
```
g_vectors:
	.word _estack                0x0000 0000
	.word Reset_Handler          0x0000 0004
	.word NMI_Handler            0x0000 0008
	.word HardFault_Handler      0x0000 000C
```

Written in C
```
uint32_t vector_table[] __attribute__(section(.isr_table))
{
	STACK,
	uint32_t Reset_Handler
}
```

Interrupt Handlers are attributated as weak. Weak means the implementation can be overwritten in source files.
- Once triggered will jump to implementation

Whats the design to implement interrupts?

Section 12 Interrupts
- Has a external interrupt controller `EXTI`
	- Used with other peripherals
	- Used with GPIOs

> Refer to 12.2.5 in Reference Manual

This is the designed for ST
```
peripheral ---> NVIC

other peripherals ---> EXTI ---> NVIC
```

For an example PA0 is connected to EXTI0 interrupt, so anything configured at PA0 you used the EXTI0_Handler in the vector table

Button interrupt:
1. Button is connected to a GPIO pin of microcontroller
2. GPIO pin should be configured to input mode
3. The link between GPIO port and the relevant EXTI line must be established using the `SYSCFG_EXTICRx` register
4. Configure the trigger getection (falling/rising/both) for relevant EXTI line
5. Implement the handler to service the interrupt

EXTI Lines
```

GPIO Button ---> EXTI Controller ---> EXTI Lines 1 --
                                                    |            
													----------> |\ 
													            | | ---> NVIC <---> CPU
                                                    ----------> |/
                                                    |           
                                                    |
                 EXTI Pending Register --------------
```                          
- EXTI Pending Register has to be clear by the Programmer by masking with `1 << LOCATION`
	- Since it is always 1 it will always provide an interrupt

## NVIC

Nested Vectored Interrupt Controller (NVIC) is found in the processor core document (Cortex M4 Generic Guide)

There is a memory map of registers for NVIC 

To configure the proper Interrupt Request Number (IRQn) go to the registers `NVIC_ISER0 - NVIC_ISER7`

- `NVIC_ISER` stands for (N)ested (V)ectored (I)nterrupt (C)ontroller (I)nterrupt (S)et (E)nable (R)egister
	- Uses to set (enable) the IRQn
- `NVIC_ICER` stands for (N)ested (V)ectored (I)nterrupt (C)ontroller (I)nterrupt (C)lear (E)nable (R)egister
	- Uses to clear (disable) the IRQn
- `NVIC_IPR` stands for (N)ested (V)ectored (I)nterrupt (C)ontroller (I)nterrupt (P)riority (R)egister
	- Use to set priority level of IRQn

The `NVIC_IPR` is different from SCB (System Control Block) which deals with exceptions not IRQs!

> [!NOTE]
> Depending on the processor core each IRQn may vary based on each core specifications. Refer to the Generic User Guide on that device.

where each 32 bit register corresponds the IRQn

`NVIC_ISER0` = 0 - 32 bit or 
- Bit 0 = IRQn 0
- Bit 1 = IRQn 1

> It is important to not that `NVIC_ISER0` can only be written to, so when trying to disable that specific IRQn used `NVIC_ICER`

`NVIC_IPR` holds 4 IRQs per register. This means each IRQ holds 8 bits in a register
```
-------------------------------------
|  IRQ3  |  IRQ2  |  IRQ1  |  IRQ0  |
-------------------------------------
  8 bits
```
`NVIC_IPR0 - NVIC_IPR59`

For instance if trying to configure IRQn 239
- `NVIC_IPRn = IRQn / 4 = 59` rounded down

That means the register will be `NVIC_IPR59` 
- `NVIC_IPRn % 4 = position = 3 * 8 = 24`
- Mulitple by 8 because each bit field is 8 bits long

> Note: Only the last 4 bits of each bit field is configurable

- 0x0 = 0
- 0x1 = 1
- 0x...
- 0xF = 15

So `position = NVIC_IPRn % 4 * 8 + 4`
```
*nvic_ipr59 |= (0x1U << ((239 % 4) * 8 + 4));
                         (3) * 8 + 4)
						 24 + 4
/* This is priorty of 1 */
*nvic_ipr59 |= (0x1U << (28));
*nvic_ipr59 = 0001 0000 0000 0000 0000 0000 0000 0000
                28   24    20  16   12    8    4    0
```
