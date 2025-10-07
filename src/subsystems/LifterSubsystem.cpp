#include "LifterSubsystem.h"

// --------- Susytems Functions ---------
void LifterSubsystem::Init() {
    currentState = State::Idle;

#ifdef __SUBSYSTEM_DEBUG
    Serial.println("LifterSubsystem -> Initilized");
#endif
}

void LifterSubsystem::Update() {
    switch (currentState) {
        case State::Idle:
            Idle();
            break;

        case State::L1:
            GoToL(0);
            break;

        case State::L15:
            GoToL(500;
            break;

        case State::L2:
            GoToL(1500);
            break;

        case State::L25:
            GoToL(2000);
            break;

        case State::L3:
            GoToL(2200);
            break;
    }
}

bool LifterSubsystem::IsDone() const {
    return currentState == State::Idle;
}
// 2200 max hight

// --------- States ---------
void LifterSubsystem::Idle() {
    //TODO: stop motors
    motor.setEffort(0);
}

void LifterSubsystem::GoToL(float rot) {
    // TODO: replace with set Lifter to L code
    float error = rot - motor.getPosition();
    motor.setEffort(error);
    if (abs(error) < 20) { //TODO: replace true with logic for when Lifter is at Leval
        SetState(State::Idle);  // go back to idle when done
        motor.setEffort(0);
    }
}

void LifterSubsystem::SetState(State newState) {
    if (newState != currentState) {
        previousState = currentState;
        currentState = newState;

    #ifdef __SUBSYSTEM_DEBUG
        switch (newState) {
            case State::Idle:       Serial.println("LifterSubsystem -> Entering IDLE"); break;
            case State::L1:  Serial.println("LifterSubsystem -> Goint to L1"); break;
            case State::L15:  Serial.println("LifterSubsystem -> Goint to L1.5"); break;
            case State::L2:  Serial.println("LifterSubsystem -> Goint to L2"); break;
            case State::L25:  Serial.println("LifterSubsystem -> Goint to L2.5"); break;
            case State::L3:  Serial.println("LifterSubsystem -> Goint to L3"); break;
        }
    #endif
    }
}

// --------- Commands ---------
void LifterSubsystem::L1Command() {
    if (currentState == State::Idle) {
        SetState(State::L1);
    }
}

void LifterSubsystem::L15Command() {
    if (currentState == State::Idle) {
        SetState(State::L15);
    }
}

void LifterSubsystem::L2Command() {
    if (currentState == State::Idle) {
        SetState(State::L2);
    }
}

void LifterSubsystem::L25Command() {
    if (currentState == State::Idle) {
        SetState(State::L25);
    }
}

void LifterSubsystem::L3Command() {
    if (currentState == State::Idle) {
        SetState(State::L3);
    }
}
