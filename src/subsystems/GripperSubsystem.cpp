#include "GripperSubsystem.h"

// Initialize the gripper
void GripperSubsystem::Init() {
    currentState = State::Idle;
    isGripperOpen = false;
}

// Update is called in the control loop
void GripperSubsystem::Update() {
    switch (currentState) {
        case State::Idle:
            Idle();
            break;

        case State::Opening:
            if (!isGripperOpen) {
                Open();
            }
            break;

        case State::Closing:
            if (isGripperOpen) {
                Close();
            }
            break;
    }
}

// Check if the gripper is done
bool GripperSubsystem::IsDone() const {
    return currentState == State::Idle;
}

// Idle state
void GripperSubsystem::Idle() {
    // TODO: Code for idle State, Stop servo
}

// Trigger opening
void GripperSubsystem::Open() {
    if (currentState == State::Opening && !isGripperOpen) {
        // TODO: Code to open gripper

        // sets state to idle when griper is open
        if (true) { // replace true with logic for when gripper is open
            SetState(State::Idle);
            isGripperOpen = true;
        }
    }
}

// Trigger closing
void GripperSubsystem::Close() {
    if (currentState == State::Idle && isGripperOpen) {
        // TODO: Code to closed gripper
        
        // sets state to idle when griper is closed
        if (true) { // replace true with logic for when gripper is closed
            SetState(State::Idle);
            isGripperOpen = false;
        }
    }
}

// Internal state change
void GripperSubsystem::SetState(State newState) {
    currentState = newState;
}
