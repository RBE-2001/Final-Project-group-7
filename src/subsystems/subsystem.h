// Subsystem.h
#pragma once

#include "Romi32U4Buttons.h"
#include <Arduino.h>

class Subsystem {
public:
    virtual ~Subsystem() = default;

    // Called to initialize the subsystem
    virtual void Init() {}
    // Called regularly (e.g., every control loop cycle)
    virtual void Update() {};
    // Called to check if the current operation is done
    virtual bool IsDone() const { return true; }
};