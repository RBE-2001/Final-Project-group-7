#pragma once

#include "chassis.h"

#include <vector>
#include "Subsystem.h"

class ChassisSubsystem : public Subsystem {
public:
    void Init() override;
    void Update() override;
    bool IsDone() const override;

    void SetDestinationCommand();
private:
    enum class State {
        Idle,
        DRIVE_TO_POINT,
    };

    State currentState = State::Idle;
    State previousState = State::Idle;
    
    void SetState(State newState);
    void Idle();
    void DriveToPoint();

    // Helper functions
    void UpdatePose(const Twist& u);
    bool CheckReachedDestination(void);

protected:
    /* Define the chassis*/
    Chassis chassis;

    /**
     * For tracking current pose and the destination.
     */
    Pose currPose;
    Pose destPose;

    // For driving an array of points
    unsigned int point_index = 0;

    // TODO: update to go around  optical
    std::vector<Pose> points = {
        {30, 30, 0},
        {60, 0, 0},
        {30, -30, 0},
        {-30, 30, 0},
        {0, 0, 0}
    };
};