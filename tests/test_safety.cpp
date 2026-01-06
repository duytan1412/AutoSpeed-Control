#include "../src/CarController.h"
#include <gtest/gtest.h>


/**
 * @file test_safety.cpp
 * @brief Unit tests for CarController safety features
 *
 * Test Categories:
 * 1. Safety Tests - Critical safety rule verification
 * 2. Boundary Tests - Edge case and limit testing
 * 3. State Tests - Gear transition validation
 */

// ============================================================================
// SAFETY TESTS - Critical for Automotive (ISO 26262)
// ============================================================================

/**
 * @test PreventReverseWhileDriving
 * @brief Verify car cannot shift to Reverse when moving forward
 * @details This is a CRITICAL safety feature - violating this can cause
 * accidents
 */
TEST(SafetyTest, PreventReverseWhileDriving) {
  CarController car;

  // Setup: Car is moving at 50 km/h in Drive
  car.setBrake(true);
  car.setGear(CarController::GEAR_DRIVE);
  car.setBrake(false);
  car.setThrottle(100);

  // Simulate driving to reach speed
  for (int i = 0; i < 20; ++i) {
    car.update();
  }

  // Verify car is moving
  ASSERT_GT(car.getSpeed(), 0) << "Car should be moving";

  // Action: Attempt to shift to Reverse while moving
  bool gearChangeResult = car.setGear(CarController::GEAR_REVERSE);

  // Assertion: Gear change MUST be rejected
  ASSERT_FALSE(gearChangeResult) << "Gear change to R while moving MUST fail";
  ASSERT_NE(car.getGear(), CarController::GEAR_REVERSE)
      << "Gear MUST NOT be Reverse when car was moving";
}

/**
 * @test BrakeOverrideThrottle
 * @brief Verify brake ALWAYS takes priority over throttle
 * @details Brake Override System (BOS) - critical for unintended acceleration
 * prevention
 */
TEST(SafetyTest, BrakeOverrideThrottle) {
  CarController car;

  // Setup: Car moving at some speed
  car.setBrake(true);
  car.setGear(CarController::GEAR_DRIVE);
  car.setBrake(false);
  car.setThrottle(100);

  for (int i = 0; i < 15; ++i) {
    car.update();
  }

  int initialSpeed = car.getSpeed();
  ASSERT_GT(initialSpeed, 0) << "Car should be moving";

  // Action: Press brake while throttle is still 100%
  car.setBrake(true);
  car.update();

  // Assertion: Speed MUST decrease despite full throttle
  ASSERT_LT(car.getSpeed(), initialSpeed)
      << "Speed MUST decrease when brake is pressed, regardless of throttle";
}

/**
 * @test MaxSpeedLimit
 * @brief Verify car cannot exceed maximum speed limit
 * @details Speed limiter - prevents dangerous overspeeding
 */
TEST(BoundaryTest, MaxSpeedLimit) {
  CarController car;

  // Setup: Full throttle in Drive
  car.setBrake(true);
  car.setGear(CarController::GEAR_DRIVE);
  car.setBrake(false);
  car.setThrottle(100);

  // Action: Accelerate for extended period (simulating long highway drive)
  for (int i = 0; i < 1000; ++i) {
    car.update();
  }

  // Assertion: Speed must not exceed MAX_SPEED
  ASSERT_LE(car.getSpeed(), CarController::MAX_SPEED)
      << "Speed MUST NOT exceed " << CarController::MAX_SPEED << " km/h";
}

/**
 * @test AllowReverseWhenStopped
 * @brief Verify car CAN shift to Reverse when completely stopped
 * @details Valid use case - reverse should work when safe
 */
TEST(SafetyTest, AllowReverseWhenStopped) {
  CarController car;

  // Setup: Car is completely stopped
  ASSERT_EQ(car.getSpeed(), 0) << "Car should start at 0 speed";

  // Action: Press brake and shift to Reverse
  car.setBrake(true);
  bool result = car.setGear(CarController::GEAR_REVERSE);

  // Assertion: Should succeed when stopped
  ASSERT_TRUE(result) << "Should be able to shift to R when stopped";
  ASSERT_EQ(car.getGear(), CarController::GEAR_REVERSE);
}

/**
 * @test GearParkRequiresBrake
 * @brief Verify shifting to Park requires brake to be pressed
 * @details Safety interlock - prevents accidental Park engagement
 */
