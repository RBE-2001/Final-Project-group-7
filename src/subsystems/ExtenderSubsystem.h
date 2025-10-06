#pragma once
#include "Subsystem.h"
#include "DualBlueMotor.h"

class ExtenderSubsystem : public Subsystem {
public:
    DualBlueMotor dualMotor
    ExtenderSubsystem(DualBlueMotor dm) {
        dualMotor = dm
    }
    
    void Init() override;
    void Update() override;
    bool IsDone() const override;

    void ExtendCommand();   // trigger opening
    void RetractCommand();  // trigger closing

private:
    enum class State {
        Idle,
        Extending,
        Retracting
    };

    State currentState = State::Idle;
    State previousState = State::Idle;
    
    bool isExtended = false;

    void SetState(State newState);
    void Idle();
    void Extend();
    void Retract();

    DualBlueMotor dualMotor = DualBlueMotor();
    
};
