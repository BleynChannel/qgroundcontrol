#!/bin/bash

# Parse arguments

# Main arguments
# init (WIP) - configurate the project
# run - run the project
# deploy - deploy the project

# Optional arguments
# -c - clean the project
# -d - run the project in debug mode
# -r - run the project in release mode

# Initialize variables
action=""
clean=false
release=false

# Parse all arguments
for arg in "$@"; do
    case $arg in
        init|run|deploy)
            if [ -n "$action" ]; then
                echo "Error: Multiple actions specified"
                echo "Usage: $0 [-c] [-d|-r] {init|run|deploy}"
                exit 1
            fi
            action=$arg
            ;;
        -c|--clean)
            clean=true
            ;;
        -d|--debug)
            release=false
            ;;
        -r|--release)
            release=true
            ;;
        *)
            echo "Error: Invalid argument '$arg'"
            echo "Usage: $0 [-c] [-d|-r] {init|run|deploy}"
            exit 1
            ;;
    esac
done

# Validate required argument
if [ -z "$action" ]; then
    echo "Error: No action specified"
    echo "Usage: $0 [-c] [-d|-r] {init|run|deploy}"
    exit 1
fi

# Main logic

build_type="Debug"
if [ "$release" = true ]; then
    build_type="Release"
fi

if [ "$clean" = true ]; then
    echo "Cleaning QGroundControl..."
    rm -rf build/$build_type/*
fi

# Build QGroundControl
if [ "$action" = "init" ]; then
    # Configuration for CMake
    # Note: Currently it's not possible to configure the project via CLI using CMake for Linux.
    # The problem is in specifying the exact path to QT_PATH for CMake. 
    # Therefore, Qt Creator is used for Linux.

    # If you know how to set the working path for CMake, you can uncomment the following code
    # if ! cmake -B build/$build_type -G Ninja -DCMAKE_BUILD_TYPE=$build_type; then
    #     echo "Error: CMake failed to configure the build."
    #     exit 1
    # fi

    exit 0
fi

# Build project if action is init or run
if [ "$action" = "init" ] || [ "$action" = "run" ]; then
    if ! cmake --build build/$build_type --config $build_type; then
        echo "Error: CMake failed to build QGroundControl."
        exit 1
    fi
fi

if [ "$action" = "run" ]; then
    # Run QGroundControl
    echo "Running QGroundControl..."
    # export QT_QPA_PLATFORM=xcb
    # exec "./build/${build_type}/QGroundControl"
fi

if [ "$action" = "deploy" ]; then
    # Deploy QGroundControl
    # mkdir -p ./build/Release
    exec "./deploy/docker/run-docker-ubuntu.sh"
fi
