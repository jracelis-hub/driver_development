#include "syscfg_driver.h"

void syscfg_clock_enable(void)
{
	rcc->apb2enr |= (0x1U << 14);
}

void syscfg_clock_disable(void)
{
	rcc->apb2enr &= ~(0x1U << 14);
}

uint8_t syscfg_get_gpiox(gpio_registers_t *gpiox)
{
	return (gpiox == gpioa) ? GPIO_PORT_A :
	       (gpiox == gpiob) ? GPIO_PORT_B :
		   (gpiox == gpioc) ? GPIO_PORT_C :
		   (gpiox == gpiod) ? GPIO_PORT_D :
		   (gpiox == gpioe) ? GPIO_PORT_E : -1;
}
