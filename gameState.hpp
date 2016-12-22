#ifndef GAMESTATE
#define GAMESTATE

#include "defs.hpp"

#include <iostream>
#include <vector>

class GameState {
public:
	// Fields
	int turn;
	GamePiece board[8][8];

	// Constructors
	GameState();
	GameState(const GameState &state);

	// Methods
	int  getWinner();
	int  isValidMove(Move move, int team, int mustHop);
	void getValidMoves(int team, std::vector<Move>& validMoves);
	void getHopperValidMoves(int team, int row, int col, std::vector<Move>& validMoves);
	int  applyMove(Move move);
};

GameState::GameState() {
	turn = PLAYERTEAM;

	// Initialize all pieces to null
	for (int r = 0; r < 8; ++r) {
		for (int c = 0; c < 8; ++c) {
			board[r][c].team = NULLTEAM;
			board[r][c].isKing = 0;
		}
	}

	// Add opponent pieces
	for (int r = 0; r < 3; ++r) {
		for (int c = (r + 1) % 2; c < 8; c += 2) {
			board[r][c].team = OPPONENTTEAM;
		}
	}

	// Add player pieces
	for (int r = 5; r < 8; ++r) {
		for (int c = (r + 1) % 2; c < 8; c += 2) {
			board[r][c].team = PLAYERTEAM;
		}
	}
}

// Copy constructor
GameState::GameState(const GameState &state) {
	turn = state.turn;
	for (int r = 0; r < 8; ++r) {
		for (int c = 0; c < 8; ++c) {
			board[r][c] = state.board[r][c];
		}
	}
}

int
GameState::getWinner() {
	int playerPieces, aiPieces;

	// Count the number of pieces each player has
	for (int r = 0; r < 8; ++r) {
		for (int c = 0; c < 8; ++c) {
			if (board[r][c].team == PLAYERTEAM) {
				++playerPieces;
			} else if (board[r][c].team == OPPONENTTEAM) {
				++aiPieces;
			}
		}
	}

	// If either have no pieces left, they lose
	if (playerPieces == 0) {
		return OPPONENTTEAM;
	} else if (aiPieces == 0) {
		return PLAYERTEAM;
	}

	// Make sure the player has valid moves left
	std::vector<Move>playerMoves;
	getValidMoves(PLAYERTEAM, playerMoves);
	if (playerMoves.size() == 0) {
		return OPPONENTTEAM;
	}

	// Make sure the AI has valid moves left
	std::vector<Move>opponentMoves;
	getValidMoves(OPPONENTTEAM, opponentMoves);
	if (opponentMoves.size() == 0) {
		return PLAYERTEAM;
	}

	// There is no winner if this point has been reached
	return NULLTEAM;
}

int
GameState::isValidMove(Move move, int team, int mustHop) {
	// If any point isn't on the board, that's bad
	if (move.startRow < 0 || move.startRow > 7 ||
		 move.startCol < 0 || move.startCol > 7 ||
		 move.endRow < 0 || move.endRow > 7 ||
		 move.endCol < 0 || move.endCol > 7) {
		return 0;
	}

	// If the start point isn't owned by team, that's bad
	if (board[move.startRow][move.startCol].team != team) {
		return 0;
	}

	// If the endpoint isn't null, that's bad
	if (board[move.endRow][move.endCol].team != NULLTEAM) {
		return 0;
	}

	int rowDiff = move.endRow - move.startRow;
	int colDiff = move.endCol - move.startCol;

	// If it's not a king...
	if (!board[move.endRow][move.endCol].isKing) {
		// If it's going the wrong way, that's bad
		if (team == PLAYERTEAM && rowDiff >= 0) {
			return 0;
		} else if (team == OPPONENTTEAM && rowDiff <= 0) {
			return 0;
		}
	}

	// If the move goes one space diagonally and doesn't need to hop, it's good!
	if (rowDiff == 1 || rowDiff == -1) {
		if (mustHop) {
			return 0;
		}
		return (colDiff == 1 || colDiff == -1);
	}

	// If it's not moving 2 spaces diagonally, that's bad
	if (rowDiff != 2 && rowDiff != -2) {
		return 0;
	}
	if (colDiff != 2 && colDiff != -2) {
		return 0;
	}
	
	// If the space getting hopped isn't owned by the opponent, that's bad
	int hoppedRowNum = move.startRow + (rowDiff / 2);
	int hoppedColNum = move.startCol + (colDiff / 2);
	int notMyTeam = (team == PLAYERTEAM) ? OPPONENTTEAM : PLAYERTEAM;
	if (board[hoppedRowNum][hoppedColNum].team != notMyTeam) {
		return 0;
	}

	// If this point is reached, it's good
	return 1;
}

void
GameState::getValidMoves(int team, std::vector<Move>& validMoves) {
	// Go through all 64 spaces on the board
	for (int r = 0; r < 8; ++r) {
		for (int c = 0; c < 8; ++c) {
			if (board[r][c].team != team) continue; // If the piece's team isn't team, skip it

			// Go through all possible places it can move to and check if they're valid
			for (int dr = -2; dr <= 2; ++dr) {
				if (dr == 0) continue;
				for (int dc = -2; dc <= 2; ++dc) {
					if (dc == 0) continue;
					Move move;
					move.startRow = r;
					move.startCol = c;
					move.endRow = r + dr;
					move.endCol = c + dc;

					// If the move is valid, add it to the provided vector
					if (isValidMove(move, team, 0)) {
						validMoves.emplace_back(move);
					}
				} // End of dc for loop
			} // End of dr for loop
		} // End of c for loop
	} // End of r for loop
} // End of getValidMoves

void
GameState::getHopperValidMoves(int team, int row, int col, std::vector<Move>& validMoves) {
	for (int dr = -2; dr <= 2; ++dr) {
		if (dr != 2 && dr != -2) continue;
		for (int dc = -2; dc <= 2; ++dc) {
			if (dc != 2 && dc != -2) continue;
			Move move;
			move.startRow = row;
			move.startCol = col;
			move.endRow = row + dr;
			move.endCol = col + dc;
			if (isValidMove(move, team, 1)) {
				validMoves.emplace_back(move);
			}
		} // End of dc for loop
	} // End of dr for loop
} // End of method

int
GameState::applyMove(Move move) {
	// Move the piece
	board[move.endRow][move.endCol] = board[move.startRow][move.startCol];

	// Generate an empty GamePiece
	GamePiece empty;
	empty.team = NULLTEAM;
	empty.isKing = 0;

	// Make the starting space empty
	board[move.endRow][move.endCol] = empty; 
	int rowDiff = move.endRow - move.startRow;
	int colDiff = move.endCol - move.startCol;

	// If the moved piece moves onto either end of the board, it's definitely a king
	if (move.endRow == 0 || move.endRow == 7) {
		board[move.endRow][move.endCol].isKing = 1;
	}

	// If no piece was hopped, return 0 saying the move wasn't a jump
	// AKA the person who moved doesn't get to go again
	if (rowDiff == 1 || rowDiff == -1) {
		return 0;
	}

	// Since a piece was hopped at this point, set it to be the empty piece
	int killedRow = move.startRow + (rowDiff / 2);
	int killedCol = move.startCol + (colDiff / 2);
	board[killedRow][killedCol] = empty;

	// Return 1, saying that the person gets to go again since they hopped a piece
	return 1;
}

#endif

