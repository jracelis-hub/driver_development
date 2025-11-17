#include "spi_driver.h"

/* Clock Functions */
void spi_clock_enable(uint8_t spi_number)
{
	switch(spi_number)
	{
		case SPI1:
			rcc->apb2enr |= (0x1U << spi_number);
			break;
		case SPI2:
			rcc->apb1enr |= (0x1U << spi_number);
			break;
		case SPI3:
			rcc->apb1enr |= (0x1U << spi_number);
			break;
	}
}

void spi_clock_disable(uint8_t spi_number)
{
	switch(spi_number)
	{
		case SPI1:
			rcc->apb2enr &= ~(0x1U << spi_number);
			break;
		case SPI2:
			rcc->apb1enr &= ~(0x1U << spi_number);
			break;
		case SPI3:
			rcc->apb1enr &= ~(0x1U << spi_number);
			break;
	}
}

void spi_init(Spi_Handler_t *spi_handle)
{
	/* This is used to write all the bit configurations once done
	 * set the specific register = temp_reg */
	uint32_t temp_reg = 0;

	/* Configure Device Mode */
	temp_reg |= spi_handle->spi_config.spi_device_mode << 2;

	/* Configure the bus config */
	if (spi_handle->spi_config.spi_bus_config == SPI_BUS_CONFIG_FD)
	{
		/* Bidi mode should be cleared */
		temp_reg &= ~(1U << 15);
	}
	else if (spi_handle->spi_config.spi_bus_config == SPI_BUS_CONFIG_HD)
	{
		/* Bidi mode should be set */
		temp_reg &= ~(1U << 15);
	}
	else if (spi_handle->spi_config.spi_bus_config == SPI_BUS_CONFIG_SIMPLEX_RXONLY)
	{
		/* Bidi mode should be cleared */
		temp_reg &= ~(1U << 15);
		/* Rx only bit must be set */
		temp_reg |= ~(1U << 10);
	}

	temp_reg |= spi_handle->spi_config.spi_speed << 3;

	temp_reg |= spi_handle->spi_config.spi_dff << 11;

	temp_reg |= spi_handle->spi_config.spi_cpha << 0;

	temp_reg |= spi_handle->spi_config.spi_cpol << 1;

	temp_reg |= spi_handle->spi_config.spi_ssm

	/* Save the value into cr1 register */
	spi_handle->spi_base_address->cr1 = temp_reg;
}

/* This is a blocking call */
void spi_data_send(spi_registers_t *spi_base_addr, uint8_t *tx_buffer, uint32_t tx_buffer_size)
{
	while(tx_buffer_size > 0)
	{
		/* Wait until TXE flag is set meaning transfer can begin */
		while(spi_get_flag_status(spi_base_addr, SPI_TXE_FLAG) == FLAG_RESET);
		/* Check the DFF bit in CR1 */
		if (spi_base_addr->cr1 & (0x1U << SPI_CR1_DFF))
		{
			/* Load the data in to the Data Register */
			spi_base_addr->dr = *((uint16_t *)tx_buffer);
			tx_buffer_size -= 2;
			(uint16_t *)tx_buffer;
		}
		else
		{
			/* 8 bit DFF */
			spi_base_addr->dr = *tx_buffer;
			tx_buffer_size--;
			tx_buffer++;
		}
	}
}

static uint8_t spi_get_flag_status(spi_register *spi_addr, uint32_t flag_name)
{
	return flag_reset;
}
