#include "minesweeper.h"
#include <ctime>
#include <cmath>
#include <iostream>

inline const int randi(const int& a, const int& b) {
	return a + rand()%(b - a + 1);
}

Game::Game(int _width, int _mines) {
    howManyBombs = _mines;
	boardSize = _width;

    toWin = boardSize * boardSize - howManyBombs;
    leftGap = ceil(log10(boardSize)) + 1;
    srand(time(NULL));
    running = false;
    moves = 0;
    win = 1;
    howManyFlags = howManyBombs;
    loadTextures(); 
    board = std::vector<std::vector<Field>> (boardSize);
    for(int i=0; i<boardSize; i++) {
        for(int j=0; j<boardSize; j++) {
			board[i].emplace_back(j, i, this);
		}
	}
}

void Game::restart() {
	toWin = boardSize * boardSize - howManyBombs;
	running = false;
	moves = 0;
	win = 1;
	howManyFlags = howManyBombs;
	board = std::vector<std::vector<Field>> (boardSize);
  	for(int i=0; i<boardSize; i++) {
       		for(int j=0; j<boardSize; j++) {
			board[i].emplace_back(j, i, this);
		}
	}
	running = 1;
	window->clear(sf::Color(150, 150, 150, 255));
	displayBoard();
	run();
}

void Game::startGame(const int x, const int y) {
    generateBoard(x, y);
    running = 1;
}

void Game::generateBoard(const int x, const int y) {
	int cnt = 0;
	while(cnt != howManyBombs) {
		const int x1 = randi(1, boardSize)-1;
		const int y1 = randi(1, boardSize)-1;
		if(board[y1][x1].getHasMine() || (abs(x-x1) <= 1 && abs(y-y1) <= 1)) 
			continue;
		board[y1][x1].addMine();
		cnt++;
	}
}

void Game::reveal(const int x, const int y) {
    if(!moves) startGame(x, y);
    if(board[y][x].getFlagged()) return;
    board[y][x].reveal();
}

void Game::flag(int x, int y) {
    board[y][x].flag();
}

void Game::lose() {
    running = false;
    win = false;
}

Game::~Game() {
    board.clear();
    delete window;
}

