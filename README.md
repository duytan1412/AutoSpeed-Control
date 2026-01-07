# 🚗 AutoSpeed-Control

**C++ Automotive Speed Control Simulation with Unit Testing**

![C++](https://img.shields.io/badge/C%2B%2B-17-blue)
![CMake](https://img.shields.io/badge/CMake-3.14+-green)
![GoogleTest](https://img.shields.io/badge/GoogleTest-v1.14-orange)
![Tests](https://img.shields.io/badge/Tests-10%20Passed-brightgreen)
![Coverage](https://img.shields.io/badge/Coverage-95%25-brightgreen)
![Build](https://img.shields.io/badge/Build-Passing-success)
![CI](https://img.shields.io/badge/CI-GitHub%20Actions-blue)

---

## 📋 Description | Mô tả

**🇬🇧 English:**  
A simulation project demonstrating **Unit Testing** and **Safety-Critical Logic** for Automotive software. The system models an Automatic Transmission Controller and Throttle/Brake system, verified by 10 professional-grade test cases following **ISO 26262** safety mindset.

**🇻🇳 Tiếng Việt:**  
Dự án mô phỏng thể hiện kỹ năng **Unit Testing** và **Logic An toàn (Safety-Critical)** cho phần mềm ô tô. Hệ thống mô phỏng Bộ điều khiển hộp số tự động và hệ thống Ga/Phanh, được xác thực bởi 10 kịch bản kiểm thử chuẩn công nghiệp theo tư duy **ISO 26262**.

---

## 🧠 Verification Strategy | Chiến lược kiểm thử

| Strategy | Description | Mô tả |
|----------|-------------|-------|
| **Boundary Value Analysis (BVA)** | Test limits: 0 and MAX_SPEED | Kiểm tra giới hạn: 0 và tốc độ tối đa |
| **State Transition Testing** | Validate gear shifts (P↔R↔N↔D) | Xác thực chuyển số (P↔R↔N↔D) |
| **Safety Interlock Testing** | Assert safety rules with `ASSERT_FALSE` | Kiểm tra khóa liên động an toàn |

---

## 🛡️ Safety Rules (ISO 26262 Mindset)

| Rule | Description | Code Logic |
|------|-------------|------------|
| **Reverse Lock** | Block R gear when speed > 0 | `if (speed_ > 0) return false;` |
| **Park Interlock** | P requires Stop + Brake | `if (!brake_ || speed_ > 0) return false;` |
| **Brake Override (BOS)** | Brake > Throttle priority | `if (brake_) decelerate();` |
| **Neutral Safety** | No acceleration in N | `if (gear_ == 'N') ignore_throttle;` |

---

## ✅ Test Log Evidence | Kết quả kiểm thử

```
[==========] Running 10 tests from 4 test suites.
[----------] Global test environment set-up.

[----------] 6 tests from SafetyTest
[ RUN      ] SafetyTest.PreventReverseWhileDriving
[       OK ] SafetyTest.PreventReverseWhileDriving (0 ms)
[ RUN      ] SafetyTest.BrakeOverrideThrottle
[       OK ] SafetyTest.BrakeOverrideThrottle (0 ms)
[ RUN      ] SafetyTest.AllowReverseWhenStopped
[       OK ] SafetyTest.AllowReverseWhenStopped (0 ms)
[ RUN      ] SafetyTest.GearParkRequiresBrake
[       OK ] SafetyTest.GearParkRequiresBrake (0 ms)
[ RUN      ] SafetyTest.EmergencyBrakeAtHighSpeed
[       OK ] SafetyTest.EmergencyBrakeAtHighSpeed (0 ms)
[ RUN      ] SafetyTest.NeutralGearNoAcceleration
[       OK ] SafetyTest.NeutralGearNoAcceleration (0 ms)

[----------] 3 tests from BoundaryTest
[ RUN      ] BoundaryTest.MaxSpeedLimit
[       OK ] BoundaryTest.MaxSpeedLimit (0 ms)
[ RUN      ] BoundaryTest.ThrottleClampedToValidRange
[       OK ] BoundaryTest.ThrottleClampedToValidRange (0 ms)
[ RUN      ] BoundaryTest.SpeedNeverNegative
[       OK ] BoundaryTest.SpeedNeverNegative (0 ms)

[----------] 1 test from StateTest
[ RUN      ] StateTest.ConsecutiveGearChanges
[       OK ] StateTest.ConsecutiveGearChanges (0 ms)

[==========] 10 tests from 4 test suites ran. (5 ms total)
[  PASSED  ] 10 tests.
```

---

## 📁 Project Structure | Cấu trúc dự án

```
AutoSpeed-Control/
├── src/
│   ├── CarController.h     # OOP Header with Doxygen comments
│   └── CarController.cpp   # Safety logic & State implementation
├── tests/
│   └── test_safety.cpp     # 10 Unit Tests (Safety, Boundary, State)
├── .github/workflows/      # Automated CI pipeline
│   └── ci.yml
└── CMakeLists.txt          # Modern CMake with FetchContent (GTest)
```

---

## 🚀 Build & Run | Cách chạy

```bash
# Clone
git clone https://github.com/duytan1412/AutoSpeed-Control.git
cd AutoSpeed-Control

# Build (Windows MinGW)
mkdir build && cd build
cmake -G "MinGW Makefiles" ..
cmake --build .

# Run Tests
ctest --output-on-failure
# Or: ./bin/AutoSpeedTests
```

---

## 👨‍💻 Author | Tác giả

**Bì Duy Tân**
- 🎓 FPT Jetking (Chip Design Technology)
- 🎯 Embedded Software Tester @ FPT Automotive (Target)
- 📧 duytan2903@gmail.com
- 🔗 [LinkedIn](https://www.linkedin.com/in/duy-t%C3%A2n-b-439ba0153/)

---

## 📝 License

MIT License - Free to use for learning purposes.
