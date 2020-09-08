<!-- THIS FILE IS ON MARKDOWN FORMAT. PLEASE READ IT ON GITLAB REPO: "https://gitlab.com/Nico_Chico/backtraking-algorithm-for-sudoku"
YOU CAN ALSO USE A PROPER .MD VISOR TO READ IT OR CONVERT TO PDF -->

# Connect4 game vs Minimax algorithm

Connect4 game for Linux Terminal implemented on C++ with possibility of Player vs Machine, Player vs Player and Machine vs Machine.
Machine IA consist on a Minimax Algorithm with Alpha-Beta Prunning

The objective of this project is getting familiar with Minimax algorithm and alpha-beta pruning using it to play a game. The game selected is Connect Four (also called as "four in a line"). (https://en.wikipedia.org/wiki/Connect_Four)

The project has been entirely developed in C++ language.

## Game description:
This game for two players consist on a board of 7 width and 6 of height.
The player drop his piece on the top and it will fall until touch another piece.
The objective is get 4 pieces connected in vertical, horizontal or diagonals.

![game img](https://gitlab.com/Nico_Chico/connect4-game-vs-minimax-algorithm/-/raw/master/gameScreenshot.png)

![game img](https://gitlab.com/Nico_Chico/connect4-game-vs-minimax-algorithm/-/raw/master/selectionmenuScreenshot.png)

# Parameters
The game have the posibility of select with player start, what type of player is each one of them (human or IA) and switch the alpha-beta prunning and set the start depth of the Minimax algorithm.
For all this you will have to make the changes in the main.cpp and rebuild. 


## How to compile the code

```bash
g++ -Wall -o ConnectFour main.cpp
```

## To run the program

To run:
*Execute the ConnectFour file*
```bash
./ConnectFour
```
There are also compiled within the folder machine_moves_info which have activated the console output of the Minimax algorithm, which will allow us to see in detail all the search tree in each move.


## Project Structure
Basically, the code consists int:
### Connect4.hpp class
	Deal with all the game board operations and the AI funtions used for Minimax algorithm and AlfaBeta prunning.
		
### Main.cpp:
	Control the game loop, the input and output of the player and most of the important set up parameters.
	
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
                
#### Minimax algorithm upgraded with Alpha-Beta pruning
I use the minimax algorithm in order to make a search of depth n between all the possible moves, to finally select the best move.
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
## Algorithm compute Times analysis 

Below I show 4 games with different depth parameters and using or not alpha-beta pruning.
You can see the cost in time of each IA movement in the item.
        
    Minimax depth 6:
                	START GAME	
                	  481807µs
                	  445949µs
                	  382154µs
                	  478308µs
                	  462658µs
                	  432432µs
                	  313379µs
                	  304806µs
                	  228421µs
                	  287337µs
                	  251501µs
                	  248089µs
                  	  END GAME
                
    Minimax depth 6 with alpha-beta prunning:
                	START GAME
                	  482786µs
                	  478974µs
                	  468419µs
                	  310755µs
                	  201079µs
                	  139831µs
                	  147130µs
                 	  157240µs
                	  140004µs
                	  112847µs
                	   43294µs
                  	  END GAME
                
    Minimax depth 8:
                	START GAME	
                	24084293µs
                	22199679µs
                	13910414µs
                	18567941µs
                	15425741µs
                	12343115µs
                	10697763µs
                	 2914534µs
                	  876564µs
                	  509791µs
                	  404952µs
                	   93477µs
                	  111103µs
                	   66411µs
                	  END GAME
                	   
    Minimax depth 8 with alpha-beta prunning:
                	START GAME
                	22139036µs
                	14837762µs
                	22009460µs
                	20162463µs
                	15936356µs
                	 4734893µs
                	 2404324µs
                	 1469703µs
                	  471068µs
                	  139007µs
                	  110568µs
                	   45465µs
                	    4988µs
                	    2859µs
                	  END GAME


### Conclusions:
Obviously the time to make a decision is reduced as the number of possibilities to be evaluated is reduced. (Fewer cells available)

This reduction is accentuated by the use of alpha-beta pruning.

The more advanced the game is, the more options are pruned, and the more time is reduced.

We can also see that the power of the pruning is more noticeable the deeper we launch the Minimax algorithm

The result given by the minimax algorithm is very good. (If we want AI to always win)

From a depth of 3 it becomes almost impossible to defeat, as it is taking into account all possible steps in 3 moves. If we add more depth, it's already unfair to the human player.

### Possible improvements
We could save the tree that generates the algorithm and when executing a movement we could keep that branch.
So if the depth is n, we should only compute the new n-depth possibilities and not all the previous ones, saving time in creating the boards and evaluating them.


    

---
 Project by: **Nicolás Magro Cruzado** | [GitLab](https://gitlab.com/Nico_Chico) ⌨️
