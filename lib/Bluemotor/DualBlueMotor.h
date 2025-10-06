#pragma once
#include <Arduino.h>

class DualBlueMotor {
public:
    enum Direction { HOLD, COAST, FORWARD, BACKWARD };
    enum State { IDLE, MOVING };

    struct Motor {
        int ain1, ain2;          // H-bridge direction pins
        int encA, encB;          // Encoder pins
        volatile long count;     // Encoder count
        short previousState;     // Previous encoder state
        State state;             // IDLE or MOVING
        Direction dir;           // Current direction
    };

    struct PID {
        float Kp = 0;
        float Ki = 0;
        float Kd = 0;
        float tolorance = 10;
        long integral = 0;
        long lastError = 0;
    };
    // Constructor: pwm pin, motor pins + encoder pins
    DualBlueMotor(int pwmPin,
                        int m1_ain1, int m1_ain2, int m1_encA, int m1_encB,
                        int m2_ain1, int m2_ain2, int m2_encA, int m2_encB);

    // Set the shared PWM duty cycle (0-400)
    void setEffort(int effort);

    // Set the direction of a motor individually
    void setMotorMode(int motorNum, Direction dir);

    // Non-blocking move to target
    bool moveToPosition(int motorNum, long target);

    // Encoder ISRs (attach in setup)
    void encoder1ISR();
    void encoder2ISR();

private:
    int pwmPin;
    Motor motor1, motor2;

    // Internal helpers
    void setMotorDirection(Motor &m, Direction dir);
    short getState(bool encA, bool encB);

    bool PIDMotor(Motor &m, long target, PID pid);
};
