// COMP3608: Introduction to AI (Adv.) - USYD
// Assignment 1
// ConectFour.cpp
// Author: Matthew Suntup
// Submission Date: 10 April 2020
// Last Edit: 20 August 2020


#include <iostream>
#include <limits>
#include <string>

#include "connect_four.hpp"
#include "debugging.hpp"
#include "evaluation.hpp"


// This function is to be called iteratively in order to traverse down the
// decision tree. It returns a MnimiaxRes object, which contains the
// column chosen by the player at the current depth, as well as the value
// associated with that choice and the number of nodes examined.
// Inputs:
//  state   -   the current board state
//  depth   -   the number of levels remaining before suspending the search
//  player  -   the player who's turn it is to go
MinimaxRes MinimaxDFS(char state[kRows][kCols], int depth, Player player){
  
  if (DEBUG) {
    std::cout << "Depth: " << depth << " | Player: " << (player==red ? "red" : "yellow") << std::endl;
    PrintMatrix(state);
    std::cout << std::endl; 
  }

  MinimaxRes result;
  result.nodes_examined = 1;

  // Check if the game is over
  int util = utility(state);
  if (util) {
    result.column = -1;
    result.value = util;
    return result;
  }

  // Check if the maximum depth has been reached
  if (depth == 0) {
    // Evaluate the current position
    result.column = -1;
    result.value = evaluation(state);
    return result;
  } else {
    int max_col;
    int max_val = std::numeric_limits<int>::min();
    int min_col;
    int min_val = std::numeric_limits<int>::max();

    // Generate all possible boards
    for (int c = 0; c < kCols; c++) {
      // Find the first free row to drop a token in
      for (int r = 0; r < kRows; r++) {
        if (state[r][c] == kEmpty) {
          // Drop a token in this column
          state[r][c] = (player == red ? 'r' : 'y');

          // Find the new state's minimax value (reduce depth by one 
          // and switch players for next turn)
          MinimaxRes child_minimax = MinimaxDFS(state, depth - 1, (player == red ? yellow : red));

          // Update vals (use < not <= so the first one is chosen in 
          // a tie)
          if (max_val < child_minimax.value) {
            max_val = child_minimax.value;
            max_col = c;
          } 
          if (min_val > child_minimax.value) {
            min_val = child_minimax.value;
            min_col = c;
          }

          result.nodes_examined += child_minimax.nodes_examined;

          // Take out the token before moving to next column
          state[r][c] = kEmpty;
          break;
        }
      }
    }

    // Red picks max, yellow picks min
    if (player == red) {
      result.column = max_col;
      result.value = max_val;
    } else {
      result.column = min_col;
      result.value = min_val;
    }

    return result;

  }

}


