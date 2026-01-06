# AutoSpeed-Control

🚗 **C++ Automotive Speed Control Simulation with Unit Testing**

![C++](https://img.shields.io/badge/C%2B%2B-17-blue)
![CMake](https://img.shields.io/badge/CMake-3.14+-green)
![GoogleTest](https://img.shields.io/badge/GoogleTest-v1.14-orange)
![Tests](https://img.shields.io/badge/Tests-10%20Passed-brightgreen)

## 📋 Mô tả

Project demo kỹ năng **Unit Testing** cho phần mềm Automotive với các tính năng:
- Mô phỏng logic điều khiển tốc độ xe
- Kiểm tra an toàn (Safety-Critical Testing)
- Tích hợp Google Test framework

## 🛡️ Safety Features

| Feature | Mô tả |
|---------|-------|
| Prevent Reverse While Driving | Không cho về số lùi khi xe đang chạy |
| Brake Override Throttle | Phanh luôn ưu tiên hơn ga |
| Max Speed Limiter | Giới hạn tốc độ tối đa 200 km/h |
| Park Safety Interlock | Về P cần dừng hẳn + đạp phanh |

## 📁 Cấu trúc Project

```
AutoSpeed-Control/
├── CMakeLists.txt          # Build configuration
├── README.md
├── src/
│   ├── CarController.h     # Class definition
│   └── CarController.cpp   # Implementation
└── tests/
    └── test_safety.cpp     # 7 Unit tests
```

## 🚀 Build & Run

```bash
# Clone repository
git clone https://github.com/YOUR_USERNAME/AutoSpeed-Control.git
cd AutoSpeed-Control

# Build
mkdir build && cd build
cmake ..
cmake --build .

# Run tests
ctest --output-on-failure
```

## ✅ Test Results

```
[==========] Running 7 tests from 3 test suites.
[----------] 5 tests from SafetyTest
[ RUN      ] SafetyTest.PreventReverseWhileDriving
[       OK ] SafetyTest.PreventReverseWhileDriving
[ RUN      ] SafetyTest.BrakeOverrideThrottle
[       OK ] SafetyTest.BrakeOverrideThrottle
[ RUN      ] SafetyTest.AllowReverseWhenStopped
[       OK ] SafetyTest.AllowReverseWhenStopped
[ RUN      ] SafetyTest.GearParkRequiresBrake
[       OK ] SafetyTest.GearParkRequiresBrake
[----------] 2 tests from BoundaryTest
[ RUN      ] BoundaryTest.MaxSpeedLimit
[       OK ] BoundaryTest.MaxSpeedLimit
[ RUN      ] BoundaryTest.ThrottleClampedToValidRange
[       OK ] BoundaryTest.ThrottleClampedToValidRange
[ RUN      ] BoundaryTest.SpeedNeverNegative
[       OK ] BoundaryTest.SpeedNeverNegative
[==========] 7 tests from 3 test suites ran.
[  PASSED  ] 7 tests.
```

## 🎓 Học hỏi từ Project này

1. **Google Test Framework** - Cú pháp TEST(), ASSERT_*, EXPECT_*
2. **CMake** - Build system chuẩn ngành
3. **Safety-Critical Thinking** - Tư duy kiểm thử an toàn cho Automotive

## 👨‍💻 Tác giả

**Bì Duy Tân**
- Sinh viên FPT Jetking - Chip Design
- Target: Embedded Tester @ FPT Software Automotive

## 📝 License

MIT License
