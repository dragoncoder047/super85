# ATtiny85 Boost Converter

This circuit uses the ADC input of the ATtiny85 and a PWM output to control a boost converter circuit.

The code sets up the ATtiny to output a ~32 kHz PWM signal on pin PB1, and read the ADC on pin PB3. Pins PB0 and PB2 are set up as SDA and SCL of the I2C bus, respectively.

Based partly on [this video](https://youtube.com/watch?v=QnUhjnbZ0T8) from GreatScott. The code he provided was quite long and verbose, and included a potentiometer to control the voltage, but this is designed to be controlled over I2C.

## I2C Register Summary

| Register Index | R/W | Default | Function |
|:--------------:|:---:|:-------:|:---------|
| 0              | R/W | 55     | ADC Target value. The code will try to maintain the output voltage at the point where the resistor-divided output voltage connected to the ADC equals register 0. Note that the ADC reference is set to the internal 2.56V regulated reference, not VCC, so the step size is exactly 10 mV, not 1/256th of VCC as the normal behavior is. |
| 1              | R/W | 220     | Maximum PWM duty cycle in 256ths. This top limit is used to prevent the duty cycle reaching 100% and the current running out of control. Set this lower to limit the maximum current. |
| 2              |  R  | n/a     | Current PWM duty cycle. This is roughly proportional to the output current draw. |
| 3              |  R  | n/a     | Current ADC reading. This is proportional to the output voltage as set by the choice of resistor divider, and (under normal conditions) should be equal or close to the target value as set by register 0. If this is less than the target, and the PWM duty cycle has hit its maximum, this indicates the power supply is overloaded. |

## Parts

* ATtiny85
* Power inductor (~200 &micro;H, thick wire for 3+ amps)
* N-channel power MOSFET (I used an IRLZ44N)
* Large capacitor (I used 1000&micro;F)
* Schottky diode (3+ amps - I used an SB360)
* Feedback resistor pair (I used 100k/10k for an 11x division of the output voltage)

## Circuit

![circuit](circuit.txt.svg)
