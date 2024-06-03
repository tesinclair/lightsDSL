#!/bin/bash

if [ -d ./bin/ ]; then
    rm -r ./bin
fi

mkdir bin
cd bin
cmake ..
cmake --bin .