// This function is to be called iteratively in order to traverse down the
// decision tree. It returns a MnimiaxRes object, which contains the
// column chosen by the player at the current depth, as well as the value
// associated with that choice and the number of nodes examined.
// Inputs:
//  state   -   the current board state
//  depth   -   the number of levels remaining before suspending the search
//  player  -   the player who's turn it is to go
//  alpha   -   the current alpha value to beat (to decide on pruning)
//  beta    -   the current beta value to beat (to decide on pruning)
MinimaxRes AlphaBetaDFS(char state[kRows][kCols], int depth, Player player, int alpha, int beta){
  if (DEBUG) {
    printf("------------------------------------------\n");
    std::cout << "+Depth: " << 4 - depth << " | Prev player: " << (player==yellow ? "red" : "yellow") << " | Alpha: " << alpha << " | Beta: " << beta << std::endl;
    PrintMatrix(state);
    std::cout << std::endl;
  }

  MinimaxRes result;
  result.nodes_examined = 1;

  // Check if the game is over
  int util = utility(state);
  if (util) {
    result.column = -1;
    result.value = util;
    if (DEBUG) {
      printf("Terminal State: %d\n", result.value);
    }
    return result;
  }

  // If we aren't going any deeper, evaluate this position
  if (depth == 0) {
    result.column = -1;
    result.value = evaluation(state);
    if(DEBUG){
      printf("Terminal State: %d\n", result.value);
    }
    return result;
  } else {
    int max_col;
    int max_val = std::numeric_limits<int>::min();
    int min_col;
    int min_val = std::numeric_limits<int>::max();

    // Generate all possible boards
    for (int c = 0; c < kCols; c++) {
      // Find the first free row to drop a token on
      for (int r = 0; r < kRows; r++) {
        if (state[r][c] == kEmpty) {
          // Drop a token in this column
          state[r][c] = (player == red ? 'r' : 'y');

          // Find the new state's minimax value 
          // (reduce depth by one and switch players for next turn)
          MinimaxRes child_minimax;
          if (player == red) {
            child_minimax = AlphaBetaDFS(state, depth - 1, yellow, alpha, beta);

            // Add to node count
            result.nodes_examined += child_minimax.nodes_examined;

            // Taken out the token for the next test
            state[r][c] = kEmpty;
            if (DEBUG) {
              printf("Child minimax val: %d\n", child_minimax.value);
            }
            // <= instead of < ensures leftmost is chosen
            if (child_minimax.value > max_val) {
              max_val = child_minimax.value;
              max_col = c;
              if (max_val > alpha) {
                alpha = max_val;
              }
            }

            if (alpha >= beta) {
              if (DEBUG) {
                printf("PRUNE (alpha>=beta) below depth %d\n", depth);
              }
              result.value = child_minimax.value;
              result.column = c;
              state[r][c] = kEmpty;    // take out added token
              return result;
            }
          } else {
            child_minimax = AlphaBetaDFS(state, depth-1, red, alpha, beta);

            // Add to node count
            result.nodes_examined += child_minimax.nodes_examined;

            // Taken out the token for the next test
            state[r][c] = kEmpty;

            if (DEBUG) {
              printf("Child minimax val: %d\n", child_minimax.value);
            }

            // >= instead of > ensures leftmost is chosen
            if (child_minimax.value < min_val) {
              min_val = child_minimax.value;
              min_col = c;
              if (min_val < beta) {
                beta = min_val;
              }
            }

            if (beta <= alpha) {
              if (DEBUG) {
                printf("PRUNE (beta<=alpha) below depth %d\n", depth);
              }
              result.value = child_minimax.value;
              result.column = c;

              // Taken out the token
              state[r][c] = kEmpty;
              return result;
            }
          }
          // Move to next column 
          // (break out of search for free row within current column)
          break;
        }
      }
    }

    // Red picks max, yellow picks min
    if (player == red) {
      result.column = max_col;
      result.value = max_val;
    } else {
      result.column = min_col;
      result.value = min_val;
    }
    if (DEBUG) {
      printf("%s chose value: %d\n",(player==red?"red":"yellow"), result.value);
    }
    return result;
  }
}


int main(int argc, char **argv){

  std::string state_str = argv[1];
  std::string player_str = argv[2];
  char mode = *argv[3];
  int depth = std::stoi(argv[4]);

  if (DEBUG) {
    PrintTest(state_str, player_str, mode, depth);
  }

  // Parse Player
  Player player;
  if (player_str[0] == 'r') {
    player = red;
  } else if (player_str[0] == 'y') {
    player = yellow;
  }

  if (DEBUG) {
    std::cout << "Player: " << (player == red ? "red" : "yellow") << std::endl;
  }

  // Parse State
  char state[kRows][kCols];

  // Split the state string into a matrix, skipping over the commas
  for (int i = 0; i < kRows*(kCols + 1); i++) {
    if (i%(kCols+1) != kCols) {
      state[int(i/(kCols + 1))][i%(kCols + 1)] = state_str[i];
    }
  }

  if (DEBUG) {
    PrintMatrix(state);
    std::cout << "Red Score: " << score(state, red) << std::endl;
    std::cout << "Yellow Score: " << score(state, yellow) << std::endl;
    std::cout << "Evaluation: " << evaluation(state) << std::endl;
  }

  MinimaxRes result;

  if (mode=='M') {
    // Minimax algorithm mode (no alpha-beta pruning)
    result = MinimaxDFS(state, depth, player);
  }  else {
    // Minimax algorithm with alpha-beta pruning
    int alpha = std::numeric_limits<int>::min();
    int beta = std::numeric_limits<int>::max();
    result = AlphaBetaDFS(state, depth, player, alpha, beta);
  }

  // Output results
  std::cout << result.column << std::endl;
  std::cout << result.nodes_examined << std::endl;
}
