#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>
#include <chrono>
class Game {
	private:
        std::unordered_map<std::string, sf::Texture> textures; 
		int howManyBombs;
		int boardSize;
        int toWin;
        int leftGap;
		bool running;
        bool win;
        sf::RenderWindow* window;
        sf::VideoMode viMode;
        sf::Event eve;
        class Field {
			private: 
		    	Game* const game;	
                const int x;
				const int y;
                bool hasMine;
				bool opened;
                bool flagged;
			    int minesAround;
                //sf::Sprite shape;
            public:
                Field();
				Field(const int, const int, Game*);

                bool getHasMine();
                bool getOpened();
			    bool getFlagged();
                int getMinesAround();
                
                void addMine();
                void adj(void(*)(Field*));
                void reveal();
                void flag(); 
                bool isClicked(sf::Vector2f);
                void display(int, int);
                void displayEnd(int, int);
		};
        std::vector<std::vector<Field>> board;	 
		void generateBoard(const int, const int);
	public:
        Game(int, int);
		~Game();
        bool isRunning();
        bool isRunningg();
        void loadTextures();          
        void startGame(const int, const int);
		void display();
        void lose();
        void reveal(int x, int y);
        void flag(int x, int y);
        void initWindow();
        void displayBoard();
        void displayEnd();
        void update();
        bool run();
        bool isEnd();
        void displayTime(int);
        void displayy();
        void displayHowManyFlags();
        void restart();
	bool waitForE();
        int moves;
        int howManyFlags; 
};

