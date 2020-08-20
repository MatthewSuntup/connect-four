#!/bin/bash

# This is just an ultra-lightweight means of running these files using Git Bash
# while I'm making modifications to check I didn't completely break it.
# I began experimenting with Google Tests and Visual Studio, but it seemed
# uncessary given I'm cleaning up a small program.

echo "Running Instance #1 ..."
./connect_four.exe .ryyrry,.rryry.,..y.r..,..y....,.......,....... red A 4
# Should produce: 1, 297

echo "Running Instance #2 ..."
./connect_four.exe .ryyrry,.rryry.,..y.r..,..y....,.......,....... yellow M 3
# Should produce: 4, 357