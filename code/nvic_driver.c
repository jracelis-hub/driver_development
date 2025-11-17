#include "nvic_driver.h"

void nvic_irq_set(uint8_t irqn)
{
	if (irqn < 32)
	{
		nvic_iser->iser[0] |= (0x1U << irqn);
	}
	else if (irqn < 64)
	{
		nvic_iser->iser[1] |= (0x1U << (irqn % 32));
	}
	else if (irqn < 82)
	{
		nvic_iser->iser[2] |= (0x1U << (irqn % 32));
	}
}

void nvic_irq_clear(uint8_t irqn)
{
	if (irqn < 32)
	{
		*nvic_iser0 |= (0x1U << irqn);
	}
	else if (irqn < 64)
	{
		*nvic_iser1 |= (0x1U << (irqn % 32));
	}
	else if (irqn < 82)
	{
		*nvic_iser2 |= (0x1U << (irqn % 32));
	}
}

/* TODO */
void nvic_config_priority(uint8_t irqn, uint8_t priority)
{
		

}
