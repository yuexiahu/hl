#!/bin/bash

cd $(dirname $0)/..
cmake -S. -Bbuild -DHL_BUILD_TESTS=ON
cmake --build build
./build/tests/tests
