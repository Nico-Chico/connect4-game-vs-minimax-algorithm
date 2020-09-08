#include "Connect4.hpp"
#include <iostream>
#include <unistd.h>	//for  sleep() and build getch()
#include <termios.h> //for getch()
#include <chrono>
#include <string>

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
	int diff; // (difficulty): 0 is human player, 1 is machine player of lvl 1...	
	Player(int col, bool d) { color = col; diff = d; }
};


const std::string title =
						R"(
	                                        ██╗  ██╗ 
	       ░▄▀▀░▄▀▄░█▄ █░█▄ █▒██▀░▄▀▀░▀█▀   ██║  ██║	
	       ░▀▄▄░▀▄▀░█▒▀█░█▒▀█░█▄▄░▀▄▄ ▒█▒▒░ ███████║ 
	                                        ╚════██║
	                                             ██║
	                                             ╚═╝ )";

const std::string controls = R"(            🆆       ⬆️
	  🅰 🆂 🅳 = ⬅️ ⬇️ ➡️             🆂🅿🅲 = set              🅴  = 🚫)";
 						

void difficultySelector(Player &p1, Player &p2) {
	char c;				// catch the key input of keyboard using getch
	int selection = 0;  // option to be chosen
	std::string difficulties[5] = {"     Human      ", " Machine (lv 1) ", " Machine (lv 2) ", " Machine (lv 3) ", " Machine (lv 4) "}; 
	int selecting = 1;	// what player is choosing difficulties in that moment.
	while(selecting < 3) {
		system("clear");
		std::cout << title << std::endl;
		std::cout << std::endl << std::endl;
		std::cout << "\t  Player One (🔵)\t\t\t  Player Two (🔴)" << std::endl;
//		std::cout << "\t    ---------\t\t\t\t    ---------" << std::endl;
		std::cout << "\t ⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼\t\t\t ⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼" << std::endl;
		if(selecting == 1) {
			std::cout << "\t\t▴\t\t\t\t\t▵" << std::endl;
			std::cout << "  \t " << difficulties[selection] << "\t\t\t " << difficulties[p2.diff] << std::endl;
			std::cout << " \t\t▾\t\t\t\t\t▿" << std::endl;
		}
		if(selecting == 2) {
			std::cout << "\t\t▵\t\t\t\t\t▴" << std::endl;
			std::cout << "\t " << difficulties[p1.diff] << "\t\t\t " << difficulties[selection] << std::endl;
			std::cout << "\t\t▿\t\t\t\t\t▾" << std::endl;
		}
		std::cout << "\t ⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼\t\t\t ⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼⎼" << std::endl;
		std::cout << "\n\n\n\n\n\n" << controls << std::endl;
			
		//READING INPUT
		c = getch();
		switch(c) {
			case 's':
			 	selection++;
			 	if(selection==5)
			  		selection=0;
			  	break;
		   	case 'w':
			  	selection--;
			  	if(selection==-1)
			  		selection=4;
			  	break;
			case 'd':
			case ' ':
				if(selecting==1) {
					p1.diff = selection;
					selection = p2.diff;
				}
				else if(selecting == 2) {
					p2.diff = selection;
				}
				selecting++;
			  	break;
		  	case 'a':
		  		if(selecting > 1) {
			  		selecting--;
			  		selection = p1.diff;
		  		}
		  		break;			
		}
	}
}

int main (int argc, char const* argv[]) {
	Player p1(1, 0);	// Blue 
	Player p2(2, 1);    // Red
	difficultySelector(p1, p2);		// Launch Selection Menu
	Connect4 game;
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
			if(currPlayer->diff==0) {	// HUMAN PLAYER
				// UPDATING SCREEN
				system("clear");
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
				std::cout << controls << std::endl;
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
			} else if(currPlayer->diff > 0) { // AI PLAYER
				// UPDATING SCREEN
				system("clear");
				std::cout << title << std::endl;
				std::cout << std::endl;
				game.showBoard();	// Show the board;

				t1 = std::chrono::high_resolution_clock::now(); 	// Time point 1
				
				//Machine moves using simple bestMove selector;
//				int bestCol = game.pickBestMove(currPlayer->color);
//				std::cout <<"    Column selected by AI: " << bestCol << std::endl;
//				game.setPiece(bestCol, currPlayer->color);

//				//Machine move using MINIMAX with ALPHA BETA PRUNING
				miniMaxRet ret = game.miniMaxAlphaBeta(game.board, currPlayer->diff, -INT_MAX, INT_MAX, true, currPlayer->color);	

				t2 = std::chrono::high_resolution_clock::now();		// Time point 2
				duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();	// Calculating duration

				//Showing data of the IA move.
				std::cout << "    Machine move data |  Score: " << ret.score << " | Selected col: " << ret.bestMove << " | Computing time: " << duration << "µs"  << std::endl;
				game.setPiece(ret.bestMove, currPlayer->color);

				usleep(1000000);		// Delay for better experience
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
	system("clear");
	std::cout << title << std::endl << std::endl;
	game.showBoard();	// Show the board;
	std::cout << std::endl;
	if(winner == -1)
		std::cout << "    The board is full! No winner :(  " << std::endl;
	else if(winner == 1)
		std::cout << "    The winner is BLUE player!  🔵 " << std::endl;
	else if(winner == 2)
		std::cout << "    The winner is RED player!  🔴 " << std::endl;				
	return 0;
}
