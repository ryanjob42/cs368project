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
	Move getMove(GameState state, Move prevMove);
};

Move
Player::getMove(GameState state, Move prevMove) {
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

		if (prevMove.endRow != -1) {
			if ( (move.startRow != prevMove.endRow) ||
				  (move.startCol != prevMove.endCol)) {
				std::cout << "You just hopped a piece, you have to move it again!" << std::endl;
				std::cout << "It was on spot " << (char)(prevMove.endCol + 65) << (char)(prevMove.endRow + 49) << std::endl;
				continue;
			}
		}
		if (prevMove.endRow == -1) {
			isValidMove = state.isValidMove(move, PLAYERTEAM, 0, 1);
		} else {
			isValidMove = state.isValidMove(move, PLAYERTEAM, 1, 1);
		}

		if (!isValidMove) {
			std::cout << "That move is invalid. Example selection: A1" << std::endl;
		}
	} while (!isValidMove);

	return move;
};

// Rows: Numbers (1 to 8) (ASCII 49 to 56)
// Cols: Letters (A to H) (ASCII 65 to 72)
Move
Player::strToMove(std::string start, std::string end) {
	// Set the move row and column
	Move move;
	move.startRow = (int)(start.at(1) - '1');
	move.startCol = (int)(start.at(0) - 'A');
	move.endRow = (int)(end.at(1) - '1');
	move.endCol = (int)(end.at(0) - 'A');

	// Adjust for lowercase letters
	if (move.startCol > 7) {
		move.startCol -= 32;
	}
	if (move.endCol > 7) {
		move.endCol -= 32;
	}

	return move;
}

#endif
