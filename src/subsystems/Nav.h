#include "chassis.h"

#include <vector>

class Nav
{
public:
    enum ROBOT_STATE 
    {
        ROBOT_IDLE,
        ROBOT_DRIVE_TO_POINT, 
    };
    ROBOT_STATE robotState = ROBOT_IDLE;

protected:
    /* Define the chassis*/
    Chassis chassis;

    /**
     * For tracking current pose and the destination.
     */
    Pose currPose;
    Pose destPose;

    // For going to array of points
    unsigned int point_index = 0;

    // TODO: update to go around  optical
    std::vector<Pose> points = {
        {30, 30, 0},
        {60, 0, 0},
        {30, -30, 0},
        {-30, 30, 0},
        {0, 0, 0}
    };

    
    void SetDestination(const Pose& destination);

    // Navigation methods.
    void UpdatePose(const Twist& u);
    void DriveToPoint(void);
    bool CheckReachedDestination(void);
    void HandleDestination(void);
};