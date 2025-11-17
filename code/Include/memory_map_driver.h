#ifndef MEMORY_MAP_DRIVER_H
#define MEMORY_MAP_DRIVER_H

#include <stdint.h>

/***************************************************************************************************
*
*                          Memory Mapped Core Peripheral Base Address
*
****************************************************************************************************/

/***************************************************************************************************
* Type:     NVIC Memory Mapped Registers
* Section:  4.2 Nested Vectored Interrupt Controller
* Location: Cortex M4 Generic Manual on page 4-3 for memory mapped addresses of NVIC
* Details:  The table of all the IRQn for the MCU is found in the Datasheet of STM32F407 under 
*           12.2 page 375
****************************************************************************************************/

/***************************************************************************************************
* Type:     NVIC Memory Map Register
* Section:  4.2 Nested Vectored Interrupt Controller
* Location: Cortex M4 Generic Manual on page 4-3 for memory mapped addresses of NVIC
****************************************************************************************************/

#define NVIC_BASE_ADDRESS           (0xE000E100UL)

/***************************************************************************************************
*
*                          Memory Mapped MCU Peripheral Base Address
*
****************************************************************************************************/

/***************************************************************************************************
* Type:     Memory Mapped Registers
* Section:  2.3 Memory Map
* Location: STM32F407 Reference Manual on page 928 for memory mapped addresses
****************************************************************************************************/

#define RCC_BASE_ADDRESS            (0x40023800UL)

/***************************************************************************************************
*                             Following Peripherals are on the AHB1 Bus   
****************************************************************************************************/

#define GPIOA_BASE_ADDRESS          (0x40020000UL)
#define GPIOB_BASE_ADDRESS          (0x40020400UL)
#define GPIOC_BASE_ADDRESS          (0x40020800UL)
#define GPIOD_BASE_ADDRESS          (0x40020C00UL)
#define GPIOE_BASE_ADDRESS          (0x40021000UL)

/***************************************************************************************************
*                             Following Peripherals are on the APB1 Bus   
****************************************************************************************************/

#define USART2_BASE_ADDRESS         (0x40004400UL)
#define USART3_BASE_ADDRESS         (0x40004800UL)
#define USART4_BASE_ADDRESS         (0x40004800UL)
#define UART5_BASE_ADDRESS          (0x40005000UL)
#define UART7_BASE_ADDRESS          (0x40007800UL)
#define UART8_BASE_ADDRESS          (0x40007C00UL)

#define SPI2_BASE_ADDRESS           (0x40003800UL)
#define SPI3_BASE_ADDRESS           (0x40003C00UL)

#define I2C1_BASE_ADDRESS           (0x40005400UL)
#define I2C2_BASE_ADDRESS           (0x40005800UL)
#define I2C3_BASE_ADDRESS           (0x40005C00UL)

/***************************************************************************************************
*                             Following Peripherals are on the APB2 Bus   
****************************************************************************************************/

#define USART1_BASE_ADDRESS         (0x40011000UL)
#define USART6_BASE_ADDRESS         (0x40011400UL)

#define EXTI_BASE_ADDRESS           (0x40013C00UL)

#define SYSCFG_BASE_ADDRESS         (0x40013800UL)

#define SPI1_BASE_ADDRESS           (0x40013000UL)
#define SPI4_BASE_ADDRESS           (0x40013400UL)

/****************************************************************************************************
*
*                               Core Processor Registers Structures 
*
****************************************************************************************************/

/****************************************************************************************************
* Type:     Nested Vectored Interrupt Control Memory Map
* Section:  4.2 Nested Vectored Interrupt Controller 
* Location: Cortex M4 Generic User Guide on page 4-3    
****************************************************************************************************/
typedef struct
{
    volatile uint32_t iser[8];           /* Interrupt Set Enable Register             - Offset 0x100 - 0x11C */
    volatile uint32_t reserve_1[24];     /* Reserve 1                                 - Offset 0x120 - 0x17C */
    volatile uint32_t icer[8];           /* Interrupt Clear Enable Register           - Offset 0x180 - 0x19C */
    volatile uint32_t reserve_2[24];     /* Reserve 2                                 - Offset 0x1A0 - 0x1FC */
    volatile uint32_t ispr[8];           /* Interrupt Set-pending Register            - Offset 0x200 - 0x21C */
    volatile uint32_t reserve_3[24];     /* Reserve 3                                 - Offset 0x220 - 0x27C */
    volatile uint32_t icpr[8];           /* Interrupt Clear-pending Register          - Offset 0x280 - 0x29C */
    volatile uint32_t reserve_4[24];     /* Reserve 4                                 - Offset 0x2A0 - 0x2FC */
    volatile uint32_t iabr[8];           /* Interrupt Clear-pending Register          - Offset 0x300 - 0x31C */
    volatile uint32_t reserve_5[36];     /* Reserve 5                                 - Offset 0x320 - 0x3FC */
    volatile uint32_t ipr[60];           /* Interrupt Priority Register               - Offset 0x400 - 0x4EF */
} nvic_registers_t;

