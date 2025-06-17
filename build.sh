#!/bin/bash

# Build QGroundControl
if ! cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug; then
    echo "Error: CMake failed to configure the build."
    exit 1
fi

if ! cmake --build ~/qgroundcontrol/build --config Debug; then
    echo "Error: CMake failed to build QGroundControl."
    exit 1
fi

