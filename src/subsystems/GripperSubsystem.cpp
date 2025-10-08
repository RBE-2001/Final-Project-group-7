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

        case State::Toggle:
            goTo(1000);
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

int cnt = 0;

void GripperSubsystem::goTo(uint16_t goal) {
    // TODO: replace with open gripper code
    if (isGripperOpen) {
        servo.setTargetPos(1000);
    } else
    {
        servo.setTargetPos(2000);
    }
    cnt += 1;
    Serial.print("going to goal: ");
    Serial.println(goal);

    if (cnt > 50) {
        isGripperOpen = !isGripperOpen;
        SetState(State::Idle);
    }
}

void GripperSubsystem::SetState(State newState) {
    cnt = 0;
    if (newState != currentState) {
        previousState = currentState;
        currentState = newState;

    #ifdef __SUBSYSTEM_DEBUG
        switch (newState) {
            case State::Idle:       Serial.println("GripperSubsystem -> Entering IDLE"); break;
            case State::Toggle:  Serial.println("GripperSubsystem -> Entering Opening"); break;
        }
    #endif
    }
}

// --------- Commands ---------

void GripperSubsystem::Toggle() {
    if (currentState == State::Idle) {
        SetState(State::Toggle);
    }
}
