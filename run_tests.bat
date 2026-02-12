@echo off
REM =============================================================================
REM AutoSpeed-Control: Build & Run All Tests (Windows)
REM Usage: run_tests.bat
REM =============================================================================

echo =================================================
echo   AutoSpeed-Control - Build ^& Test Runner
echo =================================================
echo.

REM Step 1: Configure
echo [1/3] Configuring CMake...
cmake -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] CMake configuration failed!
    exit /b 1
)
echo.

REM Step 2: Build
echo [2/3] Building project...
cmake --build build
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] Build failed!
    exit /b 1
)
echo.

REM Step 3: Run Tests
echo [3/3] Running verification tests...
echo -------------------------------------------------
cd build
ctest --output-on-failure
if %ERRORLEVEL% EQU 0 (
    echo.
    echo =================================================
    echo   ALL TESTS PASSED - Safety Logic Verified!
    echo =================================================
) else (
    echo.
    echo =================================================
    echo   SOME TESTS FAILED - Check output above
    echo =================================================
    exit /b 1
)
cd ..
