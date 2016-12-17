#ifndef PLAYER
#define PLAYER

#include "defs.hpp"
#include "gameState.hpp"

#include <iostream>
#include <string>

class Player {
private:
	Move strToMove(std::string start, std::string end);
public:
	Move getMove(GameState state);
};

Move Player::getMove(GameState state) {
	Move move;
	int isValidMove = 0;

	// Get a valid move
	do {
		std::cout << "Select a piece to move: ";
		std::string start;
		std::cin >> start;

		std::cout << "Select a destination: ";
		std::string end;
		std::cin >> end;

		move = strToMove(start, end);
		isValidMove = state.isValidMove(move, PLAYERTEAM);
		if (!isValidMove) {
			std::cout << "That move is invalid." << std::endl;
		}
	} while (!isValidMove);

	return move;
};

// Rows: Numbers (1 to 8) (ASCII 49 to 56)
// Cols: Letters (A to H) (ASCII 65 to 72)
Move Player::strToMove(std::string start, std::string end) {
	// Set the move row and column
	Move move;
	move.start.row = (int)(start.at(0) - 49);
	move.start.col = (int)(start.at(1) - 65);
	move.end.row = (int)(end.at(0) - 49);
	move.end.col = (int)(end.at(1) - 65);

	return move;
}

#endif
