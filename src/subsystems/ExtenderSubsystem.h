#pragma once
#include "Subsystem.h"

#include "BlueMotorExtender.h"

class ExtenderSubsystem : public Subsystem {
public:
    
    void Init() override;
    void Update() override;
    bool IsDone() const override;

    void ExtendTopCommand();   // trigger opening
    void ExtendBottomCommand();   // trigger opening
    void RetractCommand();  // trigger closing

private:
    enum class State {
        Idle,
        ExtendingTop,
        ExtendingBottom,
        Retracting
    };

    BlueMotorExtender motor;

    State currentState = State::Idle;
    State previousState = State::Idle;
    
    bool isExtended = false;

    void SetState(State newState);
    void Idle();
    void ExtendTop();
    void ExtendBottom();
    void Retract();
};
