
#define ROWS 6
#define COLS 7
#define EMPTY '.'
#define DOUBLE_VAL 10
#define TRIPLE_VAL 100
#define QAUDRUPLE_VAL 1000

#define r_win 10000
#define y_win -10000

#include <iostream>
#include <limits>
#include <string>



enum Player {red, yellow};

typedef struct MinimaxRes{
	int column;
	int value;
	int nodes_examined;
}MinimaxRes;


int nodes_global=0;


void print_test(std::string state_str, std::string player, char mode, int depth){
	std::cout << "Test Running with Input:\n"
	<< "State: " << state_str << std::endl
	<< "Next Player: " << player << std::endl
	<< "Mode: " << mode << std::endl
	<< "Depth: " << depth << std::endl << std::endl;
}


void print_matrix(char state[ROWS][COLS]){
	// Test print
	// std::cout << "State Matrix:" << std::endl;
	for(int r = ROWS-1; r >= 0 ; r--){
		for(int c = 0; c < COLS; c++){
			std::cout << state[r][c];
		}
		std::cout << std::endl;
	}
}



/*
	count is a num between 2 and 4 (inclusive)
*/
int num_in_a_row(int count, char state[ROWS][COLS], Player player){

	char token = (player==red ? 'r' : 'y');
	int num = 0;
	int tmp_check;

	// Iterate through every column and row
	for(int c = 0; c < COLS; c++){
		for(int r = 0; r < ROWS; r++){
			if(state[r][c]==token){
				// Check horizontal line-up by checking for the right-most token in a line-up
				// Check there are enough tokens to the left, and that it doesn't extend to the right or further left
				if(c >= count-1 && (c==COLS-1 || state[r][c+1]!=token) && (c==count-1 || state[r][c-(count-1)-1]!=token)){
					tmp_check = 1;
					// Check the tokens to the left to see they're all the same
					for(int i = (count-1); i>0; i--){
						if(state[r][c-i]!=token){
							tmp_check = 0;
							break;
						}
					}
					if(tmp_check){
						num++;
						// printf("Horizontal line-up found\n");
					}
				}

				// Check vertical line-up by checking for the top-most token in a line-up
				// Check there are enough tokens below, and that it doesn't extend above or further below
				if(r >= count-1 && (r==ROWS-1 || state[r+1][c] != token) && (r==count-1 || state[r-(count-1)-1][c]!=token)){
					tmp_check = 1;
					// Check the tokens below to see they're all the same
					for(int i = (count-1); i>0; i--){
						if(state[r-i][c]!=token){
							tmp_check = 0;
							break;
						}
					}
					if(tmp_check){
						num++;
						// printf("Vertical line-up found\n");
					}
				}

				// Check bottom-left to top-right diagonal line-up by checking for the right-top-most token
				// Check enough tokens below and to the left, and doesn't extend beyond or further back
				if(r >= count-1 && c >= count-1 && (r==ROWS-1 || c==COLS-1 || state[r+1][c+1] != token) && (r==count-1 || c==count-1 || state[r-(count-1)-1][c-(count-1)-1]!=token)){
					tmp_check = 1;
					// Check the tokens below and left to see they're all the same
					for(int i = (count-1); i>0; i--){
						if(state[r-i][c-i]!=token){
							tmp_check = 0;
							break;
						}
					}
					if(tmp_check){
						num++;
						// printf("Diagonal bottom-left to top-right line-up found\n");
					}
				}

				// Check top-left to bottom-right diagonal line-up by checking for the bottom-right-most token
				// Check enough tokens above and to the left, and doesn't extend beyond or further back
				if(r < ROWS-(count-1) && c >= count-1 && (r==0 || c==COLS-1 || state[r-1][c+1] != token) && (r==ROWS-(count-1)-1 || c==count-1 || state[r+(count-1)+1][c-(count-1)-1]!=token)){
					tmp_check = 1;
					// Check the tokens above and left to see they're all the same
					for(int i = (count-1); i>0; i--){
						if(state[r+i][c-i]!=token){
							tmp_check = 0;
							break;
						}
					}
					if(tmp_check){
						num++;
						// printf("Diagonal top-left to bottom-right line-up found\n");
					}
				}
			}
			else if(state[r][c]==EMPTY){
				// Tokens cannot be floating, so we can move to the next column
				continue;
			}
		}
	}
	return num;
}


