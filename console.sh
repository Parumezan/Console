#!/bin/sh

if [ ! -d "build" ]; then
    mkdir build
fi
if [ "$#" -eq 1 ] && [ "$1" = "debug" ]; then
    echo "-- DEBUG MODE"
    cmake -G Ninja -S . -B build -DCMAKE_BUILD_TYPE=debug
else
    cmake -G Ninja -S . -B build -DCMAKE_BUILD_TYPE=release
fi

ninja -C build