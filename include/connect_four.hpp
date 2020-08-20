#ifndef CONNECT_FOUR_HPP_
#define CONNECT_FOUR_HPP_

// Grid Size
constexpr int kRows = 6;
constexpr int kCols = 7;

// Empty Marker
constexpr char kEmpty = '.';

// Evaluation and Utility Scores
constexpr int kDoubleVal = 10;
constexpr int kTripleVal = 100;
constexpr int kRWinScore = 10000;
constexpr int kYWinScore = -10000;

enum Player {red, yellow};

typedef struct MinimaxRes{
  int column;
  int value;
  int nodes_examined;
}MinimaxRes;

MinimaxRes MinimaxDFS(char state[kRows][kCols], int depth, Player player);
MinimaxRes AlphaBetaDFS(char state[kRows][kCols], int depth, Player player, 
						int alpha, int beta);
 void PrintUsage(void);
 void PrintError(std::string msg);

#endif // CONNECT_FOUR_HPP_