int score(char state[ROWS][COLS], Player player){

	// Get the total number of tokens of that player's colour
	int token_count = 0;
	char token = (player==red ? 'r' : 'y');
	for(int c = 0; c < COLS; c++){
		for(int r = 0; r < ROWS; r++){
			if(state[r][c]==token){
				token_count++;
			}
			else if(state[r][c]==EMPTY){
				// Tokens cannot be floating, so we can move to the next column
				continue;
			}
		}
	}

	int score2 = DOUBLE_VAL*num_in_a_row(2, state, player);
	int score3 = TRIPLE_VAL*num_in_a_row(3, state, player);

	// TODO: Remove testing for 4 in a row as this is a win anyway
	//int score4 = QAUDRUPLE_VAL*num_in_a_row(4, state, player);

	return token_count + score2 + score3; //+ score4;
}


int evaluation(char state[ROWS][COLS]){
	return score(state, red) - score(state, yellow);
}

// A winning state might be 5 in a row or more!!! (because you could have rr.rr and then drop in the middle r)
int utility(char state[ROWS][COLS]){
	if(num_in_a_row(4, state, red) || num_in_a_row(5, state, red) || num_in_a_row(6,state,red)){
		return r_win;
	}
	else if(num_in_a_row(4,state,yellow) || num_in_a_row(5, state, yellow) || num_in_a_row(6,state,yellow)){
		return y_win;
	}
	else{
		return 0;
	}
}


MinimaxRes minimax_DFS(char state[ROWS][COLS], int depth, Player player){
	
	std::cout << "Depth: " << depth << " | Player: " << (player==red ? "red" : "yellow") << std::endl;
	print_matrix(state);
	std::cout << std::endl;

	MinimaxRes result;
	result.nodes_examined = 1;

	// Check if the game is over
	int util = utility(state);
	if(util){
		result.column = -1;
		result.value = util;
		return result;
	}

	// If we aren't going any deeper, evaluate this position
	if(depth==0){
		result.column = -1;
		result.value = evaluation(state);
		return result;
	}
	else{
		int max_col;
		int max_val = std::numeric_limits<int>::min();
		int min_col;
		int min_val = std::numeric_limits<int>::max();

		// Generate all possible boards
		for(int c=0; c<COLS; c++){
			// Find the first free row to drop a token on
			for(int r=0; r<ROWS; r++){
				if(state[r][c]==EMPTY){
					// Drop a token in this column
					state[r][c] = (player==red ? 'r' : 'y');

					// Find the new state's minimax value (reduce depth by one and switch players for next turn)
					MinimaxRes child_minimax = minimax_DFS(state, depth-1, (player==red ? yellow : red));

					// Update vals (use < not <= so the first one is chosen in a tie)
					if(max_val < child_minimax.value){
						max_val = child_minimax.value;
						max_col = c;
					} 
					if(min_val > child_minimax.value){
						min_val = child_minimax.value;
						min_col = c;
					}

					result.nodes_examined += child_minimax.nodes_examined;

					// Taken out the token before moving to next column
					state[r][c] = EMPTY;
					break;
				}
			}
		}

		// Red picks max, yellow picks min
		if(player == red){
			result.column = max_col;
			result.value = max_val;
		}
		else{
			result.column = min_col;
			result.value = min_val;
		}

		return result;

	}

}

