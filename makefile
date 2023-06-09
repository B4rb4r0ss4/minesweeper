output:
	@g++ ./src/main.cpp ./src/game.cpp ./src/field.cpp ./src/console.cpp ./src/window.cpp -o main -fsanitize=address -g -lsfml-graphics -lsfml-window -lsfml-system -Wall -Wextra -Wno-ignored-qualifiers
