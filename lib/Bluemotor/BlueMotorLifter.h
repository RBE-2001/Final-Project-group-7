#pragma once

class BlueMotorLifter
{
public:
    BlueMotorLifter();
    void setEffort(int effort);
    void moveTo(long position);
    long getPosition();
    void reset();
    void setup();

private:
    void setEffort(int effort, bool clockwise);
    static void isr();
    static short getState(bool encA, bool encB);
    const int tolerance = 3;
    const int PWMOutPin = 11; // motor speed
    const int AIN2 = 4; // h bridge input 2
    const int AIN1 = 13; // h bridge input 1
};