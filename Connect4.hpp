#ifndef CONNECT4_H
#define CONNECT4_H

#include <iostream>
#include <vector>
#include <bits/stdc++.h> 

//#define height 7
//#define width 6

// struct returned by Minimax algorithm
struct miniMaxRet {
	int bestMove;
	int score;
	miniMaxRet(int bestM, int sc) {bestMove = bestM; score = sc;}
};

class Connect4 {
  public:
	static const int width = 7;
	static const int height = 6;
//  private:
	int board[width][height]; 	// Board of the game
  	int winner;  // 0  no winner yet; 1 or 2 player 1 or 2 is the winner
//  public:
	// Initialice the board to 0
  	Connect4();
  	// Return the value of the position	
  	int getPiece(int i, int j);
  	// Drop a piece of player 'val' on the desire column
  	bool setPiece(int col, int val);
  	// Show a board representation
    void showBoard();
    // Return winner value
    int getWinner() { return winner;} 
    // Check if there is a winner on the actual board or if the game is over.
    int checkWinner(int col, int row, int player);
    
// Methods for IA  start here
// ------------------------
    // Copy status on one board on other board.
    void copyGameBoard(int dest[width][height], int origin[width][height]);
	// Evaluates and give score to a window (group of 4 cells);
   	int evaluateWindow(int windowCounts[3], int player);
    // Check player win the game on the hypotetical board 'evBoard'
    bool winningMove(int evBoard[width][height], int player);
    // Evaluates score of an hypotetical board where a move is already made. 
    int scoreMove(int board[width][height], int player);
    // Simple selector of best move. Not used in the minimax algorithm.
    int pickBestMove(int player);
	// Minimax that search for the best posible move for the player 'player'.
	miniMaxRet miniMax(int evBoard[width][height], int depth, bool maximizingPlayer, int player);
	// Minimax upgraded with Alpha-Beta Prunning
	miniMaxRet miniMaxAlphaBeta(int evBoard[width][height], int depth, int alpha, int beta, bool maximizingPlayer, int player);
};

Connect4::Connect4() {
	for(unsigned int i=0; i<height; i++)
		for(unsigned int j=0; j<width; j++)
			board[j][i] = 0;
	winner = 0;	// No winner yet
}


bool Connect4::setPiece(int col, int val) {
	// Setting the piece
	int h=height;
	while(board[col][h-1]==0 && h>0) 
		h--;
	if(h==height)
		return false;
	else {
		board[col][h] = val;
		// Checking the board;
		winner = checkWinner(col, h, val);
		return true;
	}
}


int Connect4::getPiece(int i, int j) {
	return board[i][j];
}

void Connect4::showBoard() {
	std::string representation = "";
	representation.append("\t\t\t╓┄┄╥┄┄╥┄┄╥┄┄╥┄┄╥┄┄╥┄┄╖\n");
	for(int i=height-1; i>=0; i--) {
		representation.append("\t\t\t");
		for(int j=0; j<width; j++) {
			representation.append("║");		
			if(board[j][i] == 0)
				representation.append("  ");
			else if(board[j][i] == 1)
				representation.append("🔵");
			else if(board[j][i] == 2)
				representation.append("🔴");
			else
				representation.append("❌");
		}
		representation.append("║\n");
		if(i!=0)
			representation.append("\t\t\t╠══╬══╬══╬══╬══╬══╬══╣\n");
		else
			representation.append("\t\t\t╚══╩══╩══╩══╩══╩══╩══╝\n");	
	}
	std::cout << representation << std::endl;
}

