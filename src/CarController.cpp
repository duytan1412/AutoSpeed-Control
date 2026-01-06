#include "CarController.h"

/**
 * @file CarController.cpp
 * @brief Implementation of automotive speed control simulation
 */

CarController::CarController()
    : speed_(0)
    , gear_(GEAR_PARK)
    , brake_(false)
    , throttle_(0)
{
}

void CarController::update()
{
    // Safety Rule 1: Brake ALWAYS overrides throttle
    if (brake_) {
        // Apply braking deceleration
        speed_ -= DECELERATION;
        if (speed_ < 0) {
            speed_ = 0;
        }
        return;  // Brake takes priority, ignore throttle
    }
    
    // Gear-based speed update
    switch (gear_) {
        case GEAR_DRIVE:
            if (throttle_ > 0) {
                // Accelerate based on throttle (simplified linear model)
                int accel = (throttle_ * ACCELERATION) / 100;
                speed_ += accel > 0 ? accel : 1;
                
                // Safety Rule 2: Enforce max speed limit
                if (speed_ > MAX_SPEED) {
                    speed_ = MAX_SPEED;
                }
            } else {
                // Natural deceleration when no throttle
                speed_ -= NATURAL_DECEL;
                if (speed_ < 0) speed_ = 0;
            }
            break;
            
        case GEAR_REVERSE:
            if (throttle_ > 0) {
                // Reverse has lower max speed (-30 km/h conceptually, stored as positive)
                int accel = (throttle_ * ACCELERATION) / 200;  // Half acceleration
                speed_ += accel > 0 ? accel : 1;
                
                // Max reverse speed is 30 km/h
                if (speed_ > 30) {
                    speed_ = 30;
                }
            } else {
                speed_ -= NATURAL_DECEL;
                if (speed_ < 0) speed_ = 0;
            }
            break;
            
        case GEAR_NEUTRAL:
        case GEAR_PARK:
        default:
            // In N or P, speed naturally decreases
            speed_ -= NATURAL_DECEL;
            if (speed_ < 0) speed_ = 0;
            break;
    }
}

bool CarController::setGear(char newGear)
{
    // Validate new gear
    if (!isValidGear(newGear)) {
        return false;
    }
    
    // Safety Rule 3: Cannot shift to REVERSE if moving forward
    if (newGear == GEAR_REVERSE && speed_ > 0) {
        return false;  // REJECT - safety violation!
    }
    
    // Safety Rule 4: Cannot shift to PARK if moving or brake not pressed
    if (newGear == GEAR_PARK) {
        if (speed_ > 0) {
            return false;  // Must be stopped
        }
        if (!brake_) {
            return false;  // Must have brake pressed
        }
    }
    
    // Safety Rule 5: Cannot shift from PARK without brake pressed
    if (gear_ == GEAR_PARK && newGear != GEAR_PARK && !brake_) {
        return false;
    }
    
    // All safety checks passed
    gear_ = newGear;
    return true;
}

void CarController::setThrottle(int value)
{
    // Clamp throttle to valid range
    if (value < 0) {
        throttle_ = 0;
    } else if (value > 100) {
        throttle_ = 100;
    } else {
        throttle_ = value;
    }
}

void CarController::setBrake(bool pressed)
{
    brake_ = pressed;
}

bool CarController::isValidGear(char g) const
{
    return g == GEAR_PARK || 
           g == GEAR_REVERSE || 
           g == GEAR_NEUTRAL || 
           g == GEAR_DRIVE;
}
