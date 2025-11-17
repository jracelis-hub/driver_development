#ifndef SYSCFG_DRIVER_H
#define SYSCFG_DRIVER_H

#include "gpio_driver.h"

void syscfg_clock_enable(void);
void syscfg_clock_disable(void);
uint8_t syscfg_get_gpiox(gpio_registers_t *gpiox);

#endif /* SYSCFG_DRIVER_H */
