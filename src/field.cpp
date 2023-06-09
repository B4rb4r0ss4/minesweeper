#include "minesweeper.h"

#include <iostream>
Game::Field::Field(const int _x, const int _y, Game* _game) 
    : game(_game) , x(_x), y(_y) {
    hasMine = false;
    opened = false;
    flagged = false;
    minesAround = 0;
}

void Game::Field::adj(void(*fun)(Field* field)) {
        for(int x2 = std::max(x - 1, 0); x2 < std::min(x + 2, game->boardSize); x2++) {
            for(int y2 = std::max(y - 1, 0); y2 < std::min(y + 2, game->boardSize); y2++) {
                if(x2 == x && y2 == y) {
                    continue;
                }
                fun(&(game->board[y2][x2]));
            }
        }
}

void Game::Field::addMine() {
	hasMine = true;
	adj([](Field* field){
		field->minesAround++;
			}); 	
}

void Game::Field::flag() {
    if(game->howManyFlags <= 0 && !flagged) return;
    flagged = !flagged;
    if(flagged) game->howManyFlags--;
    else game->howManyFlags++;
}

void Game::Field::reveal() {
    if(opened) return;
    if(hasMine) {
        opened = true;
        game->lose();
        return;
    }
    opened = true;
    game->toWin--;
    if(!game->toWin) game->running = false;
    if(!minesAround) {
        adj([](Field* field){
                field->reveal();
                });
    } 
}

bool Game::Field::getHasMine() {
	return hasMine;
}

bool Game::Field::getOpened() {
    return opened;
}


int Game::Field::getMinesAround() {
    return minesAround;
}

bool Game::Field::getFlagged() {
    return flagged;
}
