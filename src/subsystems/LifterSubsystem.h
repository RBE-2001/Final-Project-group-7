#pragma once
#include "Subsystem.h"
#include "DualBlueMotor.h"

class LifterSubsystem : public Subsystem {
public:

    void Init() override;
    void Update() override;
    bool IsDone() const override;

    void L1Command();
    void L15Command();
    void L2Command();
    void L25Command();
    void L3Command();

private:
    enum class State {
        Idle,
        L1,
        L15,
        L2,
        L25,
        L3,
    };

    State currentState = State::Idle;
    State previousState = State::Idle;

    void SetState(State newState);
    void Idle();
    void GoToL(float rot);
};