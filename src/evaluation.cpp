// evaluation.cpp
// Functions used to determine the winning player and evaluate how "good" a
// board state is for either player.

#include "debugging.hpp"
#include "evaluation.hpp"

// Evaluation function to quantify the quality of the current state for either
// player. 
// Inputs:
//  state   -   the current board state
int evaluation(char state[kRows][kCols]) {
  return score(state, red) - score(state, yellow);
}


// Utility function to determine if the game has been won. Note that it is
// possible to have more than 4 in a row if two series of tokens in a row (each
// less than 4) are joined with a final token. Returns the utility value
// if the game is won, and 0 otherwise.
// Inputs:
//  state   -   the current board state
int utility(char state[kRows][kCols]) {
  if (num_in_a_row(4, state, red) || num_in_a_row(5, state, red) || 
        num_in_a_row(6,state,red)) {
    return kRWinScore;
  } else if (num_in_a_row(4,state,yellow) || num_in_a_row(5, state, yellow) || 
              num_in_a_row(6,state,yellow)) {
    return kYWinScore;
  } else {
    return 0;
  }
}


// Function to determine the score for each player individually as part of the
// evaluation process. 
// Inputs:
//  state   -   the current board state
//  player  -   the player being evaluated
int score(char state[kRows][kCols], Player player) {

  // Get the total number of tokens of that player's colour
  int token_count = 0;
  char token = (player == red ? 'r' : 'y');
  for (int c = 0; c < kCols; c++) {
    for (int r = 0; r < kRows; r++) {
      if (state[r][c] == token) {
        token_count++;
      } else if (state[r][c] == kEmpty) {
        // Tokens cannot be floating, so we can move to the next column
        continue;
      }
    }
  }

  int score2 = kDoubleVal*num_in_a_row(2, state, player);
  int score3 = kTripleVal*num_in_a_row(3, state, player);

  return token_count + score2 + score3;
}


// Function to determine how many instances of 2-4 tokens in a row exist 
// on the current boar state for a particular colours.
// Inputs:
//  count   -   number of tokens in a row to check for {2,3,4}
//  state   -   the current board state
//  player  -   the player corresponding to the colour being checked
int num_in_a_row(int count, char state[kRows][kCols], Player player) {

  char token = (player==red ? 'r' : 'y');
  int num = 0;
  int tmp_check;

  // Iterate through every column and row
  for (int c = 0; c < kCols; c++) {
    for (int r = 0; r < kRows; r++) {
      if (state[r][c] == token) {
        // Check horizontal line-up by checking for the right-most token in a 
        // line-up
        // Check there are enough tokens to the left, and that it doesn't 
        // extend to the right or further left
        if (c >= count-1 && (c == kCols - 1 || state[r][c + 1]!=token) && 
           (c == count - 1 || state[r][c - (count - 1) - 1] != token)) {
          tmp_check = 1;
          // Check the tokens to the left to see they're all the same
          for (int i = (count - 1); i > 0; i--) {
            if (state[r][c-i] != token) {
              tmp_check = 0;
              break;
            }
          }
          if (tmp_check) {
            num++;
            if (DEBUG) {
              printf("Horizontal line-up found\n");
            }
          }
        }

        // Check vertical line-up by checking for the top-most token in a 
        // line-up
        // Check there are enough tokens below, and that it doesn't extend 
        // above or further below
        if (r >= count - 1 && (r == kRows - 1 || state[r + 1][c] != token) && 
            (r ==count - 1 || state[r-(count - 1) - 1][c] != token)) {
          tmp_check = 1;
          // Check the tokens below to see they're all the same
          for (int i = (count - 1); i > 0; i--) {
            if (state[r - i][c] != token) {
              tmp_check = 0;
              break;
            }
          }
          if (tmp_check) {
            num++;
            if (DEBUG) {
              printf("Vertical line-up found\n");
            }
          }
        }

        // Check bottom-left to top-right diagonal line-up by checking for the 
        // right-top-most token
        // Check enough tokens below and to the left, and doesn't extend beyond 
        // or further back
        if (r >= count - 1 && c >= count - 1 && 
            (r == kRows - 1 || c == kCols - 1 || 
              state[r + 1][c + 1] != token) && (r == count - 1 || 
              c == count - 1 || state[r - (count - 1) - 1][c - (count - 1) - 1] 
              != token)) {
          tmp_check = 1;
          // Check the tokens below and left to see they're all the same
          for (int i = (count - 1); i > 0; i--) {
            if (state[r - i][c - i] != token) {
              tmp_check = 0;
              break;
            }
          }
          if (tmp_check) {
            num++;
            if (DEBUG) {
              printf("Diagonal bottom-left to top-right line-up found\n");
            }
          }
        }

        // Check top-left to bottom-right diagonal line-up by checking for the 
        // bottom-right-most token
        // Check enough tokens above and to the left, and doesn't extend beyond
        // or further back
        if(r < kRows - (count - 1) && c >= count - 1 && 
            (r == 0 || c == kCols - 1 || state[r - 1][c + 1] != token) && 
            (r == kRows - (count - 1) - 1 || c == count - 1 || 
            state[r + (count - 1) + 1][c - (count - 1) - 1] != token)) {
          tmp_check = 1;
          // Check the tokens above and left to see they're all the same
          for (int i = (count - 1); i > 0; i--) {
            if (state[r + i][c - i] != token) {
              tmp_check = 0;
              break;
            }
          }
          if (tmp_check) {
            num++;
            if (DEBUG) {
              printf("Diagonal top-left to bottom-right line-up found\n");
            }
          }
        }
      }
      else if(state[r][c] == kEmpty) {
        // Tokens cannot be floating, so we can move to the next column
        continue;
      }
    }
  }
  return num;
}
