#!/bin/bash
#=============================================================================
# AutoSpeed-Control: Build & Run All Tests
# Usage: bash run_tests.sh
#=============================================================================

set -e  # Exit on first error

echo "================================================="
echo "  AutoSpeed-Control - Build & Test Runner"
echo "================================================="
echo ""

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Step 1: Configure
echo "[1/3] Configuring CMake..."
cmake -B build -DCMAKE_BUILD_TYPE=Release 2>&1
echo ""

# Step 2: Build
echo "[2/3] Building project..."
cmake --build build 2>&1
echo ""

# Step 3: Run Tests
echo "[3/3] Running verification tests..."
echo "-------------------------------------------------"
cd build
if ctest --output-on-failure; then
    echo ""
    echo -e "${GREEN}=================================================${NC}"
    echo -e "${GREEN}  ✅ ALL TESTS PASSED - Safety Logic Verified!${NC}"
    echo -e "${GREEN}=================================================${NC}"
    exit 0
else
    echo ""
    echo -e "${RED}=================================================${NC}"
    echo -e "${RED}  ❌ SOME TESTS FAILED - Check output above${NC}"
    echo -e "${RED}=================================================${NC}"
    exit 1
fi
