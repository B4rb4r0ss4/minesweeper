#include "minesweeper.h"

#include <iostream>
#include <string>
#include <unordered_map>


inline std::vector<char> getSepNum(int num) {
    std::vector<char> nums;
    do {
        nums.push_back(num%10 + '0');
    } while(num/=10);
    nums.push_back('0');
    nums.push_back('0');
    nums.push_back('0');
    return nums;
}

void Game::loadTextures() {
    sf::Texture blank; blank.loadFromFile("./src/images/blank.gif");
    textures["blank"] = blank;

    std::string open = "./src/images/open";
    std::string time = "./src/images/time";
    for(int i=0; i<9; i++) {
        std::string path = open+std::to_string(i)+".gif";
        sf::Texture openi; openi.loadFromFile(path);
        std::string name = "open" + std::to_string(i);
        textures[name] = openi;
    
        std::string path2 = time+std::to_string(i)+".gif";
        std::string name2 = "time" + std::to_string(i);
        sf::Texture timei; timei.loadFromFile(path2);
        textures[name2] = timei;
    }

    sf::Texture flag; flag.loadFromFile("./src/images/bombflagged.gif");
    textures["flag"] = flag;
    sf::Texture bomb; bomb.loadFromFile("./src/images/bombdeath.gif");
    textures["bomb"] = bomb;
    sf::Texture incFla; incFla.loadFromFile("./src/images/bombmisflagged.gif");
    textures["incFlag"] = incFla;
    sf::Texture bombRev; bombRev.loadFromFile("./src/images/bombrevealed.gif");
    textures["bombRev"] = bombRev;
    sf::Texture faceSmile; faceSmile.loadFromFile("./src/images/facesmile.gif");
    textures["faceSmile"] = faceSmile;
    sf::Texture sadSmile; sadSmile.loadFromFile("./src/images/facedead.gif");
    textures["sadSmile"] = sadSmile;
     sf::Texture winSmile; sadSmile.loadFromFile("./src/images/facewin.gif");
    textures["winSmile"] = sadSmile;
    sf::Texture time9; time9.loadFromFile("./src/images/time9.gif");
    textures["time9"] = time9;
}



void Game::initWindow() {
    // Initialize window
    viMode.height = boardSize * 32 + 180;
    viMode.width = boardSize * 32 + 40;
    window = new sf::RenderWindow(viMode, "Minesweeper");
    window->setFramerateLimit(40); 
    running = 1;
    window->clear(sf::Color(150, 150, 150, 255));
    displayBoard();
    run();

}

void Game::Field::display(int i, int j) {
    sf::Sprite sprite; 
    if(!opened && !getFlagged()) {
       sprite.setTexture(game->textures["blank"]);
    } else if(getFlagged()){
       sprite.setTexture(game->textures["flag"]); 
    } else if(!hasMine) {
        std::string name = "open"+std::to_string(minesAround);
        sprite.setTexture(game->textures[name]);
    } else if(hasMine) {
        sprite.setTexture(game->textures["bomb"]);
    }
    sprite.setPosition(j*32+20, i*32+90);
    game->window->draw(sprite);
}

void Game::displayBoard() {
    sf::Sprite sprite; sprite.setTexture(textures["faceSmile"]);
    for(int i=0; i<boardSize; i++) {
        for(int j=0; j<boardSize; j++) {
            board[j][i].display(i, j);
        }
    }
    sprite.setPosition((boardSize*32-16)/2, 20);
    window->draw(sprite);
}

bool Game::Field::isClicked(sf::Vector2f mouse) {
    //return shape.getGlobalBounds().contains(mouse);
    return mouse.x > x*32+20 && mouse.x < x*32+52 && mouse.y > y*32+50 && mouse.y < y*32+82;
}

