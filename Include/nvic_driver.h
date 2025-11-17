#ifndef NVIC_DRIVER_H
#define NVIC_DRIVER_H

#include "memory_map_driver.h" 

void nvic_irq_set(uint8_t irqn);
void nvic_irq_clear(uint8_t irqn);

#endif /* NVIC_DRIVER_H */
