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

![game img](https://gitlab.com/Nico_Chico/connect4-game-vs-minimax-algorithm/-/raw/master/gameScreenshot.png)


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
<!--## Project Structure-->
<!--Basically, the code consists int the class Sudoku and main function.-->
<!--Diferents sudoku problems are saved on the data files: `Sudoku9.csv` `Sudoku16.csv` & `Sudoku25.csv` -->

<!--### Class Sudoku:   `Sudoku.hpp`-->
<!--This class is responsible of store and deal with the sudoku grid and the methods necessary to implement Backtracking.-->

<!--### Main function :       `SudokuSolver.cpp`-->
<!--Starts and checks the computation time by solving all the problems contained in:-->

<!--`Sudoku9.csv`	46 problems of 9×9, diferent difficulties-->

<!--`Sudoku16.csv` 	1 problem of 16×16.-->

<!--`Sudoku25.csv` 	1 problem of 25×25.-->

<!--In addition to these the program can solve any N×N sudoku. Where N is a perfect square.-->
<!--These problems can be initialized with all unassigned items, or from a file, as we do with the ones explained above.-->

<!--However, as we will see in the experiments, from 25x25 the computation time of the algorithm scales very much and can last for days.-->

<!--N can be changed on the `main.cpp`-->

<!--## Formulating the problem.-->
<!--For the sake of simplicity, I'll explain the problem by assuming a classic 9x9 Sudoku grid. -->
<!--The numbers that we will place on the grid must belong to the interval [1, 9].-->
<!--In addition, in order to meet our goal, we will have to address a number of constraints. We can model them as the following 3.-->

<!--1. All the numbers in the range [1, 9] should appear in each row. Therefore none of these numbers will appear twice on the same line. Since we have 9 different numbers and exactly 9 places to put them.-->

<!--        [ 1 4 6 5 3 2 8 9 7 ] ✅ -->
<!--        -->
<!--        [ 2 4 5 6 3 3 2 1 1 ] ❌-->

<!--2. All the numbers in the range [1, 9] should appear in each column. Therefore none of these numbers will appear twice on the same column.-->
<!--3. All the numbers in the range [1, 9] should appear in each subgrid of 3x3 results from dividing our 9x9 grid into 9 subgrids of 3x3. -->

<!--These three restrictions are reflected in the checkRow(), checkCol() and checkBox() methods of the Sudoku class respectively.-->
<!--```c++-->
<!--	bool checkRow(int row, int num);            // Check if the number already exists in the row: -->
<!--	bool checkCol(int col, int num);            // Check if the number already exists in the column: -->
<!--	bool checkBox(int row, int col, int num); 	// Check if the number already exists in the box(subgrid): -->

<!--```-->

<!--This can be extended to a Sudoku of N×N but we must keep in mind that N must be a perfect square in order for the forms and properties of the Sudoku to be maintained.-->
<!--Then we only have to change the domain of our values of [1, N].-->
<!--Therefore the possible Sudokus would be:-->

<!--        2² -> 4×4-->
<!--        3² -> 9×9-->
<!--        4² -> 16×16 -->
<!--        5² -> 25×25-->
<!--        6² -> 36×36-->
<!--        7² -> 49×49-->
<!--        ...-->



## Experiment, analysis & conclusions:
		AB: 8, between 41353265442 and 62813541345 µs for each movement

---
 Project by: **Nicolás Magro Cruzado** | [GitLab](https://gitlab.com/Nico_Chico) ⌨️
