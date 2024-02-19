// Ratio between the pulse frequencies
// Wheel is turning at 10 holes/sec
#define WHEEL_TICKS 6
// Line frequency is 60Hz
#define LINE_TICKS 1

void setup() {
    pinMode(1, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(0, INPUT);
    pinMode(2, INPUT);
    //setTimer0Prescale(1);
    byte temp = TCCR0A;
    temp &= ~(7<<CS00);
    temp |= 1<<CS00;
    TCCR0A = temp;
}

// Error < 0 means wheel is behind
// Error > 0 means wheel is ahead
int error = 0;
byte pwm = 0;

byte last_PINB = 0;

void loop() {
    if (error > 0) {
        if (pwm > 0) pwm--;
    } else {
        if (pwm < 255) pwm++;
    }
    analogWrite(1, pwm);
    int cur_PINB = PINB;
    if (cur_PINB & (1<<PB0) && !(last_PINB & (1<<PB0))) {
        error += WHEEL_TICKS;
    }
    if (cur_PINB & (1<<PB2) && !(last_PINB & (1<<PB2))) {
        error -= LINE_TICKS;
    }
    last_PINB = cur_PINB;
    digitalWrite(4, error < 0 ? HIGH : LOW);
}
