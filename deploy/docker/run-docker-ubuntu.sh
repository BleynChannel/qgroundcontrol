#!/usr/bin/env bash

# Run this from root directory

set -e

BUILD_TYPE=$1

docker build --file ./deploy/docker/Dockerfile-build-ubuntu -t qgc-ubuntu-docker .
docker run --cap-add SYS_ADMIN --device /dev/fuse --security-opt apparmor:unconfined --rm -e BUILD_TYPE=${BUILD_TYPE} -v ${PWD}:/project/source -v ${PWD}/build:/project/build qgc-ubuntu-docker
