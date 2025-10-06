#include <Arduino.h>
#include <BlueMotorExtender.h>

long oldValue = 0;
long newValue;
long count = 0;
unsigned time = 0;
short previousState = 0; // uses numbs 0-3 to represent the 4 possible states

// Moved becues prof told us to //TEST
const int ENCA = 2; 
const int ENCB = 3;

BlueMotorExtender::BlueMotorExtender()
{
}

void BlueMotorExtender::setup()
{
    pinMode(PWMOutPin, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(ENCA, INPUT);
    pinMode(ENCB, INPUT);
    // TCCR1A = 0xA8; //0b10101000; //gcl: added OCR1C for adding a third PWM on pin 11
    // TCCR1B = 0x11; //0b00010001;
    // ICR1 = 400;
    // OCR1C = 0;
    // Stop Timer 4

    attachInterrupt(digitalPinToInterrupt(ENCA), isr, CHANGE); // interrupt on both channels
    attachInterrupt(digitalPinToInterrupt(ENCB), isr, CHANGE);
    reset();
}

long BlueMotorExtender::getPosition()
{
    long tempCount = 0;
    noInterrupts();
    tempCount = count;
    interrupts();
    return tempCount;
}

void BlueMotorExtender::reset()
{
    noInterrupts();
    count = 0;
    interrupts();
}


void BlueMotorExtender::isr()
{
    // --- Read encoder pins ---
    short s = getState(digitalRead(ENCA), digitalRead(ENCB));

    // --- Compute difference with previous state ---
    short diff = (s-previousState+4)%4;

    // --- Handle valid movement only ---
    if (diff == 1)
        count--; // clockwise negative
    else if (diff == 3)
        count++; // counterclockwise positive
    // diff == 0 → no movement, ignore
    // diff == 2 → invalid transition (e.g., bounce or skipped step), ignore
    
    previousState = s; // save state for next time
}

short BlueMotorExtender::getState(bool encA, bool encB)
{
    if (!encA && !encB)
        return 3;
    else if (!encA && encB)
        return 2;
    else if (encA && encB)
        return 1;
    return 0;
}

void BlueMotorExtender::setEffort(int effort)
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

void BlueMotorExtender::setEffort(int effort, bool clockwise)
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
    analogWrite(6, effort/400.0 * 255.0); // duty 200/255

}

void BlueMotorExtender::moveTo(long target)  //Move to this encoder position within the specified
{                                    //tolerance in the header file using proportional control
                                     //then stop
    
    setEffort(0);
}