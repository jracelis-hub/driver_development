# SPI (Serial Peripheral Communication)

## Quickstart

Make sure pin outputs match in Volatages for master <--> slave
- Voh/Vol Voltage Output (High/Low)
- Vih/Vil Voltage Input (High/Low)

Configurations:
- 4 pin configuration
	- MISO - master in slave out
	- MOSI - master out slave in
	- SCLK
	- SS
- 2 pin configuration
	- MOSI
	- SCLK
	- SS (Slave GND)

Shift bit registers 16 bit or 8 bits

SS always in output mode

### API

- SPI Initialization/ Peripheral Clock
- SPI Tx
- SPI Rx
- SPI Interrupt Configuration & Handling
- Other SPI management APIs

## Theory

Serial data communication is one master to several slaves

Use typically 4 pins:
- MISO (Master In / Slave Out)
	- Data pin
	- Received data in master mode or transmit in slave mode
- MOSI (Master Out / Slave In)
	- Data pin
	- Transmit data in master mode or receive data in slave mode
- SCLK (Serial Clock)
	- Synchronous through this
	- Master produces the clock
	- Slave does not produce clock
- NSS/SS (Slave Select)
	- this can be used to select an individual slave device for commmunication
	- Master can select the slave in which it wants to communicate with

> SPI is short distance serial communication

Master and slave need to support SPI interface or else can not use

Master selects the slave using GPIO pin by pulling it to ground then the SS will be gnd and communication activated

Minimal SPI Bus communication

Can customize based on application

Will only need two lines
- One for clock and data signal
- Connect SS to GND

SPI Operations

SPI communication is based on shift registers

Upon first communication there are 8 bits A0 - A7 when clock begins on bit goes into Master and One goes to slave
- For every clock cycle Master Least Signifcant Bit -> Slave -> Least Significant Bit Slave -> Master
- When Master Sends data it always received data if MISO line is connected

**SPI IS FULL DUPLEX COMMUNICATION**

SPI can also be configured using half duplex
- One data line
- Needs MOSI data line
- Clock

Simplex Communication
- Transmit only or receive only

Block Diagram

Shift registers
- Data communication up to 16 bits in shift register

SCK
- Configurated using the Buad rate generator
- `BR` register

Flow

For writing
```
APB Bus -> Write -> Tx Buffer -> Shift register -> MOSI
```

For reading
```
MISO -> Shift register -> Rx Buffer -> APB Bus
```

Chip Select

When a device is slave mode:
- NSS works as a standard chip select input and lets the slave communicate with the master

When a device is a master:
- In master mode, NSS can be used either as output or input. As an input it cam prevent multi-master bus collisions, and as an output it can drive a slave select signal of a single slave

2 Configuration:
1. Software slave management
2. Hardware slave management

Hardware/Software slave management can be set using the `SSM` bit in the `SPIx_CR1` register

Software Slave Management
- Master does not utilize NSS
- `SSM = 1`
- `SSI = 0` (grounded)

Hardware Slave Management
- NSS pin must be in output mode
- `SSM = 0`
- `NSS` pin must be pulled low to active slave to communicate with master

SPI Commmunication Format

- SCLK Phase (CPHA)
- SCLK Polarity (CPOL)
- Data Frame Format (DFF)

During SPI communication, receive and transmit operations are performed simultaneously
- The serial (SCK) synchronizes the shfiting andsmapling of the information on the data lines
- The communication format depends on the clock phase, the clock polarity and the data frame format. To be able to communicate together, the master and slaves devices must follow the same communication format

CPOL(Clock Polarity)
- CPOL bit controls the idle state value of the clock when no data is being transferred
- CPOL is reset, the SCLK pin has a low-level idle state. 
- If CPOL is set, the SCLK pin as a high-level idle state

CPOL = 0
```
   ----  ----
   |  |  |  |
----  ----  ---- <-- Idle State Low
```
> Data will be sampled on the CPHA = 1 trailing (2nd) edge of the clock

CPOL = 1
```
----  ---- <--- Idle State High
   |  |  |
   ----  ----
```
> Data will be sampled on the CPHA = 0 leading (1st) edge of the clock

CPHA(Clock Phase)
- CPHA controls at which clock edge of the SCLK (1st or 2nd) the data should be sampled by the slave
- The combination of CPOL bits selects the data capture clock edge.

Sampling happens on the input side to know what data is being sent
- MOSI slave is sampling
- MISO master is sampling
