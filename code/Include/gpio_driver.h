#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include "memory_map_driver.h"

/***************************************************************************************************
* Type:     GPIO Port Number               
****************************************************************************************************/

#define BSRR_RESET                    (0x0U)
#define BSRR_SET                      (0x1U)

/***************************************************************************************************
* Type:     GPIO Port Number               
****************************************************************************************************/

#define GPIO_PORT_A                   (0x0U)
#define GPIO_PORT_B                   (0x1U)
#define GPIO_PORT_C                   (0x2U)
#define GPIO_PORT_D                   (0x3U)
#define GPIO_PORT_E                   (0x4U)

/***************************************************************************************************
* Type:     GPIO Pin Number               
****************************************************************************************************/

#define GPIO_PIN_0                    (0x0U)
#define GPIO_PIN_1                    (0x1U)
#define GPIO_PIN_2                    (0x2U)
#define GPIO_PIN_3                    (0x3U)
#define GPIO_PIN_4                    (0x4U)
#define GPIO_PIN_5                    (0x5U)
#define GPIO_PIN_6                    (0x6U)
#define GPIO_PIN_7                    (0x7U)
#define GPIO_PIN_8                    (0x8U)
#define GPIO_PIN_9                    (0x9U)
#define GPIO_PIN_10                   (0xAU)
#define GPIO_PIN_11                   (0xBU)
#define GPIO_PIN_12                   (0xCU)
#define GPIO_PIN_13                   (0xDU)
#define GPIO_PIN_14                   (0xEU)
#define GPIO_PIN_15                   (0xFU)

/***************************************************************************************************
* Type:     Mode Options             
* Section:  8.4.1 GPIO Port Mode Options
* Location: Reference Manual on page 284 
****************************************************************************************************/

#define GPIO_MODE_INPUT               (0x0U)
#define GPIO_MODE_OUTPUT              (0x1U)
#define GPIO_MODE_ALT_FUNC            (0x2U)
#define GPIO_MODE_ANALOG              (0x3U)
#define GPIO_MODE_IT_FT               (0x4U)
#define GPIO_MODE_IT_RT               (0x4U)
#define GPIO_MODE_IT_FTRT             (0x4U)

/***************************************************************************************************
* Type:     Output Type Options
* Section:  8.4.2 GPIO Port Output Type 
* Location: Reference Manual on page 284 
****************************************************************************************************/

#define GPIO_OTYPE_PUSH_PULL          (0x0U)
#define GPIO_OTYPE_OPEN_DRAIN         (0x1U)

/***************************************************************************************************
* Type:     Output Speed Options
* Section:  8.4.3 GPIO Port Output Speed 
* Location: Reference Manual on page 285 
****************************************************************************************************/

#define GPIO_OSPEED_LOW               (0x0U)
#define GPIO_OSPEED_MEDIUM            (0x1U)
#define GPIO_OSPEED_HIGH              (0x2U)
#define GPIO_OSPEED_VERY_HIGH         (0x3U)

/***************************************************************************************************
* Type:     Pull-up Pull Down Options
* Section:  8.4.4 GPIO Port Pull-up Pull-Down 
* Location: Reference Manual on page 285 
****************************************************************************************************/

#define GPIO_PULL_UPDOWN_NONE         (0x0U)
#define GPIO_PULL_UP                  (0x1U)
#define GPIO_PULL_DOWN                (0x2U)

/***************************************************************************************************
* Type:     Alternate Function Options
* Section:  8.4.9 GPIO Alternate Function 
* Location: Reference Manual on page 288 - 289
****************************************************************************************************/

#define GPIO_ALT_FUNC_0               (0x0U)
#define GPIO_ALT_FUNC_1               (0x1U)
#define GPIO_ALT_FUNC_2               (0x2U)
#define GPIO_ALT_FUNC_3               (0x3U)
#define GPIO_ALT_FUNC_4               (0x4U)
#define GPIO_ALT_FUNC_5               (0x5U)
#define GPIO_ALT_FUNC_6               (0x6U)
#define GPIO_ALT_FUNC_7               (0x7U)
#define GPIO_ALT_FUNC_8               (0x8U)
#define GPIO_ALT_FUNC_9               (0x9U)
#define GPIO_ALT_FUNC_10              (0xAU)
#define GPIO_ALT_FUNC_11              (0xBU)
#define GPIO_ALT_FUNC_12              (0xCU)
#define GPIO_ALT_FUNC_13              (0xDU)
#define GPIO_ALT_FUNC_14              (0xEU)
#define GPIO_ALT_FUNC_15              (0xFU)

/***************************************************************************************************
* Type:     GPIO Pin Configurations
****************************************************************************************************/

typedef struct
{
	uint8_t pin_number;	
	uint8_t mode;
	uint8_t o_type; 
	uint8_t o_speed;
	uint8_t pup_pdown;
	uint8_t alt_func_low;
	uint8_t alt_func_high;
} gpio_config_t;

/***************************************************************************************************
* Type:       GPIO Handle
* Info:
* *gpiox      - holds address of gpio(a-e) port
* gpio_config - holds the configurations for the register parameters
****************************************************************************************************/

typedef struct
{
	gpio_registers_t *gpiox;
	gpio_config_t gpio_config;
} gpio_handle_t;

/***************************************************************************************************
* Info: Enables the peripheral clock for gpio port
****************************************************************************************************/

void gpio_clock_enable(uint8_t gpio_port);
void gpio_clock_disable(uint8_t gpio_port);

/***************************************************************************************************
* Info: Initializes the gpio port and pin of the given parameters passed into
****************************************************************************************************/
void gpio_init(gpio_handle_t *gpio_handle);

/***************************************************************************************************
* Info: Writes to the odr by toggling bssr based on data                       
****************************************************************************************************/
void gpio_write_to_odr(gpio_registers_t *gpiox, uint8_t pin_number, uint8_t data);

/***************************************************************************************************
* Info: Reads from the idr and returns if input was received or not            
****************************************************************************************************/
uint8_t gpio_read_from_idr(gpio_registers_t *gpiox, uint8_t pin_number);

#endif /* GPIO_DRIVER_H */
