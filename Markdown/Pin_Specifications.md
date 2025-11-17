# Pin Specifications

What is Vdd and Vss

Vdd is external main power supplier of the microcontroller. Provided externally through Vdd pins of the microcontroller
- standard operating voltage of Vdd is :1.8V <= Vdd <= 3.6V
- Max voltage which can be applied on any Vdd pin of the microcontroller is 4V
	- Check AMR (Absolute Maxiumum Ratings) table to get specifications
- Vss is a **ground reference** of the microcontroller and she be maintained at 0V
- Minimum value which can be applied to Vss is -0.3V 

> Refer to datasheet Operating Conditions for specifications

Vin (Voltage In)

The maximum voltage that can be input for pins

Two types of pins:
- TT pin - Three-volt (Vin = 3V) tolerant
	- TTa pin (Three-volt tolerant Analog)
- FT pin - Five-volt (Vin = 5V) tolerant

Five-volt tolerant pin (FT)

- Five-volt tolerant pin means voltage protection is guaranteed (signal clamping using protection dioded) for the pin when its input voltage falls with in -0.3 <= Vin <= 5.5V
- GPIO is five-volt tolerant **only in input mode** (Five-volt tolerant feature not applicable when the gpio is in the output mode of analog mode)
- For FT GPIO, maximum Vin voltage limied to Vdd+4V
- General operating condition for FT pin: -0.3V <= Vin (ft) <= 5.5V
- For FT pin, regardless of the supply voltage, Ensure that Vin cannot exceed 5.5V
- When Vdd = 0V (Unpowered stm32 device), the input voltage on the FT GPIO cannot exceed 4V

Pin Current

- Ivdd = total current into Vdd power lines (source)
- Ivss = total current out of Vss ground lines (sink)
- Iio = output current sunk by I/O and control pin
	- External power -> pin into ground
- Iio = output current source by an I/Os and control pin
	- Flows from MCU to external world
	- This is when pin is at a High (1)

Current sourcing = make I/O pin high and current flows from Vdd -> I/O pin to external world

Current sinking = external power -> I/O pin -> Vss (GND)
	- Max current is 25 mA there for need to have resister to limit current

**Logic Levels**

Transmitting Device

oh - Ouput Logic High (at a specific voltage it will be represented as high)

ol - Output Logic Low (at a specific voltage it will be represented as low)

Voh/Vol - Voltage Out High (output threshhold)
- This is when the output voltage is driven high
- If Voh >= Vih

o is output mode for digital pins

If voltage is not at least the minimum of Vih then it wont be recognize as a logical high (5V or 3.3V) 

Receiver Device

ih - Input Logic High (to be recognized from pin as input it has to meet a voltage to be see as High)

il - Input Logic Low (to be recognized from pin as input it has to meet a voltage to be see as Low)

Vih/Vil - Voltage input High (input threshhold)

If voltage is higher then Vil that means it won't be able to recognize that it is a logical low (0V)
