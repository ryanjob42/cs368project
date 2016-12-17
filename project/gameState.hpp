#ifndef GAMESTATE
#define GAMESTATE

#include "defs.hpp"

#include <stdio.h>

class GameState {
private:
	void setPiece(int row, int col, int team, int isKing);
public:
	GamePiece boardState[8][8];
	int turn;
	int playerPieces;
	int opponentPieces;
	GameState();
	GameState(const GameState &state);
	int getWinner();
	int isValidMove(Move move, int team);
	int applyMove(Move move);
	int becomesKing(GamePiece piece);
};

void GameState::setPiece(int row, int col, int team, int isKing) {
	boardState[row][col].team = team;
        boardState[row][col].isKing = isKing;
        boardState[row][col].position.row = row;
        boardState[row][col].position.col = col;
}

GameState::GameState() {
	// Initialize Player's pieces
	for (int row = 0; row < 3; ++row) {
		for (int col = row % 2; col < 8; col += 2) {
			setPiece(row, col, PLAYERTEAM, 0);
		}
	}
	playerPieces = 12;

	// Initialize Computer's pieces
	for (int row = 5; row < 8; ++row) {
		for (int col = row % 2; col < 8; col += 2) {
			setPiece(row, col, OPPONENTTEAM, 0);
		}
	}
	opponentPieces = 12;
}

GameState::GameState(const GameState &state) {
	for (int r = 0; r < 8; ++r) {
		for (int c = 0; c < 8; ++c) {
			boardState[r][c] = state.boardState[r][c];
		}
	}

	turn = state.turn;
        playerPieces = state.playerPieces;
        opponentPieces = state.opponentPieces;
}

int GameState::getWinner() {
	// Check if a player has no pieces left on the board
	if (playerPieces == 0) {
		return OPPONENTTEAM;
	} else if (opponentPieces == 0) {
		return PLAYERTEAM;
	}

	// Check if there are no valid moves left for either team
	// TODO

	return -1;
}

int GameState::isValidMove(Move move, int team) {
        // Make sure all move positions are on the board (between 0 and 7 inclusive)
        // TODO

        // Make sure the player is moving one of their own pieces
        // TODO

        // Make sure the destination isn't an unused tile
        // TODO

        // Make sure the destination isn't on top of another piece
        // TODO

        // Make sure non-king pieces don't go backwards
        // TODO

        // Make sure the move is either going one space or jumping an opponent (and only going 2 spaces)
        // TODO

	return 1;
}

int GameState::applyMove(Move move) {
	// Double check the move is valid
	// TODO

	// Move the piece that's to be moved
	// TODO

	// Return 0 if no piece was jumped
	// TODO

	// Remove the jumped piece
	// TODO

	return 1;
}

int becomesKing(GamePiece piece) {
	// TODO
	return 0;
}

#endif

