# <img src="img/Connect Four Project Logo.png?raw=true" height="70">

This code was originally developed for a University of Sydney assignment in the [Advanced Introduction to Artificial Intelligence course (2020 Semester 1)](https://www.sydney.edu.au/courses/units-of-study/2020/comp/comp3608.html). It has since been updated with clearer organisation and documentation for an unfamiliar reader.

The software generates a decision tree and uses a minimax search algorithm with the option of alpha-beta pruning in order to play a game of [Connect Four](https://en.wikipedia.org/wiki/Connect_Four). The program takes an initial board state and whose turn it is to play and outputs a number corresponding to the column it chooses to play the next token in.

## Input
The program takes 4 inputs as command line arguments.
- The current state of the board as a string of the form: ``` row0,row1,row2,row3,row4,row5 ```

  Each row contains 7 characters, representing the 7 columns in the board. The characters may only be ```r```, ```y```, or ```.``` representing a red token, a yellow token, and a blank space respectively.

- The player who is to play next, either ```red``` or ```yellow```
- The option for the algorithm to use alpha-beta pruning (```A```) or simply the minimax algorithm with no pruning (```M```)
- An integer representing the maximum depth that the algorithm should search in the decision tree

### Example Input
```
.ryyrry,.rryry.,..y.r..,..y....,.......,....... red A 4
```
These input arguments dictate that it is ```red```'s turn to play, ```A```lpha-beta pruning should be used,the decision tree should be explored to a maximum depth of ```4``` levels, and the initial board state may be visualised as follows:

<img src="img/board_example.jpg?raw=true" height="200">

## Output
There are 2 output lines produced by the program:
- An integer value representing the column that the algorithm will play in ```(0-6)```
- The number of nodes that were examined during the search

### Example Output
For the example input above, the output of the algorithm is:
```
1
297
```
Meaning the algorithm has chosen the 2nd column as the best option for red to play after having searched ```297``` nodes.
