#include "Connect4.hpp"
#include <iostream>
#include <unistd.h>	//for  sleep() and build getch()
#include <termios.h> //for getch()
#include <chrono>

char getch(void) {
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if(tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if(tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if(read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
//    printf("%c\n", buf);
    return buf;
}
 
struct Player {
	int color;
	bool isHuman;
	Player(int col, bool hum) { color = col; isHuman = hum; }
};

int main (int argc, char const* argv[]) {
	Connect4 game;
	const std::string title =
						R"(
	                                        ██╗  ██╗ 
	       ░▄▀▀░▄▀▄░█▄ █░█▄ █▒██▀░▄▀▀░▀█▀   ██║  ██║	
	       ░▀▄▄░▀▄▀░█▒▀█░█▒▀█░█▄▄░▀▄▄ ▒█▒▒░ ███████║ 
	                                        ╚════██║
	                                             ██║
	                                             ╚═╝ )";
	
	Player p1(1, true);		// Blue 
	Player p2(2, false);     // Red
	Player* currPlayer = &p1; 	// AIM TO CURRENT PLAYER //First turn to p1;
	char c;		// catch the key input of keyboard using getch
	int select=3;		// Position 3 selected by default

	bool turnFinished = false;
	bool gameForceExit = false;
	int winner = 0;
	
	// Variables used to check compute time of AI
	auto t1 = std::chrono::high_resolution_clock::now();
	auto t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
	
	// GAME LOOP
	while(winner == 0 && !gameForceExit) {
		while(!turnFinished) {
			if(currPlayer->isHuman) {	// HUMAN PLAYER
				// UPDATING SCREEN
//				system("clear");
				std::cout << title << std::endl;
				//Show selection piece
				std::cout << "\t\t\t ";
				for(int i=0; i<select; i++) 		
					std::cout << "   ";
				if(currPlayer->color == 1)
					std::cout << "🔵" <<std::endl;
				else if(currPlayer->color == 2)
					std::cout << "🔴" <<std::endl;
				game.showBoard();	// Show the board;
				std::cout << "    Controls:  🅰  = ⬅️   |  🆂 or 🆂🅿🅲 = set  |  🅳  = ➡️   |  🅴  = 🚫" << std::endl;
				//READING INPUT
				c = getch();
				switch(c) {
					case 'd':
					 	select++;
					 	if(select==game.width)
					  		select=0;
					  	break;
				   	case 'a':
					  	select--;
					  	if(select==-1)
					  		select=game.width-1;
					  	break;
					case 's':
					case ' ':
					  	if(game.setPiece(select, currPlayer->color))
					  		turnFinished = true;
					  	break;
				  	case 'e':
				  		turnFinished = true;
				  		gameForceExit = true;
				  		break;
					
				}
			} else if(currPlayer->isHuman == false) { // AI
				// UPDATING SCREEN
//				system("clear");
				std::cout << title << std::endl;
				std::cout << std::endl;
				game.showBoard();	// Show the board;

				t1 = std::chrono::high_resolution_clock::now(); 	// Time point 1
				
				//AI moves using simple bestMove selector;
//				int bestCol = game.pickBestMove(currPlayer->color);
//				std::cout <<"    Column selected by AI: " << bestCol << std::endl;
//				game.setPiece(bestCol, currPlayer->color);

				//AI move using MINIMAX
//				miniMaxRet ret = game.miniMax(game.board, 8, true, currPlayer->color);	
//				//AI move using MINIMAX with ALPHA BETA PRUNING
				miniMaxRet ret = game.miniMaxAlphaBeta(game.board, 8, -INT_MAX, INT_MAX, true, currPlayer->color);	

				t2 = std::chrono::high_resolution_clock::now();		// Time point 2
				duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();	// Calc duration
				//Showing data of the IA move.
				std::cout << "    AI data |  Score: " << ret.score << " | Selected col: " << ret.bestMove << " | Time wasted: " << duration << "µs"  << std::endl;
				game.setPiece(ret.bestMove, currPlayer->color);

				usleep(100000);		// Delay
				turnFinished = true;
			}
		}
		// Switch currPlayer
		if(currPlayer == &p1)
			currPlayer = &p2;
		else currPlayer = &p1;
		turnFinished = false;
		winner = game.getWinner();
	}
	// GAME END - COMPROBATIONS:
//	system("clear");
	std::cout << title << std::endl << std::endl;
	game.showBoard();	// Show the board;
	if(winner == -1)
		std::cout << "    The board is full! No winner :(  " << std::endl;
	else if(winner == 1)
		std::cout << "    The winner is BLUE player!  🔵 " << std::endl;
	else if(winner == 2)
		std::cout << "    The winner is RED player!  🔴 " << std::endl;				
	return 0;
}
