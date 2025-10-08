#include <Arduino.h>
#include <BlueMotorLifter.h>

long oldValue = 0;
long newValue;
long count = 0;
unsigned time = 0;
short previousState = 0; // uses numbs 0-3 to represent the 4 possible states

// Moved becues prof told us to //TEST
const int ENCA = 0; 
const int ENCB = 1;

BlueMotorLifter::BlueMotorLifter()
{
}

void BlueMotorLifter::setup()
{
    pinMode(PWMOutPin, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(ENCA, INPUT);
    pinMode(ENCB, INPUT);
    TCCR1A = 0xA8; //0b10101000; //gcl: added OCR1C for adding a third PWM on pin 11
    TCCR1B = 0x11; //0b00010001;
    ICR1 = 400;
    OCR1C = 0;

    attachInterrupt(digitalPinToInterrupt(ENCA), isr, CHANGE); // interrupt on both channels
    attachInterrupt(digitalPinToInterrupt(ENCB), isr, CHANGE);
    reset();
}

long BlueMotorLifter::getPosition()
{
    long tempCount = 0;
    noInterrupts();
    tempCount = count;
    interrupts();
    return tempCount;
}

void BlueMotorLifter::reset()
{
    noInterrupts();
    count = 0;
    interrupts();
}


void BlueMotorLifter::isr()
{
    // --- Read encoder pins ---
    short s = getState(digitalRead(ENCA), digitalRead(ENCB));

    // --- Compute difference with previous state ---
    short diff = s - previousState;

    // Handle wrap-around manually instead of using modulus
    if (diff < 0)
        diff += 4;

    // --- Handle valid movement only ---
    if (diff == 1)
        count--; // clockwise negative
    else if (diff == 3)
        count++; // counterclockwise positive
    // diff == 0 → no movement, ignore
    // diff == 2 → invalid transition, ignore

    previousState = s; // save state for next time
}

short BlueMotorLifter::getState(bool encA, bool encB)
{
    if (!encA && !encB)
        return 3;
    else if (!encA && encB)
        return 2;
    else if (encA && encB)
        return 1;
    return 0;
}

void BlueMotorLifter::setEffort(int effort)
{
    if (effort < 0)
    {
        setEffort(-effort, true);
    }
    else
    {
        setEffort(effort, false);
    }
}

void BlueMotorLifter::setEffort(int effort, bool clockwise)
{
    if (clockwise)
    {
        digitalWrite(AIN1, HIGH);
        digitalWrite(AIN2, LOW);
    }
    else
    {
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, HIGH);
    }
    // analogWrite(PWMOutPin, effort/400.0 * 255.0); // duty 200/255//OCR1C = constrain(effort, 0, 400);
    OCR1C = constrain(effort, 0, 400);
}

void BlueMotorLifter::moveTo(long target)  //Move to this encoder position within the specified
{                                    //tolerance in the header file using proportional control
                                     //then stop
    
    setEffort(0);
}