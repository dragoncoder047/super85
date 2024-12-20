// Ratio between the pulse frequencies
// Wheel is turning at 10 holes/sec
#define WHEEL_TICKS 6
// Line frequency is 60Hz
#define LINE_TICKS 1

#define DEBUG_LED 4
#define PWM_PIN 1
#define LINE_PULSE_PIN 2
#define WHEEL_PULSE_PIN 0

void setup() {
    pinMode(PWM_PIN, OUTPUT);
    pinMode(DEBUG_LED, OUTPUT);
    pinMode(LINE_PULSE_PIN, INPUT);
    pinMode(WHEEL_PULSE_PIN, INPUT);

    TCCR1 = 1 << CS10 | 1 << PWM1A | 2 << COM1A0;  // turn off clock divisor, select PB1 as OC1A output
}

// Error < 0 means wheel is behind
// Error > 0 means wheel is ahead
int error = 0;

#define SLOWDOWN_BY 128

#define MIN_PWM 0
#define MAX_PWM 10


void do_pid() {
    static int slowdown = 0;
    int div_by = 0; // constrain(abs(error), 16, 128); // run the loop faster as error gets smaller
    slowdown++;
    if (slowdown < div_by) return;
    slowdown = 0;

    static byte pwm = MIN_PWM;

    if (error > 0) {
        if (pwm > MIN_PWM) pwm--;
    } else {
        if (pwm < MAX_PWM) pwm++;
    }
    OCR1A = pwm;
}

void loop() {
    do_pid();

    static byte last_PINB = 0;
    int cur_PINB = PINB;
    if (cur_PINB & (1 << WHEEL_PULSE_PIN) && !(last_PINB & (1 << WHEEL_PULSE_PIN))) {
        error += WHEEL_TICKS;
    }
    if (cur_PINB & (1 << LINE_PULSE_PIN) && !(last_PINB & (1 << LINE_PULSE_PIN))) {
        error -= LINE_TICKS;
    }
    last_PINB = cur_PINB;
    digitalWrite(DEBUG_LED, error < 0 ? HIGH : LOW);
}
