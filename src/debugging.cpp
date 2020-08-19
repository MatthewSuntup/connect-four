

#include "debugging.hpp"

// A simple print function with basic game statistics, used for debugging.
void PrintTest(std::string state_str, std::string player, char mode, int depth){
  std::cout << "Test Running with Input:\n"
  << "State: " << state_str << std::endl
  << "Next Player: " << player << std::endl
  << "Mode: " << mode << std::endl
  << "Depth: " << depth << std::endl << std::endl;
}


// A simple print function to visualise the game board, used for debugging.
// Inputs:
//  state   -   the current board state
void PrintMatrix(char state[kRows][kCols]){
  for (int r = kRows-1; r >= 0 ; r--) {
    for (int c = 0; c < kCols; c++) {
      std::cout << state[r][c];
    }
    std::cout << std::endl;
  }
}
