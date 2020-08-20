#ifndef DEBUGGING_HPP_
#define DEBUGGING_HPP_

#define DEBUG 0

#include <iostream>
#include <string>

#include "connect_four.hpp"

void PrintTest(std::string state_str, std::string player, char mode, int depth);
void PrintMatrix(char state[kRows][kCols]);

#endif // DEBUGGING_HPP_