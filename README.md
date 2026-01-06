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
A simulation project demonstrating **Unit Testing** and **Safety-Critical Logic** for Automotive software. The system models an Automatic Transmission Controller and Throttle/Brake system, verified by 10 professional-grade test cases.

**🇻🇳 Tiếng Việt:**  
Dự án mô phỏng thể hiện kỹ năng **Unit Testing** và **Logic An toàn (Safety-Critical)** cho phần mềm ô tô. Hệ thống mô phỏng Bộ điều khiển hộp số tự động và hệ thống Ga/Phanh, được xác thực bởi 10 kịch bản kiểm thử chuẩn công nghiệp.

---

## 🧠 Verification Strategy | Chiến lược kiểm thử

**🇬🇧 English:**
- **Boundary Value Analysis (BVA):** Testing speed limits (0 and 200 km/h) and throttle clamping (0% - 100%).
- **State Transition Testing:** Validating gear shifts (P, R, N, D) under different speed conditions.
- **Safety Interlock Assertion:** Using Google Test macros (`ASSERT_FALSE`, `EXPECT_EQ`) to enforce mechanical safety rules in software.

**🇻🇳 Tiếng Việt:**
- **Phân tích giá trị biên (BVA):** Kiểm tra giới hạn tốc độ (0 và 200 km/h) và kẹp giá trị ga (0% - 100%).
- **Kiểm thử chuyển trạng thái:** Xác thực việc chuyển số (P, R, N, D) trong các điều kiện tốc độ khác nhau.
- **Xác thực khóa liên động an toàn:** Sử dụng các macro Google Test để thực thi các quy tắc an toàn cơ khí ngay trên phần mềm.

---

## 🛡️ Safety Rules Implementation | Cài đặt quy tắc an toàn

| Rule | Description | Logic Implementation |
|------|-------------|----------------------|
| **Reverse Lock** | Prevent R gear when speed > 0 | `if (newGear == 'R' && speed_ > 0) return false;` |
| **Park Interlock** | Park requires Stop & Brake | `if (newGear == 'P' && (speed_ > 0 || !brake_)) return false;` |
| **BOS (Brake Override)** | Brake > Throttle priority | `if (brake_) speed_ -= DECELERATION; else calculate_accel();` |
| **Neutral Safety** | No acceleration in N | `if (gear_ == 'N') throttle_ignored;` |

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
└── CMakeLists.txt          # Modern CMake with FetchContent (GTest)
```

---

## 🚀 Build & Run | Cách chạy

```bash
# Windows (MinGW)
mkdir build && cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
ctest --output-on-failure
```

---

## 👨‍💻 Author | Tác giả

**Bì Duy Tân**
- 🎓 FPT Jetking (Chip Design Technology)
- 🎯 Embedded Software Tester Career Path
- 📧 duytan2903@gmail.com
- 🔗 [LinkedIn](https://www.linkedin.com/in/duy-t%C3%A2n-b-439ba0153/)