TEST(SafetyTest, GearParkRequiresBrake) {
  CarController car;

  // Setup: Car stopped but brake NOT pressed
  car.setBrake(true);
  car.setGear(CarController::GEAR_NEUTRAL);
  car.setBrake(false); // Release brake

  // Action: Try to shift to Park without brake
  bool result = car.setGear(CarController::GEAR_PARK);

  // Assertion: Should be rejected
  ASSERT_FALSE(result) << "Should NOT shift to P without brake pressed";

  // Now press brake and try again
  car.setBrake(true);
  result = car.setGear(CarController::GEAR_PARK);

  // Assertion: Should succeed now
  ASSERT_TRUE(result) << "Should shift to P when brake is pressed";
}

// ============================================================================
// ADDITIONAL TESTS
// ============================================================================

/**
 * @test ThrottleClampedTo100
 * @brief Verify throttle is clamped to valid range 0-100
 */
TEST(BoundaryTest, ThrottleClampedToValidRange) {
  CarController car;

  // Test upper bound
  car.setThrottle(150);
  ASSERT_EQ(car.getThrottle(), 100) << "Throttle should be clamped to 100";

  // Test lower bound
  car.setThrottle(-50);
  ASSERT_EQ(car.getThrottle(), 0) << "Throttle should be clamped to 0";
}

/**
 * @test SpeedNeverNegative
 * @brief Verify speed never goes negative
 */
TEST(BoundaryTest, SpeedNeverNegative) {
  CarController car;

  // Apply brake many times when already at 0
  car.setBrake(true);
  for (int i = 0; i < 100; ++i) {
    car.update();
  }

  ASSERT_GE(car.getSpeed(), 0) << "Speed must never be negative";
}

// ============================================================================
// ADDITIONAL TESTS (3 more to reach 10 total)
// ============================================================================

/**
 * @test EmergencyBrakeAtHighSpeed
 * @brief Verify emergency braking works at high speed
 * @details Critical safety test for panic braking scenarios
 */
TEST(SafetyTest, EmergencyBrakeAtHighSpeed) {
  CarController car;

  // Setup: Drive to high speed
  car.setBrake(true);
  car.setGear(CarController::GEAR_DRIVE);
  car.setBrake(false);
  car.setThrottle(100);

  // Accelerate to near max speed
  for (int i = 0; i < 200; ++i) {
    car.update();
  }

  int highSpeed = car.getSpeed();
  ASSERT_GT(highSpeed, 100) << "Should be at high speed";

  // Emergency brake!
  car.setBrake(true);
  car.update();
  car.update();
  car.update();

  // Speed must significantly decrease
  ASSERT_LT(car.getSpeed(), highSpeed)
      << "Emergency braking must reduce speed immediately";
}

/**
 * @test NeutralGearNoAcceleration
 * @brief Verify car cannot accelerate in Neutral gear
 * @details Safety feature - N gear should not respond to throttle
 */
TEST(SafetyTest, NeutralGearNoAcceleration) {
  CarController car;

  // Setup: Switch to Neutral
  car.setBrake(true);
  car.setGear(CarController::GEAR_NEUTRAL);
  car.setBrake(false);

  // Try to accelerate in Neutral
  car.setThrottle(100);

  int initialSpeed = car.getSpeed();
  for (int i = 0; i < 50; ++i) {
    car.update();
  }

  // Speed should NOT increase in Neutral
  ASSERT_LE(car.getSpeed(), initialSpeed)
      << "Car must NOT accelerate in Neutral gear";
}

/**
 * @test ConsecutiveGearChanges
 * @brief Verify rapid gear changes follow safety rules
 * @details Stress test for gear state machine
 */
TEST(StateTest, ConsecutiveGearChanges) {
  CarController car;

  // Valid sequence when stopped with brake: P -> R -> N -> D -> N -> R -> P
  car.setBrake(true);

  ASSERT_TRUE(car.setGear(CarController::GEAR_REVERSE)) << "P->R should work";
  ASSERT_EQ(car.getGear(), CarController::GEAR_REVERSE);

  ASSERT_TRUE(car.setGear(CarController::GEAR_NEUTRAL)) << "R->N should work";
  ASSERT_EQ(car.getGear(), CarController::GEAR_NEUTRAL);

  ASSERT_TRUE(car.setGear(CarController::GEAR_DRIVE)) << "N->D should work";
  ASSERT_EQ(car.getGear(), CarController::GEAR_DRIVE);

  ASSERT_TRUE(car.setGear(CarController::GEAR_NEUTRAL)) << "D->N should work";
  ASSERT_TRUE(car.setGear(CarController::GEAR_REVERSE)) << "N->R should work";
  ASSERT_TRUE(car.setGear(CarController::GEAR_PARK)) << "R->P should work";

  ASSERT_EQ(car.getGear(), CarController::GEAR_PARK)
      << "Should end in Park after valid sequence";
}

// Main function for running tests
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
