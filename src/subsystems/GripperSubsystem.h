#pragma once
#include "Subsystem.h"

class GripperSubsystem : public Subsystem {
public:
    void Init() override;
    void Update() override;
    bool IsDone() const override;

    void OpenCommand();   // trigger opening
    void CloseCommand();  // trigger closing

private:
    enum class State {
        Idle,
        Opening,
        Closing
    };

    State currentState = State::Idle;
    State previousState = State::Idle;
    
    bool isGripperOpen = false;

    void SetState(State newState);
    void Idle();
    void Open();
    void Close();
};
