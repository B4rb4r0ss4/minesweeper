#include "minesweeper.h"
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::to_string;
#define RED 31
#define GREEN 32

string getColored(const string& text, int color) {
    return ("\033[1;" + to_string(color) + "m" + text + "\033[0m");
}

/*void Game::lose() {
    cout<<getColored("Lose!", RED);
    running = 0;
}*/

bool Game::isRunning() {
    if(!toWin) {
        running = 0;
        //cout<<getColored("WIN!", GREEN);
    }
    return running;
}

void Game::display() {
    int z = 1; 
    for(int i=0; i<leftGap; i++) cout<<" ";
    int cnt = 0;
    for(int i=0; i<boardSize; i++) {
        if(!(i%z)) {
            cnt++;
            z*=10;
        }
        cout<<i;
        for(int j = 0; j<leftGap - cnt; j++) cout<<' ';

    }
    cout<<'\n';
    cnt = 0;
    z = 1;
    for(int i=0; i<boardSize; i++) {
        if(!(i%z)) {
            cnt++;
            z*=10;
        }
        std::cout<<i;
        for(int j=0; j<leftGap-cnt; j++) std::cout<<' ';
        for(int j=0; j<boardSize; j++) { 
            if(!board[i][j].getOpened()) 
                std::cout<<"\033["<<(board[i][j].getFlagged() ? 41: 43) <<"m \033[0m";
            else if(board[i][j].getHasMine()) 
                cout<<"\033[1;31mX\033[0m";
            else 
                std::cout<<"\033[1;"<<37-board[i][j].getMinesAround()<<"m"<<board[i][j].getMinesAround()<<"\033[0m";
            for(int k = 0; k<leftGap-1; k++) 
                std::cout<<' '; 
        }
        std::cout<<"\n";
    }
}
