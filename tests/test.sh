#!/bin/bash

cd $(dirname $0)/..
cmake -S. -Bbuild -DBUILD_TESTING=ON
cmake --build build
cd build
env CTEST_OUTPUT_ON_FAILURE=1 ctest