bool Game::run() {
        sf::Event event;
        
        while(window->pollEvent(event)) {
	    if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
              	int curX = (mousePosition.x);
                int curY = (mousePosition.y);
                  
		if(curX >= (boardSize*32-16)/2 && curX <= (boardSize*32-16)/2+48 && curY >=20 && curY <= 68) {
                    startGame(boardSize, howManyBombs);
                    return 0;
                }
		else if(curY <= 90 || curX <= 20 || curX >= 32*boardSize+20 || curY >= 32*boardSize+90) return 1;
		curX = (mousePosition.x-20)/32;
                curY = ((mousePosition.y-90)/32);
               
		reveal(curY, curX);
               
                moves++;
                window->clear(sf::Color(150, 150, 150, 255));
                displayBoard();

            } else if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
                int curX = (mousePosition.x-20)/32;
                int curY = ((mousePosition.y-90)/32);
                flag(curY, curX);
                window->clear(sf::Color(150, 150, 150, 255));
                displayBoard();
 
            } 
	    else if(event.type == sf::Event::Closed) window->close();
        }
	return 1;
        
}

bool Game::isRunningg() {
    return window->isOpen();
}
void Game::Field::displayEnd(int i, int j) {
    sf::Sprite sprite;

    if(getFlagged() && hasMine){
       sprite.setTexture(game->textures["flag"]); 
    } else if(getFlagged() && !hasMine) {
        sprite.setTexture(game->textures["incFlag"]);
    } else if(!hasMine && getOpened()) {
        std::string name = "open"+std::to_string(minesAround);
        sprite.setTexture(game->textures[name]);
    } else if(hasMine && !getOpened()) {
        sprite.setTexture(game->textures["bombRev"]);
    } else if(getOpened() && hasMine) {
        sprite.setTexture(game->textures["bomb"]);
    } else {
        sprite.setTexture(game->textures["blank"]);
    }
    sprite.setPosition(j*32+20, i*32+90);
    game->window->draw(sprite);


}
void Game::displayEnd() {
    window->clear(sf::Color(150, 150, 150, 255));
     for(int i=0; i<boardSize; i++) {
        for(int j=0; j<boardSize; j++) {
            board[j][i].displayEnd(i, j);
        }
    }

    sf::Sprite sprite; 
    if(!win)
        sprite.setTexture(textures["sadSmile"]);
    else 
        sprite.setTexture(textures["winSmile"]);
    sprite.setPosition((boardSize*32-16)/2, 20);
    window->draw(sprite);

}

bool Game::isEnd() {
    if(running) return false;
    if(!toWin) std::cout<<"Win\n";
    if(!win) std::cout<<"Loose\n";
    return 1;
}

void Game::displayTime(int num) {
    std::vector<char> nums = getSepNum(num);
    sf::Sprite time1, time2, time3;
    std::string tmp1 = "time", tmp2 = "time", tmp3 = "time";
    tmp1.push_back(nums[0]);
    tmp2.push_back(nums[1]);
    tmp3.push_back(nums[2]);
    time1.setTexture(textures[tmp1]);
    time2.setTexture(textures[tmp2]);
    time3.setTexture(textures[tmp3]);
    time1.setPosition(boardSize*32-10, 20);
    time2.setPosition(boardSize*32-35, 20);
    time3.setPosition(boardSize*32-60, 20);
    window->draw(time1);
    window->draw(time2);
    window->draw(time3);

}
void Game::displayy() {
    window->display();
}

void Game::displayHowManyFlags() {
    std::vector<char> nums = getSepNum(howManyFlags);
    std::string tmp1 = "time", tmp2 = "time", tmp3 = "time";
    sf::Sprite time1, time2, time3;
    tmp1.push_back(nums[0]);
    tmp2.push_back(nums[1]);
    tmp3.push_back(nums[2]);
    time1.setTexture(textures[tmp1]);
    time2.setTexture(textures[tmp2]);
    time3.setTexture(textures[tmp3]);
    time3.setPosition(20, 20);
    time2.setPosition(45, 20);
    time1.setPosition(70, 20);
    window->draw(time1);
    window->draw(time2);
    window->draw(time3);
}

bool Game::waitForE() {
        sf::Event event;
        
        while(window->pollEvent(event)) {
            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
                int curX = (mousePosition.x);
                int curY = (mousePosition.y);
                if(curX >= (boardSize*32-16)/2 && curX <= (boardSize*32-16)/2+48 && curY >=20 && curY <= 68) {
                    startGame(boardSize, howManyBombs);
                    return 1;
                }

            }
            else if(event.type == sf::Event::Closed) 
                window->close();
        }
        return 0;
}


