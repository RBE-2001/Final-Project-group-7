#include "GripperSubsystem.h"

// --------- Susytems Functions ---------
void GripperSubsystem::Init() {
    currentState = State::Idle;
    isGripperOpen = false;

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
            Open();
            break;

        case State::Closing:
            Close();
            break;
    }
}

bool GripperSubsystem::IsDone() const {
    return currentState == State::Idle;
}

// --------- States ---------
void GripperSubsystem::Idle() {
    //TODO: stop motors
}

void GripperSubsystem::Open() {
    // TODO: replace with open gripper code

    if (true) { //TODO: replace true with logic for when gripper is open
        isGripperOpen = true;
        SetState(State::Idle);  // go back to idle when done
    }
}

void GripperSubsystem::Close() {
    // TODO: replace with close gripper code

    if (true) { //TODO: replace true with logic for when gripper is closed
        isGripperOpen = false;
        SetState(State::Idle);  // go back to idle when done
    }
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
