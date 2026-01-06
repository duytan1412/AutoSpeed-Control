cmake_minimum_required(VERSION 3.14)
project(AutoSpeed-Control VERSION 1.0.0 LANGUAGES CXX)

# C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ============================================================================
# Main Library
# ============================================================================
add_library(CarControllerLib
    src/CarController.cpp
)

target_include_directories(CarControllerLib PUBLIC
    ${CMAKE_SOURCE_DIR}/src
)

# ============================================================================
# Google Test Configuration
# ============================================================================
include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

# ============================================================================
# Tests
# ============================================================================
enable_testing()

add_executable(AutoSpeedTests
    tests/test_safety.cpp
)

target_link_libraries(AutoSpeedTests
    CarControllerLib
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(AutoSpeedTests)

# ============================================================================
# Summary
# ============================================================================
message(STATUS "")
message(STATUS "=================================================")
message(STATUS "  AutoSpeed-Control Configuration")
message(STATUS "=================================================")
message(STATUS "  C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Build Type:   ${CMAKE_BUILD_TYPE}")
message(STATUS "  Output Dir:   ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "=================================================")
message(STATUS "")