#define nvic                        ((nvic_registers_t *)NVIC_BASE_ADDRESS)

/****************************************************************************************************
*
*                                 Peripheral Registers Structures 
*
****************************************************************************************************/

/****************************************************************************************************
* Type:     RCC Reset Clock and Control Registers    
* Section:  6.3 RCC Registers
* Location: STM32F407 Reference Manual on page 212 for register map   
****************************************************************************************************/

typedef struct 
{
    volatile uint32_t cr;                /* Control Register                          - Offset 0x00 */
    volatile uint32_t pllcfgr;           /* PLL Configuration Register                - Offset 0x04 */
    volatile uint32_t cfgr;              /* Clock Configuration Register              - Offset 0x08 */
    volatile uint32_t cir;               /* Clock Interrupt Register                  - Offset 0x0C */
    volatile uint32_t ahb1rstr;          /* Clock Interrupt Register                  - Offset 0x10 */
    volatile uint32_t ahb2rstr;          /* Clock Interrupt Register                  - Offset 0x14 */
    volatile uint32_t ahb3rstr;          /* Clock Interrupt Register                  - Offset 0x18 */
    volatile uint32_t reserve1;          /* Reserve Register 1                        - Offset 0x1C */
    volatile uint32_t apb1rstr;          /* Clock Interrupt Register                  - Offset 0x20 */
    volatile uint32_t apb2rstr;          /* Clock Interrupt Register                  - Offset 0x24 */
    volatile uint32_t reserve2[2];       /* Reserve Registers 2                       - Offset 0x28 - 0x2C */
    volatile uint32_t ahb1enr;           /* Clock Enable AHB1 Register                - Offset 0x30 */
    volatile uint32_t ahb2enr;           /* Clock Enable AHB2 Register                - Offset 0x34 */
    volatile uint32_t ahb3enr;           /* Clock Enable AHB3 Register                - Offset 0x38 */
    volatile uint32_t reserve3;          /* Reserve Registers 3                       - Offset 0x3C */
    volatile uint32_t apb1enr;           /* Clock Enable APB1 Register                - Offset 0x40 */
    volatile uint32_t apb2enr;           /* Clock Enable APB2 Register                - Offset 0x44 */
	volatile uint32_t reserve4[2];       /* Reserve Registers 4                       - Offset 0x48 - 0x4C */
    volatile uint32_t ahb1lpenr;         /* Clock Enable Low Power AHB1 Register      - Offset 0x50 */
    volatile uint32_t ahb2lpenr;         /* Clock Enable Low Power AHB2 Register      - Offset 0x54 */
    volatile uint32_t ahb3lpenr;         /* Clock Enable Low Power AHB3 Register      - Offset 0x58 */
    volatile uint32_t reserve5;          /* Reserve Register 5                        - Offset 0x5C */
    volatile uint32_t apb1lpenr;         /* Clock Enable Lower Power APB1 Register    - Offset 0x60 */
    volatile uint32_t apb2lpenr;         /* Clock Enable Lower Power APB2 Register    - Offset 0x64 */
    volatile uint32_t reserve6[2];       /* Reserve Registers 6                       - Offset 0x68 - 0x6C */
    volatile uint32_t bdcr;              /* Backup Domain Control Register            - Offset 0x70 */
    volatile uint32_t csr;               /* Clock Control & Status Register           - Offset 0x74 */
    volatile uint32_t reserve7[2];       /* Reserve Registers 7                       - Offset 0x78 - 0x7C */
    volatile uint32_t sscgr;             /* Spread Spectrum Clock Generation Register - Offset 0x80 */
    volatile uint32_t plli2scfgr;        /* I2S PLL Configuration Register            - Offset 0x84 */
    volatile uint32_t pllsaicfgr;        /* SAI PLL Configuration Register            - Offset 0x88 */
    volatile uint32_t dckcfgr;           /* Dedicated Clock Configuration Register    - Offset 0x8C */
} rcc_registers_t;

