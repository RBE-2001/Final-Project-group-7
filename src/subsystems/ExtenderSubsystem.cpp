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

        case State::ExtendingTop:
            ExtendTop();
            break;
        
        case State::ExtendingBottom:
            ExtendBottom();
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
    //TODO: stop motors
    motor.setEffort(0);
}

void ExtenderSubsystem::ExtendTop() {
    // TODO: replace with Extend extending code
    motor.setEffort(-400);
    
    if (motor.getPosition() <= -150.0) { //TODO: replace true with logic for when Extender is extended
        motor.setEffort(0);
        isExtended = true;
        SetState(State::Idle);  // go back to idle when done
    }
}
void ExtenderSubsystem::ExtendBottom() {
    // TODO: replace with Extend extending code
    motor.setEffort(-400);
    
    if (motor.getPosition() <= -100.0) { //TODO: replace true with logic for when Extender is extended
        motor.setEffort(0);
        isExtended = true;
        SetState(State::Idle);  // go back to idle when done
    }
}

void ExtenderSubsystem::Retract() {
    // TODO: replace with Extend Retract code
    motor.setEffort(400);
    if (motor.getPosition() > -25) { //TODO: replace true with logic for when Extender is Retracted
        isExtended = false;
        SetState(State::Idle);  // go back to idle when done
    }
}

void ExtenderSubsystem::SetState(State newState) {
    if (newState != currentState) {
        previousState = currentState;
        currentState = newState;

    #ifdef __SUBSYSTEM_DEBUG
        switch (newState) {
            case State::Idle:       Serial.println("ExtenderSubsystem -> Entering IDLE"); break;
            case State::ExtendingTop:  Serial.println("ExtenderSubsystem -> Entering EXTENDING"); break;
            case State::ExtendingBottom:  Serial.println("ExtenderSubsystem -> Entering EXTENDING"); break;
            case State::Retracting: Serial.println("ExtenderSubsystem -> Entering RETRACTING"); break;
        }
    #endif
    }
}

// --------- Commands ---------
void ExtenderSubsystem::ExtendTopCommand() {
    if (currentState == State::Idle && !isExtended) {
        SetState(State::ExtendingTop);
    }
}

void ExtenderSubsystem::ExtendBottomCommand() {
    if (currentState == State::Idle && !isExtended) {
        SetState(State::ExtendingBottom);
    }
}

void ExtenderSubsystem::RetractCommand() {
    if (currentState == State::Idle && isExtended) {
        SetState(State::Retracting);
    }
}
