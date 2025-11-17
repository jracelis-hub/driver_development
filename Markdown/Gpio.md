# GPIO Driver

GPIO Port is nothing but a collection of fixed number of I/O pins
- GPIOA 0-15 Pin

After reset all GPIO pins are already set to input state, therefore since no configuration it is floating
- High Impedance State

**Input Mode w/ Pull Up/Pull Down**
- Pull up means resistor connected to VCC
- Pull down means resistor connected to GND

Without this can cause leakage of current

Pull Up
```
                 Vcc
                  0
                  |
 Input Buffer     z
       /|         z Ri  Pin
------| |---------|-----[]--
       \|

```
Pull Down
```
 Input Buffer      
       /|               Pin
------| |---------|-----[]--
       \|         z
                  z Ri
				  |
				 ---
				  -
			     GND
```

**Output Mode w/ Open Drain**
- Open Drain State
	- 2 States:
	1. GND
	2. Float

Open-Drain configuration lacks pull up pin capability 

Needs internal pull up resistor or external pull up resistor without it the mode is useless

**Output Mode with Push-Pull Configuration**

No need for pull resistor

Power Consumption

Important to configure input to high (Vcc) or low (GND) to avoid floating states

Port Input Data Register
- Used to read from the register

Port Output Data Register
- Used to write to the register

GPIO Mode Register
- Has 15 pins for each GPIO Port
- Can Configure To:
	- Input (reset state)
	- General Purpose Output Mode
	- Alternate Function Mode
	- Analog Mode
- The data present on the I/O pin are sampled into the input data register every AHB1 clock cycle
- Read access to the input data register provides the I/O state of that pin

Give attention to pull up resistor

GPIO Output Configuration
- Two output configuration:
	1. Push Pull configuration
		- If needed High and Low States
	2. Open-Drain
		- High state in the output pin
		- I2C has to be in open-drain output type

Aternate Function Mode
- Pin will be assigned for different functionality
	- UART TX
	- UART RX
	- I2C
	- Timers
	- etc...

The Aternate Function Output will control the output control

GPIO Port Output Speed Register
- Only used when GPIO is in output mode

Can configure how quick the GPIO transition is from high to low and low to high
- Trise the switch from Low to High
- Tfall the switch from High to Low

Four Types of Speeds:
- Low Speed
- Medium Speed
- High Speed
- Very High Speed

> Refer to datasheet for actual values

GPIO Pull Up and Pull Down Registers
- No pull up or pull down
- Pull up Vdd
- Pull down GND
- Reserved

GPIO Port Input Register
- Read the I/O state from each pin
- Updated one every AHB1 cycle

Types of Configurations
- Input Floating
- Input pull-up
- Input pull-down
- Analog
- Output open-drain with pull-up or pull-down capability
- Output push-pull with pull-up or pull-down capability
- Alternate function push-pull with pull-up or pull-down capability
- Alternate function open-drain with pull-up or pull-down capability

When in Alternate Functional Mode can have 16 different types
- Everything GPIO pin can have 16 different alternative modes
