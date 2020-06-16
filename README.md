# Connect4 game vs Minimax algorithm

Connect4 game implemented on C++ with possibility of Player vs Machine, Player vs Player and Machine vs Machine.
Machine IA consist on a Minimax Algorithm with Alpha-Beta Prunning

<!-- THIS FILE IS ON MARKDOWN FORMAT. PLEASE READ IT ON GITLAB REPO: "https://gitlab.com/Nico_Chico/backtraking-algorithm-for-sudoku"
YOU CAN ALSO USE A PROPER .MD VISOR TO READ IT OR CONVERT TO PDF -->

# Backtraking Algorithm for Sudoku

*Laboratory 3, Introduction to Artificial Intelligence*

This is the third **laboratory work** of the **Introduction to Artificial Intelligence** 2020 course in the Computer Science program from **Politechnika Wrocławska** University.

The objective is getting familiar with Minimax algorithm and alpha-beta prunning using it to play a game. The game selected is connect 4.

The project has been entirely developed in C++ language.

## Game description:
This game for two players consist on a board of 7 width and 6 of height.
The player drop his piece on the top and it will fall until touch another piece.
The objective is get 4 pieces connected in vertical, horizontal or diagonals.

![game img](https://gitlab.com/Nico_Chico/connect4-game-vs-minimax-algorithm/-/raw/master/gameScreenshot.png)

# Parameters
The game have the posibility of select with player start, what type of player is each one of them (human or IA) and switch the alpha-beta prunning and set the start depth of the Minimax algorithm.
For all this you will have to make the changes in the main.cpp and rebuild. 


## How to compile the code

```bash
g++ -Wall -o Connect4 main.cpp
```

## To run the program

There is different versions already compiled with fixed parameters to make it easy.
`Connect4_PlvsAI` will run a game vs AI but it will not show any AI information on the screen.

`Connect4_PlvsAI` with info will show AI background info on the screen.

To run:
*In the project directory*
```bash
./Connect4...
```
## Project Structure
Basically, the code consists int:
### Connect4.hpp class
	Deal with all the game operations and the AI and main function
		
### Main.cpp:
	Control the gameLoop and most of the important set up parameters.
	
### Algorithm used
#### Minimax algorithm
I use the minimax algorithm in order to make a search of depth n betwenn all the possible moves, to finally select the best move.
This selection will be based on a score system when the depth is 0 or there is a Terminal node. To get info about this score and how the minimax algorithm match with Connect4 see the comments on the code in `Connect4.hpp`

            function minimax(node, depth, maximizingPlayer) is
            if depth = 0 or node is a terminal node then
                return the heuristic value of node
            if maximizingPlayer then
                value := −∞
                for each child of node do
                    value := max(value, minimax(child, depth − 1, FALSE))
                return value
            else (* minimizing player *)
                value := +∞
                for each child of node do
                    value := min(value, minimax(child, depth − 1, TRUE))
                return value
                    
    
            (* Initial call *)
            minimax(origin, depth, TRUE)
                
#### Minimax algorithm upgraded with Alpha-Beta prunning
I use the minimax algorithm in order to make a search of depth n betwenn all the possible moves, to finally select the best move.
This selection will be based on a score system when the depth is 0 or there is a Terminal node. To get info about this score and how the minimax algorithm match with Connect4 see the comments on the code in `Connect4.hpp`

            function alphabeta(node, depth, α, β, maximizingPlayer) is
                if depth = 0 or node is a terminal node then
                    return the heuristic value of node
                if maximizingPlayer then
                    value := −∞
                    for each child of node do
                        value := max(value, alphabeta(child, depth − 1, α, β, FALSE))
                        α := max(α, value)
                        if α ≥ β then
                            break (* β cut-off *)
                    return value
                else
                    value := +∞
                    for each child of node do
                        value := min(value, alphabeta(child, depth − 1, α, β, TRUE))
                        β := min(β, value)
                        if β ≤ α then
                            break (* α cut-off *)
                    return value
                
                (* Initial call *)
                minimax(origin, depth, TRUE)


*For a more precisely description see the comments on the code.*
## Experiment, analysis & conclusions:
*In progress*
		AB: 8, between 41353265442 and 62813541345 µs for each movement

---
 Project by: **Nicolás Magro Cruzado** | [GitLab](https://gitlab.com/Nico_Chico) ⌨️
