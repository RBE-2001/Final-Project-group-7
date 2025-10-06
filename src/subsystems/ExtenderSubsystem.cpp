#include "ExtenderSubsystem.h"

// --------- Susytems Functions ---------
void ExtenderSubsystem::Init() {
    currentState = State::Idle;
    isExtended = false;

#ifdef __SUBSYSTEM_DEBUG
    Serial.println("ExtenderSubsystem -> Initilized");
#endif
}

void ExtenderSubsystem::Update() {
    switch (currentState) {
        case State::Idle:
            Idle();
            break;

        case State::Extending:
            Extend();
            break;

        case State::Retracting:
            Retract();
            break;
    }
}

bool ExtenderSubsystem::IsDone() const {
    return currentState == State::Idle;
}

// --------- States ---------
void ExtenderSubsystem::Idle() {
#ifdef __SUBSYSTEM_DEBUG
    Serial.println("ExtenderSubsystem -> IDLE");
#endif
    //TODO: stop motors
}

void ExtenderSubsystem::Extend() {
#ifdef __SUBSYSTEM_DEBUG
    Serial.println("ExtenderSubsystem -> Extending");
#endif
    // TODO: replace with Extend extending code

    if (true) { //TODO: replace true with logic for when Extender is extended
        isExtended = true;
        SetState(State::Idle);  // go back to idle when done
    }
}

void ExtenderSubsystem::Retract() {
#ifdef __SUBSYSTEM_DEBUG
    Serial.println("ExtenderSubsystem -> Retracting");
#endif
    // TODO: replace with Extend Retract code

    if (true) { //TODO: replace true with logic for when Extender is Retracted
        isExtended = false;
        SetState(State::Idle);  // go back to idle when done
    }
}

void ExtenderSubsystem::SetState(State newState) {
    currentState = newState;
}

// --------- Commands ---------
void ExtenderSubsystem::ExtendCommand() {
    if (currentState == State::Idle && !isExtended) {
        SetState(State::Extending);
    }
}

void ExtenderSubsystem::RetractCommand() {
    if (currentState == State::Idle && isExtended) {
        SetState(State::Retracting);
    }
}
