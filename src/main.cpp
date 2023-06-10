#include <iostream>
#include "minesweeper.h"

int main(int argc, char* argv[]) {
    // Init minesweeper game
    int width = 10, mines = 20;
    if(argc > 1) {
        width = atoi(argv[1]);
        mines = atoi(argv[2]);
    }
    
   
    Game game(width, mines);

    game.initWindow();
    sf::Clock clock;
    int endedTime = 0; 
    bool end = false; int i = 0;
    do { 
        if(game.isRunning()) {
            if(game.run()) {
            	game.displayHowManyFlags();
            	game.displayTime((int)clock.getElapsedTime().asSeconds());
            	game.displayy(); 
	    } else {
		game.restart();
		end = false;
		i = 0;
		clock.restart();
	    }
        }
        if(!end) {
            end = game.isEnd();
        }
        if(end && !i) {
            i++;
            game.displayEnd(); 
            game.displayHowManyFlags();
            endedTime =  ((int)clock.getElapsedTime().asSeconds());

            game.displayTime(endedTime);
            game.displayy(); 
        }
        else if(end){
            game.displayEnd();
            game.displayTime(endedTime);
            game.displayHowManyFlags();
            game.displayy();
            if(game.waitForE()) {
	    	game.restart();
		end = false;
		i = 0;
		clock.restart();
	    }
        }
    } while(game.isRunningg());
    
    return 0;
    /* 
    //    in terminal
    do {
        game.display();
        char choice;
        std::cout<<"Provide r/f & x & y: ";
        int x, y; std::cin>>choice>>x>>y;
        if(choice == 'r')
            game.reveal(x, y);
        else
            game.flag(x, y);
    } while(game.isRunning());
    */

}



