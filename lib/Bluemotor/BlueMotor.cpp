#include "BlueMotor.h"

// Static motor pointers
BlueMotor* BlueMotor::motorInstances[2] = {nullptr, nullptr};

BlueMotor::BlueMotor(int pwmPin, int ain1, int ain2, int enca, int encb)
    : PWMOutPin(pwmPin), AIN1(ain1), AIN2(ain2), ENCA(enca), ENCB(encb) {}

void BlueMotor::setup()
{
    pinMode(PWMOutPin, OUTPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(ENCA, INPUT);
    pinMode(ENCB, INPUT);

    // Timer setup for PWM (UNO/Nano: Timer1 on pin 11)
    TCCR1A = 0xA8;
    TCCR1B = 0x11;
    ICR1 = 400;
    OCR1C = 0;

    // Attach interrupts based on encoder pins
    if (!motorInstances[0]) {
        motorInstances[0] = this;
        attachInterrupt(digitalPinToInterrupt(ENCA), isr0, CHANGE);
        attachInterrupt(digitalPinToInterrupt(ENCB), isr0, CHANGE);
    } else if (!motorInstances[1]) {
        motorInstances[1] = this;
        attachInterrupt(digitalPinToInterrupt(ENCA), isr1, CHANGE);
        attachInterrupt(digitalPinToInterrupt(ENCB), isr1, CHANGE);
    }

    reset();
}

long BlueMotor::getPosition()
{
    noInterrupts();
    long temp = count;
    interrupts();
    return temp;
}

void BlueMotor::reset()
{
    noInterrupts();
    count = 0;
    interrupts();
}

void BlueMotor::handleEncoderChange()
{
    short s = getState(digitalRead(ENCA), digitalRead(ENCB));
    short diff = (s - previousState + 4) % 4;

    if (diff == 1) count--;       // CW
    else if (diff == 3) count++;  // CCW

    previousState = s;
}

short BlueMotor::getState(bool encA, bool encB)
{
    if (!encA && !encB) return 3;
    else if (!encA && encB) return 2;
    else if (encA && encB) return 1;
    return 0;
}

void BlueMotor::setEffort(int effort)
{
    if (effort < 0) setEffort(-effort, true);
    else setEffort(effort, false);
}

void BlueMotor::setEffort(int effort, bool clockwise)
{
    if (clockwise) {
        digitalWrite(AIN1, HIGH);
        digitalWrite(AIN2, LOW);
    } else {
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, HIGH);
    }
    OCR1C = constrain(effort, 0, 400);
}

void BlueMotor::moveTo(long target)
{
    setEffort(0); // placeholder (PID/proportional can be added later)
}

// --- ISR Wrappers ---
void BlueMotor::isr0() { if (motorInstances[0]) motorInstances[0]->handleEncoderChange(); }
void BlueMotor::isr1() { if (motorInstances[1]) motorInstances[1]->handleEncoderChange(); }
