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
#ifdef __SUBSYSTEM_DEBUG
    Serial.println("GripperSubsystem -> IDLE");
#endif
    //TODO: stop motors
}

void GripperSubsystem::Open() {
#ifdef __SUBSYSTEM_DEBUG
    Serial.println("GripperSubsystem -> Open");
#endif
    // TODO: replace with open gripper code

    if (true) { //TODO: replace true with logic for when gripper is open
        isGripperOpen = true;
        SetState(State::Idle);  // go back to idle when done
    }
}

void GripperSubsystem::Close() {
#ifdef __SUBSYSTEM_DEBUG
    Serial.println("GripperSubsystem -> Closed");
#endif
    // TODO: replace with close gripper code

    if (true) { //TODO: replace true with logic for when gripper is closed
        isGripperOpen = false;
        SetState(State::Idle);  // go back to idle when done
    }
}

void GripperSubsystem::SetState(State newState) {
    currentState = newState;
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
