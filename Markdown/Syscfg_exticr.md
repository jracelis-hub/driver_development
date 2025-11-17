# Syscfg

The syscfg register for exti controls which **gpio port** will be configured for the corresponding interrupt

Where 

- gpiox_pin0 --> exti0
- gpiox_pin1 --> exti1
- gpiox_pin2 --> exti2
- gpiox_pin3 --> exti3
- gpiox_pin4 --> exti4
- gpiox_pin5_9 --> exti5_9
- gpiox_pin10-15 --> exti10-15

each `syscfg_exticr` holds 4 pins each
- `syscfg_exticr1` = 0 - 3
- `syscfg_exticr1` = 4 - 7
- `syscfg_exticr1` = 8 - 11
- `syscfg_exticr1` = 12 - 15

Then each 4 bit corresponds to the specific gpio port
- PA = 0000 = 0x0 = 0
- PB = 0001 = 0x1 = 1
- PC = 0010 = 0x2 = 2
- PD = 0011 = 0x3 = 3
- PE = 0100 = 0x4 = 4

So if I wanted to configure gpio port a pin 4 the pseudo code will be 
```
/* First clear the bits 
 * Note we are using cr2 because is the pin range of 4 - 7 
 * and it is modulo 16 because it can only be 0 4 8 12 */
syscfg->exticr2 &= ~(0xFU << (4 * gpio_handle->gpio_config.pin_number) % 16);
/* Then set the configuration for instance if we want pin 4 
 * It is shifted by 0 because the configuration for PA = 0x0
 */
syscfg->exticr2 |= (0x0U << (4 * gpio_handle->gpio_config.pin_number) % 16);

/* This is what it would look like if we wanted to configure gpiod */
syscfg->exticr2 |= (0x3U << (4 * gpio_handle->gpio_config.pin_number) % 16);
```
