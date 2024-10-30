#!/bin/bash

# bash script to run the program

# compile the program
cd build 

cmake ..

cd ..

make -C build -j32 && ./build/bin/cpp
