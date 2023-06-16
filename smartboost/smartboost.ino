#define I2C_SLAVE_ADDRESS 0x05 // the 7-bit address
#include <Wire.h>
volatile uint8_t i2c_regs[] = { 55, 220, 128, 0 };
#define ADC_TARGET i2c_regs[0]
#define MAX_PWM i2c_regs[1]
#define CURRENT_PWM i2c_regs[2]
#define CURRENT_ADC i2c_regs[3]
// I2C handler routines
const uint8_t reg_size = sizeof(i2c_regs) / sizeof(i2c_regs[0]);
volatile uint8_t reg_position;
void requestEvent() {
    while (reg_position < reg_size) {
        Wire.write(i2c_regs[reg_position]);
        reg_position++;
    }
    reg_position = 0;
}
void receiveEvent(uint8_t howMany) {
    if (howMany < 1) return;
    reg_position = Wire.read();
    howMany--;
    if (!howMany) return;
    while (howMany--) {
        if (reg_position >= reg_size) reg_position = 0;
        i2c_regs[reg_position] = Wire.read();
        reg_position++;
    }
}

void setup() {
    cli();
    // set pin modes
    DDRB = 1<<PB1;

    TCCR1 = 1<<CS10 | 1<<PWM1A | 2<<COM1A0; // turn off clock divisor, select PB1 as OC1A output

    Wire.begin(I2C_SLAVE_ADDRESS);
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);

    // Set up ADC
    ADMUX = 2<<REFS0 | 1<<REFS2 | 1<<ADLAR | 3<<MUX0; // Set 2.56V reference, left adjust, pin PB3 as ADC pin
    ADCSRA = 1<<ADEN | 6<<ADPS0; // turn on ADC with 125kHz clock

    sei(); // Enable interrupts
}

uint8_t pwm = 128, adc;
void loop() {
    ADCSRA |= 1<<ADSC;
    while (ADCSRA & (1<<ADSC));
    adc = ADCH;
    CURRENT_ADC = adc;
    if (adc > ADC_TARGET) {
        if (pwm > 0) pwm--;
    }
    else {
        if (pwm < MAX_PWM) pwm++;
    }
    CURRENT_PWM = pwm;
    OCR1A = pwm;
}
