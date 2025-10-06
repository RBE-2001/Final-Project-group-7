#include "DualBlueMotor.h"

// Constructor
DualBlueMotor::DualBlueMotor(int pwmPin,
                                         int m1_ain1, int m1_ain2, int m1_encA, int m1_encB,
                                         int m2_ain1, int m2_ain2, int m2_encA, int m2_encB)
    : pwmPin(pwmPin)
{
    // -------- Setup PWM --------
    pinMode(pwmPin, OUTPUT);
    TCCR1A = 0xA8;  // Fast PWM mode, custom registers (like your single motor code)
    TCCR1B = 0x11;
    ICR1   = 400;
    OCR1C  = 0;

    // Motor 1 setup
    motor1.ain1 = m1_ain1;
    motor1.ain2 = m1_ain2;
    motor1.encA = m1_encA;
    motor1.encB = m1_encB;
    motor1.count = 0;
    motor1.previousState = 0;
    motor1.state = IDLE;
    motor1.dir = HOLD;

    pinMode(motor1.ain1, OUTPUT);
    pinMode(motor1.ain2, OUTPUT);
    pinMode(motor1.encA, INPUT);
    pinMode(motor1.encB, INPUT);

    // Motor 2 setup
    motor2.ain1 = m2_ain1;
    motor2.ain2 = m2_ain2;
    motor2.encA = m2_encA;
    motor2.encB = m2_encB;
    motor2.count = 0;
    motor2.previousState = 0;
    motor2.state = IDLE;
    motor2.dir = HOLD;

    pinMode(motor2.ain1, OUTPUT);
    pinMode(motor2.ain2, OUTPUT);
    pinMode(motor2.encA, INPUT);
    pinMode(motor2.encB, INPUT);

    // Attach interrupts
    attachInterrupt(digitalPinToInterrupt(motor1.encA), encoder1ISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(motor1.encB), encoder1ISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(motor2.encA), encoder2ISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(motor2.encB), encoder2ISR, CHANGE);
}

// Set shared PWM duty cycle
void DualBlueMotor::setEffort(int effort) {
    OCR1C = constrain(effort, 0, 400);
}

// Set direction of a motor
void DualBlueMotor::setMotorMode(int motorNum, Direction dir) {
    Motor &m = (motorNum == 1) ? motor1 : motor2;
    setMotorDirection(m, dir);
}

// Internal helper: write direction pins
void DualBlueMotor::setMotorDirection(Motor &m, Direction dir) {
    m.dir = dir;
    switch(dir) {
        case FORWARD:
            digitalWrite(m.ain1, HIGH);
            digitalWrite(m.ain2, LOW);
            m.state = MOVING;
            break;
        case BACKWARD:
            digitalWrite(m.ain1, LOW);
            digitalWrite(m.ain2, HIGH);
            m.state = MOVING;
            break;
        case HOLD:
            digitalWrite(m.ain1, HIGH);
            digitalWrite(m.ain2, HIGH);
            m.state = IDLE;
            break;
        case COAST:
            digitalWrite(m.ain1, LOW);
            digitalWrite(m.ain2, LOW);
            m.state = IDLE;
            break;
    }
}

bool DualBlueMotor::moveToPosition(int motorNum, long target) {
    Motor &m = (motorNum == 1) ? motor1 : motor2;
    Motor &otherMotor = (motorNum == 1) ? motor2 : motor1;

    // Only move if the other motor is idle
    if (otherMotor.state == IDLE) {
        PIDMotor(m, target, PID(1, 0, 0)) //TODO: TUNE PID and for both motors
    }

    return false; // still moving or waiting for other motor
}

bool DualBlueMotor::PIDMotor(Motor &m, long target PID pid) {
    noInterrupts();
    long current = m.count;
    interrupts();

    // Calculate error
    long error = target - current;

    // Motor reached target
    if (abs(error) < pid.tolorance) {
        setMotorDirection(m, Direction::HOLD); // stop motor
        setEffort(m, 0);
        m.state = IDLE;

        // Reset PID state
        pid.integral = 0;
        pid.lastError = 0;
        return true;
    }

    // PID calculations
    pid.integral += error;                  // integral term
    long derivative = error - pid.lastError; // derivative term
    float output = pid.Kp * error + pid.Ki * pid.integral + pid.Kd * derivative;

    pid.lastError = error;

    // Determine direction
    if (output > 0) {
        setMotorDirection(m, Direction::FORWARD);
    } else {
        setMotorDirection(m, Direction::BACKWARD);
        output = -output; // make positive for PWM
    }

    // Constrain PWM to effert bounds
    int pwmEffort = constrain((int)output, 0, 400);
    setEffort(m, pwmEffort);

    m.state = MOVING;
    return false; // target not yet reached
}

// Encoder ISRs
void DualBlueMotor::encoder1ISR() {
    updateEncoder(motor1);
}

void DualBlueMotor::encoder2ISR() {
    updateEncoder(motor2);
}

// --- Private helpers ---
void DualBlueMotor::updateEncoder(Motor &m) {
    bool a = digitalRead(m.encA);
    bool b = digitalRead(m.encB);
    short s = getState(a, b);

    short diff = (s - m.previousState + 4) % 4;
    if (diff == 1) {
        m.count--;
    } else if (diff == 3) {
        m.count++;
    }
    m.previousState = s;
}

short DualBlueMotor::getState(bool encA, bool encB) {
    if (!encA && !encB) return 3;
    else if (!encA && encB) return 2;
    else if (encA && encB) return 1;
    return 0;
}