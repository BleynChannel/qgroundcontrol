#!/bin/bash

# Build QGroundControl
# if ! cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug; then
#     echo "Error: CMake failed to configure the build."
#     exit 1
# fi

if ! cmake --build /home/bleyn/Projects/Projects/umrc/ui/qgroundcontrol/build/Desktop_Qt_6_6_3_GCC_64bit-Debug --config Debug; then
    echo "Error: CMake failed to build QGroundControl."
    exit 1
fi

# Run QGroundControl
echo "Running QGroundControl..."
./build/Desktop_Qt_6_6_3_GCC_64bit-Debug/QGroundControl
