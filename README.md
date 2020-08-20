# <img src="img/Connect Four Project Logo.png?raw=true" height="70">

## About
This program uses artificial intelligence to choose the next move in a game of [Connect Four](https://en.wikipedia.org/wiki/Connect_Four). The software generates a decision tree and uses a minimax search algorithm with the option of alpha-beta pruning to make an informed decision. The program takes an initial board state and whose turn it is to play and outputs a number corresponding to the column it chooses to play the next token in.

This code was originally developed for a University of Sydney assignment in the [Advanced Introduction to Artificial Intelligence course (2020 Semester 1)](https://www.sydney.edu.au/courses/units-of-study/2020/comp/comp3608.html). The input/output specifications and evaluation functions are reflective of the assignment task. The project has since been updated with clearer organisation and documentation for an unfamiliar reader.

## Installation
1. Clone this repository to your local machine using one of the following:
```
git clone git@github.com:MatthewSuntup/connectFour.git
git clone https://github.com/MatthewSuntup/connectFour.git
```
2. Navigate to the root folder:
```
cd connectFour
```
3. Compile the project using the Makefile (command may vary depending on your setup):
```
make
```
4. Run the executable with appropriate input arguments (see [Input](#Input) section).


## Usage
### Input
The program takes 4 inputs as command line arguments.
- The current state of the board as a string of the form: ``` row0,row1,row2,row3,row4,row5 ```

  Each row contains 7 characters, representing the 7 columns in the board. The characters may only be ```r```, ```y```, or ```.``` representing a red token, a yellow token, and a blank space respectively.

- The player who is to play next, either ```red``` or ```yellow```
- The option for the algorithm to use alpha-beta pruning (```A```) or simply the minimax algorithm with no pruning (```M```)
- An integer representing the maximum depth that the algorithm should search in the decision tree

The input undergoes basic checks to ensure it is valid according to these rules, and will provide the user with simple usage instructions if this check fails.

#### Example Input
```
./connect_four .ryyrry,.rryry.,..y.r..,..y....,.......,....... red A 4
```

(Note the usage of ```./connect_four``` is appropriate for Linux systems and should be replaced by ```connect_four.exe``` on Windows.)


These input arguments dictate that it is ```red```'s turn to play, ```A```lpha-beta pruning should be used, the decision tree should be explored to a maximum depth of ```4``` levels, and the initial board state may be visualised as follows:

<img src="img/board_example.jpg?raw=true" height="200">

### Output
There are 2 output lines produced by the program:
- An integer value representing the column that the algorithm will play in ```(0-6)```
- The number of nodes that were examined during the search

#### Example Output
For the example input above, the output of the algorithm is:
```
1
297
```
Meaning the algorithm has chosen the 2nd column as the best option for red to play after having searched ```297``` nodes.

## Lessons

I wrote this program as part of an artificial intelligence course, and my biggest takeaway was definitely a better understanding of minimax and alpha-beta pruning algorithms.

When I came back to the code to clean it up I took the opportunity to use some tools that I didn't have a lot of experience in. I now feel much more comfortable with makefiles. Previously I often relied on auto-generated makefiles or using a template, however, this time I built up each feature of the makefile one at a time by learning the individual symbols and syntax. I also went through the Google C++ style guide for inspiration on how to best format the code for readability and became familiar with standards that I now plan to use in future C++ code. I also got some experience with Adobe Illustrator to make the logo at the top of this README!

## Future Work
If I was to spend more time on this project in the future, I would be interested in working on the following areas:

#### Interface
To make a playable game from this code, some form of GUI could be implemented. This would allow a user to play a full game against the bot, rather than inputting the game state as a string. I would implement this as a web app so it's not necessary for players to install anything, and would allow me to gain some web development experience. (Or I would use a microcontroller, LED matrix, and some buttons!)

#### Efficiency
Various improvements to run-time could be made through modifications such as storing the game state using bit strings and traversing the game tree using iterative methods instead of recursion.

#### Algorithms
There's a lot of scope for improvement if we disregard limitations set by the original assignment and simply seek a program designed to play Connect Four, here are just a few ideas:

 - The option of choosing the search depth could be removed and instead allow the user to set a time limit for the bot. The program could keep track of how much time has passed while using an iterative depth first search to look as deep as possible in the allotted time.
 - An opening book could be generated to save computation early in the game.
 - It would be interesting to explore completely different artificial intelligence algorithms, such as training a neural network or support vector machine to play.

It should be noted that Connect Four is a [solved game](https://en.wikipedia.org/wiki/Solved_game), and literature is available describing programs capable of guaranteeing a win. The purpose of improving these algorithms as described here would be for personal development and enjoyment. The availability of these programs could also make them useful for training machine learning algorithms, or evaluating the performance of different methods.

## Credit
Thank you to the University of Sydney for the original task specifications (including ```utility```, ```evaluation```, and ```score``` functions found in ```evaluation.cpp```) as well as the example input image used in this README.

## Disclaimer
This work is entirely my own and has been modified since it was implemented for an assignment. It should not be copied in any form by students in university courses with similar assignments. If you are struggling with a similar project and want to get in touch I would be happy to have a chat and help out with your understanding of AI or point you to some useful resources!
