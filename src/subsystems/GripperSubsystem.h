#pragma once
#include "Subsystem.h"

#include "servo32u4.h"

class GripperSubsystem : public Subsystem {
public:
    void Init() override;
    void Update() override;
    bool IsDone() const override;

    void Toggle();   // trigger opening

private:
    enum class State {
        Idle,
        Toggle,
    };

    State currentState = State::Idle;
    State previousState = State::Idle;

    Servo32U4Pin5 servo;
    
    bool isGripperOpen = false;

    void SetState(State newState);
    void Idle();
    void goTo(uint16_t pose);
};
