#!/bin/bash

cd $(dirname $0)/..
cmake -S. -Bbuild -DBUILD_TESTING=ON
cmake --build build
./build/tests/tests
