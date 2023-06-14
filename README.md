# SUPER85

### You can do a lot with just 5 pins.

```ascii
                  .-----___-----.
         RESET ---| O           |--- VCC
PB3/ADC3/~OC1B ---|   TINY85    |--- PB2/ADC1/SCL/T0
PB4/ADC2/OC1B  ---|             |--- PB1/OC0B/OC1A
           GND ---|             |--- PB0/SDA/OC0A/~OC1A/AREF
                  '-------------'
```

This is a collection of short Arduino sketches I have written for the ATtiny85 microcontroller.

Currently there is only one of them, a smart software-configurable boost converter, but I plan on releasing more useful ATtiny85 sketches in the future. Check out the gitignore for ones that are in the works but not ready for release yet.

## Included sketches

* [SmartBoost](smartboost/readme.md): software-configurable boost converter power supply

## Notes

* I prefer the [Sparkfun Tiny AVR Programmer][prog] to program the ATtiny85s.
* The circuit diagrams, where included, have been rendered with [Schemascii].
* Unless otherwise noted: for those sketches that use I2C communication, SDA and SCL are as indicated in the diagram above and require external pull-ups, and the protocol for communication is a standard register-based read-write method, done as follows:

    * To write a register or block of contiguous registers: write the first register's index, followed by register contents. Register pointer auto-increments, and wraps at the end. In Arduino code:
        ```c
        Wire.beginTransmission(XXX);
        Wire.write(regAddress);
        Wire.write(myData, sizeof(myData));
        Wire.endTransmission();
        ```
    * To read a register or block of contiguous registers: write the first register's index, issue an I2C restart, and then read. Register pointer auto-increments, but does **not** wrap at the end.  In Arduino code:
        ```c
        Wire.beginTransmission(XXX);
        Wire.write(regAddress);
        Wire.endTransmission(false);
        Wire.requestFrom(XXX, NNN);
        ```
* The built-in I2C slave functionality is only present in Spence Konde's [ATTinyCore], please use that.

[ATtinyCore]: https://github.com/SpenceKonde/ATTinyCore
[prog]: https://www.sparkfun.com/products/11801
[Schemascii]: https://github.com/dragoncoder047/schemascii