// parent is the parent's alpha/beta value
MinimaxRes alphabeta_DFS(char state[ROWS][COLS], int depth, Player player, int parent){
	
	printf("-------------------------\n");
	std::cout << "Depth: " << depth << " | Next player: " << (player==red ? "red" : "yellow") << " | Parent: " << parent << std::endl;
	print_matrix(state);
	std::cout << std::endl;

	MinimaxRes result;
	result.nodes_examined = 1;
	nodes_global++;

	// Check if the game is over
	int util = utility(state);
	if(util){
		result.column = -1;
		result.value = util;
		printf("Terminal State: %d\n", result.value);
		return result;
	}

	// If we aren't going any deeper, evaluate this position
	if(depth==0){
		result.column = -1;
		result.value = evaluation(state);
		printf("Terminal State: %d\n", result.value);
		return result;
	}
	else{
		int max_col;
		int max_val = std::numeric_limits<int>::min();
		int min_col;
		int min_val = std::numeric_limits<int>::max();

		// Generate all possible boards
		for(int c=0; c<COLS; c++){
			// Find the first free row to drop a token on
			for(int r=0; r<ROWS; r++){
				if(state[r][c]==EMPTY){
					// Drop a token in this column
					state[r][c] = (player==red ? 'r' : 'y');

					// Find the new state's minimax value (reduce depth by one and switch players for next turn)
					MinimaxRes child_minimax;
					if(player == red){
						child_minimax = alphabeta_DFS(state, depth-1, yellow, max_val);
						// printf("Child minimax val: %d\n", child_minimax.value);
						// <= instead of < ensures leftmost is chosen
						if(parent <= child_minimax.value || child_minimax.value == r_win){
							// Prune remaining nodes (i.e. don't visit more columns)
							printf("PRUNE below depth %d\n", depth);
							result.value = child_minimax.value;
							result.column = c;
							result.nodes_examined += child_minimax.nodes_examined;
							state[r][c] = EMPTY;	// take out added token
							return result;
						}
					}
						// TODO: could also prune when you see a win
					else{
						child_minimax = alphabeta_DFS(state, depth-1, red, min_val);
						// printf("Child minimax val: %d\n", child_minimax.value);
						// >= instead of > ensures leftmost is chosen
						if(parent >= child_minimax.value || child_minimax.value == y_win){
							// Prune remaining nodes (i.e. don't visit more columns)
							printf("PRUNE below depth %d\n", depth);
							result.value = child_minimax.value;
							result.column = c;
							result.nodes_examined += child_minimax.nodes_examined;
							state[r][c] = EMPTY;	// take out added token
							return result;
						}
					}

					// Update vals (use < not <= so the first one is chosen in a tie)
					if(max_val < child_minimax.value){
						max_val = child_minimax.value;
						max_col = c;
					} 
					if(min_val > child_minimax.value){
						min_val = child_minimax.value;
						min_col = c;
					}

					result.nodes_examined += child_minimax.nodes_examined;

					// Taken out the token before moving to next column
					state[r][c] = EMPTY;
					break;
				}
			}
		}

		// Red picks max, yellow picks min
		if(player == red){
			result.column = max_col;
			result.value = max_val;
		}
		else{
			result.column = min_col;
			result.value = min_val;
		}

		printf("%s chose value: %d\n",(player==red?"red":"yellow"), result.value);
		return result;

	}

}


int main(int argc, char **argv){

	std::string state_str = argv[1];
	std::string player_str = argv[2];
	char mode = *argv[3];
	int depth = std::stoi(argv[4]);

	print_test(state_str, player_str, mode, depth);

	// Parse Player
	Player player;
	if(player_str[0] = 'r'){
		player = red;
	}
	else if(player_str[0] = 'y'){
		player = yellow;
	}

	// Test print
	std::cout << "Player: " << (player==red ? "red" : "yellow") << std::endl;

	// Parse State
	char state[ROWS][COLS];

	// Split the state string into a matrix, skipping over the commas
	for(int i = 0; i < ROWS*(COLS+1); i++){
		if(i%(COLS+1)!=COLS){
			state[int(i/(COLS+1))][i%(COLS+1)] = state_str[i];
		}
	}

	print_matrix(state);

	std::cout << "Red Score: " << score(state, red) << std::endl;
	std::cout << "Yellow Score: " << score(state, yellow) << std::endl;
	std::cout << "Evaluation: " << evaluation(state) << std::endl;

	// Generate the game tree using a Depth-Limited Search
	for(int i=0; i<COLS; i++){
		
	}

	// MinimaxRes result = minimax_DFS(state, depth, player);

	int parent = (player==red ? std::numeric_limits<int>::max() : std::numeric_limits<int>::min());
	MinimaxRes result = alphabeta_DFS(state, depth, player, parent);

	std::cout << result.column << std::endl;
	std::cout << result.nodes_examined << std::endl;
	std::cout << nodes_global << std::endl;

}
