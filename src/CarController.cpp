#include "CarController.h"

// Implementation of automotive speed control logic

CarController::CarController()
    : speed_(0)
    , gear_(GEAR_PARK)
    , brake_(false)
    , throttle_(0)
{
}

void CarController::update()
{
    if (brake_) {
        speed_ -= DECELERATION;
        if (speed_ < 0) speed_ = 0;
        return; // Brake priority
    }
    
    // Gear-based speed update
    switch (gear_) {
        case GEAR_DRIVE:
            if (throttle_ > 0) {
                int accel = (throttle_ * ACCELERATION) / 100;
                speed_ += accel > 0 ? accel : 1;
                
                if (speed_ > MAX_SPEED) speed_ = MAX_SPEED;
            } else {
                speed_ -= NATURAL_DECEL;
                if (speed_ < 0) speed_ = 0;
            }
            break;
            
        case GEAR_REVERSE:
            if (throttle_ > 0) {
                int accel = (throttle_ * ACCELERATION) / 200;
                speed_ += accel > 0 ? accel : 1;
                
                if (speed_ > 30) speed_ = 30;
            } else {
                speed_ -= NATURAL_DECEL;
                if (speed_ < 0) speed_ = 0;
            }
            break;
            
        case GEAR_NEUTRAL:
        case GEAR_PARK:
        default:
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
    
    // Shift Gear with Interlocks
    if (newGear == GEAR_REVERSE && speed_ > 0) return false;
    
    if (newGear == GEAR_PARK && (speed_ > 0 || !brake_)) return false;
    
    if (gear_ == GEAR_PARK && newGear != GEAR_PARK && !brake_) return false;

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
