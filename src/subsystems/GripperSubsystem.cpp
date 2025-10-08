#include "GripperSubsystem.h"

// --------- Susytems Functions ---------
void GripperSubsystem::Init() {
    currentState = State::Idle;
    isGripperOpen = false;
    servo.attach();

#ifdef __SUBSYSTEM_DEBUG
    Serial.println("GripperSubsystem -> Initilized");
#endif
}

void GripperSubsystem::Update() {
    switch (currentState) {
        case State::Idle:
            Idle();
            break;

        case State::Opening:
            goTo(1000);
            break;

        case State::Closing:
            goTo(2000);
            break;
    }

    servo.update();
}

bool GripperSubsystem::IsDone() const {
    return currentState == State::Idle;
}

// --------- States ---------
void GripperSubsystem::Idle() {
    //TODO: stop motors
}

void GripperSubsystem::goTo(uint16_t goal) {
    // TODO: replace with open gripper code
    servo.setTargetPos(goal);
    
    Serial.print("going to goal: ");
    Serial.println(goal);
    isGripperOpen = !isGripperOpen;
    SetState(State::Idle);
}

void GripperSubsystem::SetState(State newState) {
    if (newState != currentState) {
        previousState = currentState;
        currentState = newState;

    #ifdef __SUBSYSTEM_DEBUG
        switch (newState) {
            case State::Idle:       Serial.println("GripperSubsystem -> Entering IDLE"); break;
            case State::Opening:  Serial.println("GripperSubsystem -> Entering Opening"); break;
            case State::Closing: Serial.println("GripperSubsystem -> Entering Closing"); break;
        }
    #endif
    }
}

// --------- Commands ---------

void GripperSubsystem::OpenCommand() {
    if (currentState == State::Idle && !isGripperOpen) {
        SetState(State::Opening);
    }
}

void GripperSubsystem::CloseCommand() {
    if (currentState == State::Idle && isGripperOpen) {
        SetState(State::Closing);
    }
}