#define rcc                         ((rcc_registers_t *)(RCC_BASE_ADDRESS))

/****************************************************************************************************
* Type:     General Purpose Input/Output (GPIO) Registers 
* Section:  8.4 GPIO Registers
* Location: STM32F407 Reference Manual on page 290 for register map   
****************************************************************************************************/

typedef struct 
{
    volatile uint32_t moder;             /* Mode Register                         - Offset 0x00 */
    volatile uint32_t otyper;            /* Output Type Register                  - Offset 0x04 */
    volatile uint32_t ospeedr;           /* Output Speed Register                 - Offset 0x08 */
    volatile uint32_t pupdr;             /* Pull-up Pull-down Register            - Offset 0x0C */
    volatile uint32_t idr;               /* Input Data Register                   - Offset 0x10 */
    volatile uint32_t odr;               /* Output Data Register                  - Offset 0x14 */
    volatile uint32_t bsrr;              /* Bit Set/Reset Register                - Offset 0x18 */
    volatile uint32_t lckr;              /* Lock Register                         - Offset 0x1C */
    volatile uint32_t afrl;              /* Alternate Function Low Register       - Offset 0x20 */
    volatile uint32_t afrh;              /* Alternate Function High Register      - Offset 0x24 */
} gpio_registers_t;

#define gpioa                       ((gpio_registers_t *)(GPIOA_BASE_ADDRESS))
#define gpiob                       ((gpio_registers_t *)(GPIOB_BASE_ADDRESS))
#define gpioc                       ((gpio_registers_t *)(GPIOC_BASE_ADDRESS))
#define gpiod                       ((gpio_registers_t *)(GPIOD_BASE_ADDRESS))
#define gpioe                       ((gpio_registers_t *)(GPIOE_BASE_ADDRESS))

/****************************************************************************************************
* Type:     System Configuration (Syscfg) Registers
* Section:  9.3 SYSCFG Registers
* Location: STM32F407 Reference Manual on page 304 for register map   
****************************************************************************************************/

typedef struct
{
    volatile uint32_t memrmp;            /* Memory Remap Register                         - Offset 0x00 */
    volatile uint32_t pmc;               /* Peripheral Mode Configuration Register        - Offset 0x04 */
    volatile uint32_t exticr[4];         /* External Interrupt Configuration Register 1-4 - Offset 0x08 - 0x14 */
    volatile uint32_t reserve[2];        /* Reserve                                       - Offset 0x18 - 0x1C */
    volatile uint32_t cmpcr;             /* Compensation Cell Control Register            - Offset 0x20 */
} syscfg_registers_t;

#define syscfg                      ((syscfg_registers_t *)(SYSCFG_BASE_ADDRESS))

/****************************************************************************************************
* Type: Extended Interrupts (EXTI) Registers
* Section: 12.3 EXTI Registers                              
* Location: STM32F407 Reference Manual on page for 390 register map   
****************************************************************************************************/

typedef struct 
{
    volatile uint32_t imr;               /* Interrupt Mask Register               - Offset 0x00 */
    volatile uint32_t emr;               /* Event Mask Register                   - Offset 0x04 */
    volatile uint32_t rtsr;              /* Rising Trigger Selection Register     - Offset 0x08 */
    volatile uint32_t ftsr;              /* Falling Trigger Selection Register    - Offset 0x0C */
    volatile uint32_t swier;             /* Software Interrupt Event Register     - Offset 0x10 */
    volatile uint32_t pr;                /* Pending Register                      - Offset 0x14 */
} exti_registers_t;

#define exti                        ((exti_registers_t *)(EXTI_BASE_ADDRESS))

/****************************************************************************************************
* Type: Inter-Integrated Circuit (I2C) Registers   
* Secion: 27.6 I2C Registers
* Location: STM32F407 Reference Manual on page 875 for register map   
****************************************************************************************************/

