# 🚗 AutoSpeed-Control

**C++ Automotive Speed Control Simulation with Unit Testing**

![C++](https://img.shields.io/badge/C%2B%2B-17-blue)
![CMake](https://img.shields.io/badge/CMake-3.14+-green)
![GoogleTest](https://img.shields.io/badge/GoogleTest-v1.14-orange)
![Tests](https://img.shields.io/badge/Tests-10%20Passed-brightgreen)
![CI](https://img.shields.io/badge/CI-GitHub%20Actions-blue)

---

## 📋 Description | Mô tả

**🇬🇧 English:**  
A simulation project demonstrating **Unit Testing** skills for Automotive software with safety-critical features. The system simulates automatic transmission control logic (P/R/N/D gears) and throttle/brake behavior with comprehensive safety verification.

**🇻🇳 Tiếng Việt:**  
Dự án mô phỏng thể hiện kỹ năng **Unit Testing** cho phần mềm ô tô với các tính năng an toàn quan trọng. Hệ thống mô phỏng logic điều khiển hộp số tự động (P/R/N/D) và hành vi ga/phanh với kiểm thử an toàn toàn diện.

---

## 🛡️ Safety Features | Tính năng an toàn

| Feature | Description | Mô tả |
|---------|-------------|-------|
| **Prevent Reverse While Driving** | Cannot shift to R when speed > 0 | Không cho về số lùi khi xe đang chạy |
| **Brake Override Throttle** | Brake always takes priority over throttle | Phanh luôn ưu tiên hơn ga |
| **Max Speed Limiter** | Speed cannot exceed 200 km/h | Giới hạn tốc độ tối đa 200 km/h |
| **Park Safety Interlock** | Must stop + press brake to shift to P | Về P cần dừng hẳn + đạp phanh |

---

## 📁 Project Structure | Cấu trúc dự án

```
AutoSpeed-Control/
├── CMakeLists.txt          # Build configuration
├── README.md               # This file
├── .github/workflows/      # CI/CD with GitHub Actions
│   └── ci.yml
├── src/
│   ├── CarController.h     # Class definition with Doxygen
│   └── CarController.cpp   # Implementation with 5 safety rules
└── tests/
    └── test_safety.cpp     # 10 Unit Tests (GTest)
```

---

## 🚀 Build & Run | Cách chạy

```bash
# Clone repository
git clone https://github.com/duytan1412/AutoSpeed-Control.git
cd AutoSpeed-Control

# Build (CMake auto-downloads GoogleTest)
mkdir build && cd build
cmake -G "MinGW Makefiles" ..   # Windows
# cmake ..                      # Linux/Mac
cmake --build .

# Run tests
ctest --output-on-failure
# Or run directly: ./bin/AutoSpeedTests
```

---

## ✅ Test Results | Kết quả kiểm thử

```
[==========] Running 10 tests from 4 test suites.

[----------] 7 tests from SafetyTest
[       OK ] SafetyTest.PreventReverseWhileDriving
[       OK ] SafetyTest.BrakeOverrideThrottle
[       OK ] SafetyTest.AllowReverseWhenStopped
[       OK ] SafetyTest.GearParkRequiresBrake
[       OK ] SafetyTest.EmergencyBrakeAtHighSpeed
[       OK ] SafetyTest.NeutralGearNoAcceleration

[----------] 2 tests from BoundaryTest
[       OK ] BoundaryTest.MaxSpeedLimit
[       OK ] BoundaryTest.ThrottleClampedToValidRange
[       OK ] BoundaryTest.SpeedNeverNegative

[----------] 1 test from StateTest
[       OK ] StateTest.ConsecutiveGearChanges

[==========] 10 tests from 4 test suites ran. (28 ms total)
[  PASSED  ] 10 tests.
```

---

## 🎓 What I Learned | Những gì tôi học được

**🇬🇧 English:**
- **Google Test Framework** - TEST(), ASSERT_*, EXPECT_* macros
- **CMake** - Industry-standard build system with FetchContent
- **Safety-Critical Thinking** - ISO 26262 mindset for Automotive
- **CI/CD** - Automated testing with GitHub Actions

**🇻🇳 Tiếng Việt:**
- **Google Test Framework** - Các macro TEST(), ASSERT_*, EXPECT_*
- **CMake** - Hệ thống build chuẩn ngành với FetchContent
- **Tư duy Safety-Critical** - Tư duy ISO 26262 cho Automotive
- **CI/CD** - Kiểm thử tự động với GitHub Actions

---

## 👨‍💻 Author | Tác giả

**Bì Duy Tân**
- 🎓 FPT Jetking - Chip Design Technology
- 🎯 Target: Embedded Tester @ FPT Software Automotive
- 📧 duytan2903@gmail.com
- 🔗 [LinkedIn](https://www.linkedin.com/in/duy-t%C3%A2n-b-439ba0153/)

---

## 📝 License

MIT License - Free to use for learning purposes.
