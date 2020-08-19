#!/bin/bash

# This is just an ultra-lightweight means of building and running these files 
# while I'm making modifications to check I didn't completely break it.
# I began experimenting with Google Tests and Visual Studio, but it seemed
# uncessary given I'm cleaning up a small program.

echo "Compiling..."
g++ connect_four.cpp evaluation.cpp debugging.cpp -o connect_four.out

echo "Running..."
./connect_four.out .ryyrry,.rryry.,..y.r..,..y....,.......,....... red A 4
# Should produce: 1, 297

echo "Running..."
./connect_four.out .ryyrry,.rryry.,..y.r..,..y....,.......,....... yellow M 3
# Should produce: 4, 357