typedef struct
{
    volatile uint32_t cr1;               /* Control Register 1                    - Offset 0x00 */
    volatile uint32_t cr2;               /* Control Register 2                    - Offset 0x04 */
    volatile uint32_t oar1;              /* Clock Enable APB2                     - Offset 0x08 */
    volatile uint32_t oar2;              /* Clock Enable APB2                     - Offset 0x0C */
    volatile uint32_t dr;                /* Data Register                         - Offset 0x10 */
    volatile uint32_t sr1;               /* Status Register 1                     - Offset 0x14 */
    volatile uint32_t sr2;               /* Status Register 2                     - Offset 0x18 */
    volatile uint32_t ccr;               /* Capture/Compare Register              - Offset 0x1C */
    volatile uint32_t trise;             /* Rise Timer Register                   - Offset 0x20 */
    volatile uint32_t fltr;              /* Filter Register                       - Offset 0x24 */
} i2c_registers_t;

#define i2c1                        ((i2c_registers_t *)(I2C1_BASE_ADDRESS))
#define i2c2                        ((i2c_registers_t *)(I2C2_BASE_ADDRESS))
#define i2c3                        ((i2c_registers_t *)(I2C3_BASE_ADDRESS))

/****************************************************************************************************
* Type:     Serial Peripheral Interface (SPI) Registers
* Section:  28.5 SPI and I2S Registers
* Location: STM32F407 Reference Manual on page 928 for register map   
****************************************************************************************************/

typedef struct
{
    volatile uint32_t cr1;               /* Control Register 1                    - Offset 0x00 */
    volatile uint32_t cr2;               /* Control Register 2                    - Offset 0x04 */
    volatile uint32_t sr;                /* Status Register                       - Offset 0x08 */
    volatile uint32_t dr;                /* Data Register                         - Offset 0x0C */
    volatile uint32_t crcpr;             /* CRC Polynomial Register               - Offset 0x10 */
    volatile uint32_t rxcrcr;            /* RX CRC Regsister                      - Offset 0x14 */
    volatile uint32_t txcrcr;            /* TX CRC Register                       - Offset 0x18 */
    volatile uint32_t i2scfgr;           /* I2S Configuration Register            - Offset 0x1C */
    volatile uint32_t i2spr;             /* I2S Prescaler Register                - Offset 0x20 */
} spi_registers_t;

#define spi1                        ((spi_registers_t *)(SPI1_BASE_ADDRESS))
#define spi2                        ((spi_registers_t *)(SPI2_BASE_ADDRESS))
#define spi3                        ((spi_registers_t *)(SPI3_BASE_ADDRESS))
#define spi4                        ((spi_registers_t *)(SPI4_BASE_ADDRESS))

/****************************************************************************************************
* Type:     Universial (Synchronous)/Asynchronous Receiver/Transmitter
* Section:  30.6 USART Registers      
* Location: STM32F407 Reference Manual on page 1021 for register map   
****************************************************************************************************/

typedef struct
{
    volatile uint32_t sr;                /* Status Register                       - Offset 0x00 */
    volatile uint32_t dr;                /* Data Register                         - Offset 0x04 */
    volatile uint32_t brr;               /* Buad Rate Register                    - Offset 0x08 */
    volatile uint32_t cr1;               /* Control Register 1                    - Offset 0x0C */
    volatile uint32_t cr2;               /* Control Register 2                    - Offset 0x10 */
    volatile uint32_t cr3;               /* Control Register 3                    - Offset 0x14 */
    volatile uint32_t gtpr;              /* Guard Time Prescaler Register         - Offset 0x18 */
} usart_registers_t;

#define usart1                      ((usart_registers_t *)(USART1_BASE_ADDRESS))
#define usart2                      ((usart_registers_t *)(USART2_BASE_ADDRESS))
#define usart3                      ((usart_registers_t *)(USART3_BASE_ADDRESS))
#define usart4                      ((usart_registers_t *)(USART4_BASE_ADDRESS))
#define uart5                       ((usart_registers_t *)(UART5_BASE_ADDRESS))
#define usart5                      ((usart_registers_t *)(USART5_BASE_ADDRESS))
#define uart6                       ((usart_registers_t *)(UART6_BASE_ADDRESS))
#define uart7                       ((usart_registers_t *)(UART7_BASE_ADDRESS))
#define uart8                       ((usart_registers_t *)(UART8_BASE_ADDRESS))

#endif /* MEMORY_MAP_DRIVER_H */
