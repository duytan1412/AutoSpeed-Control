#ifndef CAR_CONTROLLER_H
#define CAR_CONTROLLER_H

/**
 * @file CarController.h
 * @brief Header file for automotive speed control simulation
 * @details Implements safety-critical car control logic for Embedded Tester portfolio
 * 
 * FPT Software Automotive - Unit Testing Demo Project
 */

/**
 * @class CarController
 * @brief Manages vehicle speed, gear, brake, and throttle states
 * 
 * Safety Features:
 * - Prevents reverse gear when vehicle is moving forward
 * - Brake overrides throttle input
 * - Maximum speed limiter (200 km/h)
 * - Park gear requires complete stop and brake
 */
class CarController {
public:
    // Gear constants
    static constexpr char GEAR_PARK = 'P';
    static constexpr char GEAR_REVERSE = 'R';
    static constexpr char GEAR_NEUTRAL = 'N';
    static constexpr char GEAR_DRIVE = 'D';
    
    // Speed constants
    static constexpr int MAX_SPEED = 200;      // km/h
    static constexpr int ACCELERATION = 5;     // km/h per update
    static constexpr int DECELERATION = 10;    // km/h per update when braking
    static constexpr int NATURAL_DECEL = 1;    // km/h per update (no input)
    
    /**
     * @brief Constructor - initializes vehicle to parked state
     */
    CarController();
    
    /**
     * @brief Update vehicle state based on current inputs
     * @details Called every simulation cycle to update speed
     * 
     * Logic:
     * - If brake is pressed: speed decreases by DECELERATION
     * - If throttle > 0 AND gear is D AND no brake: speed increases
     * - Otherwise: speed naturally decreases
     */
    void update();
    
    /**
     * @brief Attempt to change gear
     * @param newGear Target gear (P, R, N, D)
     * @return true if gear change successful, false if blocked by safety
     * 
     * Safety Rules:
     * - Cannot shift to R if speed > 0
     * - Cannot shift to P if speed > 0 or brake not pressed
     */
    bool setGear(char newGear);
    
    /**
     * @brief Set throttle position
     * @param value Throttle percentage (0-100)
     */
    void setThrottle(int value);
    
    /**
     * @brief Set brake state
     * @param pressed true if brake pedal is pressed
     */
    void setBrake(bool pressed);
    
    // Getters
    int getSpeed() const { return speed_; }
    char getGear() const { return gear_; }
    bool isBraking() const { return brake_; }
    int getThrottle() const { return throttle_; }
    
private:
    int speed_;       // Current speed in km/h
    char gear_;       // Current gear (P, R, N, D)
    bool brake_;      // Brake pedal state
    int throttle_;    // Throttle position (0-100)
    
    /**
     * @brief Validate if gear is valid
     * @param g Gear character to validate
     * @return true if valid gear
     */
    bool isValidGear(char g) const;
};

#endif // CAR_CONTROLLER_H
