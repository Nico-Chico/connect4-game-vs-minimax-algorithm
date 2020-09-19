<!-- THIS FILE IS ON MARKDOWN FORMAT. PLEASE READ IT ON GITLAB REPO: "https://gitlab.com/Nico_Chico/backtraking-algorithm-for-sudoku"
YOU CAN ALSO USE A PROPER .MD VISOR TO READ IT OR CONVERT TO PDF -->

# Connect4 game vs Minimax algorithm

A "Connect Four" game (also called as  "Four in Line") implementation for Terminal developed in C++, with the possibility of playing against the machine in different difficulties or multiplayer.
The "intelligence" of the machine consists of a MiniMax algorithm with Alpha-Beta pruning.

The aim of this project is to become familiar with the Minimax algorithm and alpha-beta pruning by discovering its features and functionality through its implementation in a game. 

Another objective of the project to highlight has been to develop a fully interactive console interface, with a pleasant experience. I have achieved this by using Unicode characters, to give colour and shape, and by precisely controlling the text flow in the terminal.
As we can see, not all console programs have to be ugly and crude in their use. With these ideas you can give them a facelift and make them more interesting and enjoyable.

When the game is run, a selection menu appears that allows us to choose the 2 players. All options are allowed, Human vs Human, Human vs Machine or Machine vs Machine. 
The machine has several difficulty levels, corresponding to the depth with which the MiniMax algorithm tree is launched.

Once the game was functional, I was testing and investigating the behaviour of the algorithms, changing depth, measuring times, and checking decisions. 
This allowed me to draw the conclusions that I present at the end.

The project has been entirely developed by me, in C++ language.

## Game description:
This game for two players consist on a board of 7 width and 6 of height.
The player drop his piece on the top and it will fall until touch another piece.
The objective is get 4 pieces connected in vertical, horizontal or diagonals.

![game img](https://gitlab.com/Nico_Chico/connect4-game-vs-minimax-algorithm/-/raw/master/screenshot_game.png)

![game img](https://gitlab.com/Nico_Chico/connect4-game-vs-minimax-algorithm/-/raw/master/screenshot_menu.png)


## How to compile the code

```bash
g++ -Wall -o ConnectFour main.cpp
```

## To run the program

To run:
*Simply run the compiled file.*
```bash
./ConnectFour
```
There are also compiled file within the folder machine_moves_info which have activated the console output of the Minimax algorithm, which will allow us to see in detail all the search tree in each move. This is for research and debugging purposes. 
To activate this debug output, simply uncomment the corresponding lines of code in the MiniMax() function.


## Project Structure
Basically, the code consists on:
### Connect4.hpp class
Deal with all the game board operations and the AI funtions used for Minimax algorithm and AlfaBeta prunning.
	
When the machine have to make a decision, the program launch the Minimax algorithm, who analyses all possible future moves until he finds one that benefits him and harms the other. When the algorithm reaches a base case, there is a function that scores the state of the board according to how close it is to winning.
		
### Main.cpp:
After launching the selection menu, it control the game loop, the input and output of the player and set up parameters. 
	

## Algorithm used
#### Minimax algorithm
I use the minimax algorithm in order to make a search of depth n betwenn all the possible moves, to finally select the best move.
This selection will be based on a score system when the depth is 0 or there is a Terminal node. 

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
This is an improvement of the algorithm, using a technique to reduce the number of nodes that are evaluated from the whole game tree.

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



*To get more info about the structure of the code, the score system and how the minimax algorithm match with ConnectFour see the comments on the code in file `Connect4.hpp` and `main.cpp`*
	
## Algorithm compute Times analysis 

Below I show 4 games with different depth parameters and using or not alpha-beta pruning.
You can see the cost in time of each IA movement in the item. Each turn is represented by a line.
        
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

We can also see that the power of the pruning is more noticeable the deeper we launch the Minimax algorithm.

The result given by the minimax algorithm is very good. (If we set a high depth value, the machine will always win.)

From a depth of 3 it becomes almost impossible to defeat, as it is taking into account all possible steps in 3 moves. If we add more depth, it's already unfair to a human player.

### Possible improvements
We could save the tree that generates the algorithm and when executing a movement we could keep that branch.
So if the depth is n, we should only compute the new n-depth possibilities and not all the previous ones, saving time in creating the boards and evaluating them.


---
 Project by: **Nicolás Magro Cruzado** | [GitLab](https://gitlab.com/Nico_Chico) ⌨️
