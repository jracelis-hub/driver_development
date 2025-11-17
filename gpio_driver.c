#include "gpio_driver.h"
#include "syscfg_driver.h"

/********************************************************************************
* @function: To enable peripheral clock of given gpio port
*
* @param:    1. Use GPIO_PORT_X macro found in gpio_driver.h
*********************************************************************************/

void gpio_clock_enable(uint8_t gpio_port)
{
	rcc->ahb1enr |= (0x1U << gpio_port);
}

/********************************************************************************
* @function: To disable peripheral clock of given gpio port
*
* @param:    1. Use GPIO_PORT_X macro found in gpio_driver.h
*********************************************************************************/

void gpio_clock_disable(uint8_t gpio_port)
{
	rcc->ahb1enr &= ~(0x1U << gpio_port);
}

/********************************************************************************
* @function: To initialize gpio registers with given gpio configurations
*
* @param:    1. gpio_handle holds address of gpio port and gpio pin configurations
*********************************************************************************/

void gpio_init(gpio_handle_t *gpio_handle)
{
	/* Clear the mode of the gpio pin */
	gpio_handle->gpiox->moder &= ~(0x3U << (2 * gpio_handle->gpio_config.pin_number));
	
	if (gpio_handle->gpio_config.mode != GPIO_MODE_INPUT)
	{
		/* Set the mode of the gpio pin */
		gpio_handle->gpiox->moder |= (gpio_handle->gpio_config.mode << (2 * gpio_handle->gpio_config.pin_number));

		/* Clear the output type of the gpio pin */
		gpio_handle->gpiox->otyper &= ~(0x1U << gpio_handle->gpio_config.pin_number);
		if (gpio_handle->gpio_config.o_type == GPIO_OTYPE_OPEN_DRAIN)
		{
			/* Set the output type of the gpio pin */
			gpio_handle->gpiox->otyper |= (gpio_handle->gpio_config.o_type << (gpio_handle->gpio_config.pin_number));
		}

		/* Clear the speed register of the gpio pin */
		gpio_handle->gpiox->ospeedr &= ~(0x3U << (2 * gpio_handle->gpio_config.pin_number));
		if (gpio_handle->gpio_config.o_speed != GPIO_OSPEED_LOW)
		{
			/* Set the output speed of the gpio pin */
			gpio_handle->gpiox->ospeedr |= (gpio_handle->gpio_config.o_speed << (2 * gpio_handle->gpio_config.pin_number));
		}

		if (gpio_handle->gpio_config.mode == GPIO_MODE_ALT_FUNC)
		{
			if (gpio_handle->gpio_config.pin_number < 8)
			{
				/* Clear the alternate function register of the gpio pin */
				gpio_handle->gpiox->afrl &= ~(0xFU << (4 * gpio_handle->gpio_config.pin_number));

				/* Set the alternate function register of the gpio pin */
				gpio_handle->gpiox->afrl |= (gpio_handle->gpio_config.alt_func_low << (4 * gpio_handle->gpio_config.pin_number));
			}
			else
			{
				/* Clear the alternate function register of the gpio pin */
				gpio_handle->gpiox->afrh &= ~(0xFU << ((4 * gpio_handle->gpio_config.pin_number) % 32));

				/* Set the alternate function register of the gpio pin 
				 * Since each pin requires 4 bits the pin number is multipled by 4 
				 * For AF High the next register starts at 16 but in order to shift the registers they need to be from 0 - 31 
				 * if it is 4 * 16 = 64 % 32 = 0 therefore shifting within the specifications                              */
				gpio_handle->gpiox->afrh |= (gpio_handle->gpio_config.alt_func_high << ((4 * gpio_handle->gpio_config.pin_number) % 32));
			}
		}
	}
	else
	{
		if (gpio_handle->gpio_config.mode == GPIO_MODE_IT_FT)
		{
			/* Configure the FTSR */
			exti->ftsr |= (0x1U << gpio_handle->gpio_config.pin_number);

			/* Clear the RTSR to ensure only FTSR is configured */
			exti->rtsr &= ~(0x1U << gpio_handle->gpio_config.pin_number);
		}
		else if (gpio_handle->gpio_config.mode == GPIO_MODE_IT_RT)
		{
			/* Configure the RTSR */
			exti->rtsr |= (0x1U << gpio_handle->gpio_config.pin_number);

			/* Clear the FTSR to ensure only RTSR is configured */
			exti->ftsr &= ~(0x1U << gpio_handle->gpio_config.pin_number);
		}
		else if (gpio_handle->gpio_config.mode == GPIO_MODE_IT_FTRT)
		{
			/* Configure the FTSR and RTSR */
			exti->ftsr |= (0x1U << gpio_handle->gpio_config.pin_number);
			exti->rtsr |= (0x1U << gpio_handle->gpio_config.pin_number);
		}


		/* Calculate which control register of which the gpio pin is in and divide 
		 * by 4 since there 4 control registers.                               */
		uint8_t exti_range = gpio_handle->gpio_config.pin_number / 4;
		uint8_t gpio_port = syscfg_get_gpiox(gpio_handle->gpiox);

		/* Enable the clock for syscfg */
		syscfg_clock_enable();
		syscfg->exticr[exti_range] = (gpio_port << (4 * gpio_handle->gpio_config.pin_number) % 16);

		/* Enable the exti interrupt delivery using IMR */
		exti->imr |= (0x1U << gpio_handle->gpio_config.pin_number);
	}

	/* Clear the pull up/down pin configuration */
	gpio_handle->gpiox->pupdr &= ~(0x3U << (2 * gpio_handle->gpio_config.pin_number));
	if (gpio_handle->gpio_config.pup_pdown != GPIO_PULL_UPDOWN_NONE)
	{
		/* Set the gpio pin to either pull up or pull down */
		gpio_handle->gpiox->pupdr |= (gpio_handle->gpio_config.pup_pdown << (2 * gpio_handle->gpio_config.pin_number));
	}
}

/********************************************************************************
* @function: To atomic write to odr using the bit set/reset register to 
*            write(set) or reset(clear) output data register
*
* @param:    1. *gpiox the gpio port address to access specific registers
*            2. pin_number the pin number that you are trying to write to
*            3. data either SET or CLEAR the output data register (odr)
*
* @comment:  There are two ways to write into the output data register (odr)
*            1. By directly reading and writing into the odr
*            2. Using atomic operation of bssr to toggle the odr
*********************************************************************************/

void gpio_write_to_odr(gpio_registers_t *gpiox, uint8_t pin_number, uint8_t data)
{
	if (data == BSRR_SET)
	{
		gpiox->bsrr |= (0x1U << (pin_number));
	}
	else
	{
		gpiox->bsrr |= (0x1U << (16 + pin_number));
	}
}

/********************************************************************************
* @function: To read from the idr (input data register) of the gpio in input mode
*
* @param:    1. *gpiox the gpio port address to access specific registers
*            2. pin_number the pin number that you are trying to write to
*
* @return:   data is high (1) if input received or low (0) if no input
*********************************************************************************/

uint8_t gpio_read_from_idr(gpio_registers_t *gpiox, uint8_t pin_number)
{
	return ((gpiox->idr & (0x1U << pin_number))) ? 1 : 0;
}