int Connect4::checkWinner(int col, int row, int player) {
	int ret = -1;
	int i = 0;
	
	// Check first if the board is not full.
	while(ret == -1 && i < width) {
		if(board[i][height-1] == 0)
			ret = 0;
		i++;
	}
	
	// If board is not full, we check if the player won the game.
	if(ret != -1) {
		// Check if the column have 4 pieces connected
		if(row >= 3) {
			i = 1;		
			while(i<4 && board[col][row - i] == player)
				i++;
			if(i == 4)
				ret = player; // Player won! 	
		}
		
		// Check if have 4 pieces connected in horizontal;
		if(ret != player) {
			int cR = 0, cL = 0;	// Counts rights and lefts pieces of the player;
			while(col+cR+1 < width && board[col+cR+1][row] == player)
				cR++;
			while(col-cL-1 >= 0 && board[col-cL-1][row] == player)
				cL++;
//			std::cout << cL << "|" << cR<< "|" << cL + cR +1 << std::endl;	//DEBUG TOOL
			if(cL + cR + 1 >= 4)
				ret = player;
				
			// Check if have 4 pieces connected in diagonal '/';
			if(ret != player){ 
				int cR = 0, cL = 0;	// Counts rights and lefts pieces of the player;
				while(col+cR+1 < width && row+cR+1 < height && board[col+cR+1][row+cR+1] == player)
					cR++;
				while(col-cL-1 >= 0 && row-cL-1 >= 0 && board[col-cL-1][row-cL-1] == player)
					cL++;
//				std::cout << cL << "|" << cR<< "|" << cL + cR +1 << std::endl; //DEBUG
				if(cL + cR + 1 >= 4)
					ret = player;
					
				// Check if have 4 pieces connected in diagonal '\';
				if(ret != player){ 
					int cR = 0, cL = 0;	// Counts rights and lefts pieces of the player;
					while(col+cR+1 < width && row-cR-1 >= 0 && board[col+cR+1][row-cR-1] == player)
						cR++;
					while(col-cL-1 >= 0 && row+cL+1 < height && board[col-cL-1][row+cL+1] == player)
						cL++;
//					std::cout << cL << "|" << cR<< "|" << cL + cR +1 << std::endl; //DEBUG TOOL
					if(cL + cR + 1 >= 4)
						ret = player;
				}	
			}				
		}
	}
	return ret;
}

////////////////////////////////////////////////////////////

//void Connect4::copyGameBoard(int otherboard[width][height]) {
//	for(int r=0; r<height; r++)
//		for(int c=0; c<width; c++)
//			otherboard[c][r] = board[c][r];
//}

void Connect4::copyGameBoard(int dest[width][height], int origin[width][height]) {
	for(int r=0; r<height; r++)
		for(int c=0; c<width; c++)
			dest[c][r] = origin[c][r];
}

int Connect4::evaluateWindow(int windowCounts[3], int player) {
	int opponent;
	// Saving the opponent id
	if(player == 1)
		opponent = 2;
	else opponent = 1;

	int score = 0;
	if(windowCounts[player] == 4)	// If 4 player pieces in window
		score += 100;
	else if(windowCounts[player] == 3 && windowCounts[0] == 1)
		score += 5;
	else if(windowCounts[player] == 2 && windowCounts[0] == 2)
		score += 2;
		
	if(windowCounts[opponent] == 3 && windowCounts[0] == 1)
		score += -4;
//	else if(windowCounts[opponent] == 3 && windowCounts[0] == 0)
////		score += 50;
//	else if(windowCounts[opponent] == 2 && windowCounts[0] == 2)
//		score -=10;
	return score;
}

int Connect4::scoreMove(int evBoard[width][height], int player) {
	int score = 0;
	
	// Score central columns.
	// It would be a good idea to score central column more than the others.
	
	// Score horizontal
	for(int r=0; r<height; r++) {	// For each row
		for(int w=0; w<width-3; w++) {	//For each window in that row (Window = group of 4 position in horizontal)
			int windowCounts[3] = {0,0,0};		// Count the number of pieces of player and empty
			for(int d=0; d<4; d++)
				windowCounts[evBoard[w+d][r]]++;	
			score += evaluateWindow(windowCounts, player);
		}
	}
	// Score vertical
	for(int c=0; c<width; c++) {	// For each column
		for(int w=0; w<height-3; w++) {	//For each window in that row (Window = group of 4 position in vertical)
			int windowCounts[3] = {0,0,0};		// Count the number of pieces of player and empty
			for(int d=0; d<4; d++)
				windowCounts[evBoard[c][w+d]]++;	
			score += evaluateWindow(windowCounts, player);
		}
	}
	// Score Diagonal '/'
	for(int r=0; r<height-3; r++) {
		for(int c=0; c<width-3; c++) {
			int windowCounts[3] = {0,0,0};		// Count the number of pieces of player and empty
			for(int d=0; d<4; d++)		// 
				windowCounts[evBoard[c+d][r+d]]++;	
			score += evaluateWindow(windowCounts, player);
		}
	}	
	
	// Score Diagonal '\'
	for(int r=0; r<height-3; r++) {
		for(int c=0; c<width-3; c++) {
			int windowCounts[3] = {0,0,0};		// Count the number of pieces of player and empty
			for(int d=0; d<4; d++)		// 
				windowCounts[evBoard[c+d][r+3-d]]++;	
			score += evaluateWindow(windowCounts, player);
		}
	}	 
	
	return score;
}

