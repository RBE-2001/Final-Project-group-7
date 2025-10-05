#pragma once

class BlueMotor
{
public:
    BlueMotor(int pwmPin, int ain1, int ain2, int enca, int encb);
    void setup();
    void setEffort(int effort);
    void moveTo(long position);
    long getPosition();
    void reset();

private:
    void setEffort(int effort, bool clockwise);
    void handleEncoderChange();

    static void isrA0();
    static void isrB0();
    static void isrA1();
    static void isrB1();
    // (add more if you need more motors)

    static BlueMotor* motorA0;
    static BlueMotor* motorB0;
    static BlueMotor* motorA1;
    static BlueMotor* motorB1;

    int PWMOutPin;
    int AIN1;
    int AIN2;
    int ENCA;
    int ENCB;

    volatile long count = 0;
    short previousState = 0;
    const int tolerance = 3;

    short getState(bool encA, bool encB);
};