#ifndef EVALUATION_HPP_
#define EVALUATION_HPP_

#include "connect_four.hpp"

int evaluation(char state[kRows][kCols]);
int utility(char state[kRows][kCols]);
int score(char state[kRows][kCols], Player player);
int num_in_a_row(int count, char state[kRows][kCols], Player player);

#endif // EVALUATION_HPP_