// SIMPLE AI - ONLY SELECT BEST MOVE
int Connect4::pickBestMove(int player) {
	srand(time(0)); 	// Init rand seed
	int bestScore = 0;
	// Get valid columns. (Colums that is not full)
	std::vector<int> validColumns;
	for(int c=0; c<width; c++)
		if(board[c][height-1] == 0)
			validColumns.push_back(c);
	// Initialice best position to random betweenn valids columns.
	int bestCol = rand() % validColumns.size(); 
	// Search bestCol	
	for(int c : validColumns) { // For each valid column 
		int evBoard[width][height];	// New hypotetical board to evaluate
		copyGameBoard(evBoard, this->board);		// Copy data from our game board;
//		std::cout << "Control 1; column: " << c << std::endl;
		// Set piece of player on evaluating column
		int h=height;
		while(evBoard[c][h-1]==0 && h>0) 
			h--;
		evBoard[c][h] = player;
		
		int score = scoreMove(evBoard, player);
		if(score > bestScore) {
			bestScore = score;
			bestCol = c;		
		}
	}
	
	return bestCol;
}

bool Connect4::winningMove(int evBoard[width][height], int player) {
	// Check horizontal locations for winner
	for(int c=0; c<width-3; c++)
		for(int r=0; r<height; r++)
			if(evBoard[c][r] == player && evBoard[c+1][r] == player && evBoard[c+2][r] == player && evBoard[c+3][r] == player)
				return true;
	// Check vertical locations for winner
	for(int c=0; c<width; c++)
		for(int r=0; r<height-3; r++)
			if(evBoard[c][r] == player && evBoard[c][r+1] == player && evBoard[c][r+2] == player && evBoard[c][r+3] == player)
				return true;

	// Check diagonal '/' locations for winner
	for(int c=0; c<width-3; c++)
		for(int r=0; r<height-3; r++)
			if(evBoard[c][r] == player && evBoard[c+1][r+1] == player && evBoard[c+2][r+2] == player && evBoard[c+3][r+3] == player)
				return true;
	
		// Check diagonal '\' locations for winner
	for(int c=0; c<width-3; c++)
		for(int r=3; r<height; r++)
			if(evBoard[c][r] == player && evBoard[c+1][r-1] == player && evBoard[c+2][r-2] == player && evBoard[c+3][r-3] == player)
				return true;

	// If any of above, return false
	return false;
}

miniMaxRet Connect4::miniMax(int evBoard[width][height], int depth, bool maximizingPlayer, int player) {
	srand(time(0));
	
	int opponent;
	// Saving the opponent id
	if(player == 1)
		opponent = 2;
	else opponent = 1;	
	
	// Get valid columns. (Colums that is not full)
	std::vector<int> validColumns;
	for(int c=0; c<width; c++)
		if(evBoard[c][height-1] == 0)
			validColumns.push_back(c);
	bool playerWin = winningMove(evBoard, player);
	bool opponentWin = winningMove(evBoard, opponent);
	
	// // If depth = 0 or isTerminal
	if(playerWin) {
//		std::cout << "Depth: " << depth << " | PLA_WIN | Score: " << 1000000000 << ", Column " << -1 <<std::endl;
		return miniMaxRet(-1, 1000000000);
	}
	if(opponentWin) {
//		std::cout << "Depth: " << depth << " | OPP_WIN | Score: " << -1000000000 << ", Column " << -1 <<std::endl;
		return miniMaxRet(-1, -1000000000);
	}
	if(validColumns.size() == 0) {	// No valid movements
//		std::cout << "Depth: " << depth << " | NOVALID | Score: " << 0 << ", Column " << -1 <<std::endl;
		return miniMaxRet(-1, 0);
	}
	if(depth == 0 ) {
//		int sc = scoreMove(evBoard, player);
//		std::cout << "Depth: " << depth << " | depth_0 | Score: " << sc << ", Column " << -1 <<std::endl;
//		return miniMaxRet(-1, sc);		
		return miniMaxRet(-1, scoreMove(evBoard, player));
	}
	// IF NOTHING ABOVE ELSE:
	if(maximizingPlayer) {
		int value = -INT_MAX;
		int column = validColumns[rand() % validColumns.size()]; // Initialice best position to random betweenn valids columns.
		for(int c : validColumns) { // For each valid column 
			int evBoardCopy[width][height];	// New hypotetical board to evaluate
			copyGameBoard(evBoardCopy, evBoard);		// Copy data from previous game board;
			// Drop piece of player on evaluating column
			int h=height;
			while(evBoardCopy[c][h-1]==0 && h>0) 
				h--;
			evBoardCopy[c][h] = player;
			miniMaxRet ret = miniMax(evBoardCopy, depth-1, false, player);
			int newScore = ret.score;
			if(newScore > value) {
				value = newScore;
				column = c;		
			}
		}
//		std::cout << "Depth: " << depth << " |   MAX   | Score: " << value << ", Column " << column <<std::endl;
		return miniMaxRet(column, value);
	} else {	// Minimizing player
		int value = INT_MAX;
		int column = validColumns[rand() % validColumns.size()]; // Initialice best position to random betweenn valids columns.
		for(int c : validColumns) { // For each valid column 
			int evBoardCopy[width][height];	// New hypotetical board to evaluate
			copyGameBoard(evBoardCopy, evBoard);		// Copy data from our game board;
			// Drop piece of player on evaluating column
			int h=height;
			while(evBoardCopy[c][h-1]==0 && h>0) 
				h--;
			evBoardCopy[c][h] = opponent;
			miniMaxRet ret = miniMax(evBoardCopy, depth-1, true, player);
			int newScore = ret.score;
			if(newScore < value) {
				value = newScore;
				column = c;		
			}
		}
//		std::cout << "Depth: " << depth << " |   MIN   | Score: " << value << ", Column " << column <<std::endl;
		return miniMaxRet(column, value);
	}
}


