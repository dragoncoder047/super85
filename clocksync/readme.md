# ATtiny85 Motor PLL

This circuit uses an ATtiny85, a speed sensor, and a mains transformer to synchronize the speed of a DC motor to the mains frequency, so it will keep accurate time if used to drive an electric clock.

I used an old lego 71427 9V motor, which is one of the quietest lego motors. Undervolted at 6V, it runs almost silently, save for the rattling of gears. The speed sensor was a medium wheel with 6 holes and a photo-interrupter.

Speed ratio math: the mains frequency where I live is 60 Hz. The wheel was geared to spin at an (intended) speed of 5/3 turns per second (100 RPM) which with 6 holes comes out to 10 Hz pulses from the speed sensor. The ratio in the code is the reverse of that, 6 wheel:1 line, to make the speeds equal.

## Parts

* ATtiny85
* Full-bridge rectifier, or 4 diodes
* 7805
* Resistors, capacitors, etc.
* Transistor for controlling the motor (2N7000 suitable for &le;200mA)

## Circuit

![circuit](circuit.txt.svg)

Not shown in the circuit but used in the code: pin PB4 is programmed to go HIGH when the motor is behind, and go LOW when the motor is ahead, so you can attach a "debug" LED between this and GND to monitor how the motor is doing.
