#include "Connect4.hpp"
#include <iostream>
#include <unistd.h>	//for getch()
#include <termios.h> //for getch()

char getch(void)
{
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

int main (int argc, char const* argv[])
{
	Connect4 game;
	const std::string title =
						R"(
	                                        ██╗  ██╗ 
	       ░▄▀▀░▄▀▄░█▄ █░█▄ █▒██▀░▄▀▀░▀█▀   ██║  ██║	
	       ░▀▄▄░▀▄▀░█▒▀█░█▒▀█░█▄▄░▀▄▄ ▒█▒▒░ ███████║ 
	                                        ╚════██║
	                                             ██║
	                                             ╚═╝ )";
	char c;		// catch the key input of keyboard using getch
	int select=3;
	int player = 1; 	// 1 = blue, 2 = red
	bool turnFinished = false;
	bool gameForceExit = false;
	int winner = 0;
	// GAME LOOP
	while(winner == 0 && !gameForceExit) {
		while(!turnFinished) {
			// UPDATING SCREEN
			system("clear");
			std::cout << title << std::endl;
			//Show selection piece
			std::cout << "\t\t\t ";
			for(int i=0; i<select; i++) 		
				std::cout << "   ";
			if(player==1)
				std::cout << "🔵" <<std::endl;
			else if(player==2)
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
				  	if(game.setPiece(select, player))
				  		turnFinished = true;
				  	break;
			  	case 'e':
			  		turnFinished = true;
			  		gameForceExit = true;
			  		break;
				
			}
		}
		// Switch player
		if(player==1)
			player = 2;
		else player = 1;
		turnFinished = false;
		winner = game.getWinner();
	}
	// GAME END - COMPROBATIONS:
	system("clear");
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