miniMaxRet Connect4::miniMaxAlphaBeta(int evBoard[width][height], int depth, int alpha, int beta, bool maximizingPlayer, int player) {
	srand(time(0));
	
	int opponent;
	// Saving the opponent id
	if(player == 1)
		opponent = 2;
	else opponent = 1;	
	
	// Get valid columns. (Colums that is not full)
	std::vector<int> validColumns;
	for(int c=0; c<width; c++)
		if(evBoard[c][height-1] == 0)
			validColumns.push_back(c);
	bool playerWin = winningMove(evBoard, player);
	bool opponentWin = winningMove(evBoard, opponent);
	
	// // If depth = 0 or isTerminal
	if(playerWin) {
//		std::cout << "Depth: " << depth << " | PLA_WIN | Score: " << 1000000000 << ", Column " << -1 <<std::endl;
		return miniMaxRet(-1, 1000000000);
	}
	if(opponentWin) {
//		std::cout << "Depth: " << depth << " | OPP_WIN | Score: " << -1000000000 << ", Column " << -1 <<std::endl;
		return miniMaxRet(-1, -1000000000);
	}
	if(validColumns.size() == 0) {	// No valid movements
//		std::cout << "Depth: " << depth << " | NOVALID | Score: " << 0 << ", Column " << -1 <<std::endl;
		return miniMaxRet(-1, 0);
	}
	if(depth == 0 ) {
//		int sc = scoreMove(evBoard, player);
//		std::cout << "Depth: " << depth << " | depth_0 | Score: " << sc << ", Column " << -1 <<std::endl;
//		return miniMaxRet(-1, sc);		
		return miniMaxRet(-1, scoreMove(evBoard, player));
	}
	// IF NOTHING ABOVE ELSE:
	if(maximizingPlayer) {
		int value = -INT_MAX;
		int column = validColumns[rand() % validColumns.size()]; // Initialice best position to random betweenn valids columns.
		for(int c : validColumns) { // For each valid column 
			int evBoardCopy[width][height];	// New hypotetical board to evaluate
			copyGameBoard(evBoardCopy, evBoard);		// Copy data from previous game board;
			// Drop piece of player on evaluating column
			int h=height;
			while(evBoardCopy[c][h-1]==0 && h>0) 
				h--;
			evBoardCopy[c][h] = player;
			miniMaxRet ret = miniMaxAlphaBeta(evBoardCopy, depth-1, alpha, beta, false, player);
			int newScore = ret.score;
			if(newScore > value) {
				value = newScore;
				column = c;		
			}
			if(value < alpha)
				alpha = value;
			if(alpha >= beta)
				break;
		}
//		std::cout << "Depth: " << depth << " |   MAX   | Score: " << value << ", Column " << column <<std::endl;
		return miniMaxRet(column, value);
	} else {	// Minimizing player
		int value = INT_MAX;
		int column = validColumns[rand() % validColumns.size()]; // Initialice best position to random betweenn valids columns.
		for(int c : validColumns) { // For each valid column 
			int evBoardCopy[width][height];	// New hypotetical board to evaluate
			copyGameBoard(evBoardCopy, evBoard);		// Copy data from our game board;
			// Drop piece of player on evaluating column
			int h=height;
			while(evBoardCopy[c][h-1]==0 && h>0) 
				h--;
			evBoardCopy[c][h] = opponent;
			miniMaxRet ret = miniMaxAlphaBeta(evBoardCopy, depth-1, alpha, beta, true, player);
			int newScore = ret.score;
			if(newScore < value) {
				value = newScore;
				column = c;		
			}
			if(value > beta)
				beta = value;
			if(alpha >= beta)
				break;
		}
//		std::cout << "Depth: " << depth << " |   MIN   | Score: " << value << ", Column " << column <<std::endl;
		return miniMaxRet(column, value);
	}
}

#endif //CONNECT4_H

