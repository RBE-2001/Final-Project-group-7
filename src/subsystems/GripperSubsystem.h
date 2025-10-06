#pragma once
#include "Subsystem.h"

class GripperSubsystem : public Subsystem {
public:
    void Init() override;
    void Update() override;
    bool IsDone() const override;

    enum class State {
        Idle,
        Opening,
        Closing
    };
    void SetState(State newState);

private:
    State currentState = State::Idle;
    bool isGripperOpen = false;  // Tracks physical state

    // Code to controll griper
    void Open();   // Trigger opening
    void Close();  // Trigger closing
    void Idle();
};
