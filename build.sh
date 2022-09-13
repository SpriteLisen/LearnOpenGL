#!/bin/bash
echo 'Prepare build env...'
mkdir build && cd build
echo 'Build project...'
cmake .. && make -j4 install
echo 'Run APP!'
cd .. && ./build/LearnOpenGL