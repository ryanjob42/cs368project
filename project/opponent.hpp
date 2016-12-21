#ifndef OPPONENT
#define OPPONENT

#include "defs.hpp"
#include "gameState.hpp"

#include <algorithm>
#include <vector>

class Opponent {
private:
	int maxDepth;
	int maxAction(GameState &state, int currDepth, int alpha, int beta, int hRow, int hCol);
	int minAction(GameState &state, int currDepth, int alpha, int beta, int hRow, int hCol);
	int stateEval(GameState state);
public:
	Opponent(int difficulty);
	Move getMove(GameState state, Move prevMove);
};

Opponent::Opponent(int difficulty) {
	maxDepth = 3 * difficulty;
}

Move
Opponent::getMove(GameState state, Move prevMove) {
	// Initalize alpha, beta, and value to arbitrarily large values
	int alpha = -10000;
	int beta = 10000;
	int value = -10000;

	int currDepth = 1;

	// Get a vector of the possible moves and assign an arbitrarily low value to them
	std::vector<Move> moves;
	if (prevMove.endRow == -1) {
		state.getValidMoves(OPPONENTTEAM, moves);
	} else {
		state.getHopperValidMoves(OPPONENTTEAM, prevMove.endRow, prevMove.endCol, moves);
	}

	// Actually evaluate the SBE values of each of the moves
	for (int i = 0; i < moves.size(); ++i) {
		moves[i].value = -10000;	// Initalize to arbitrarily low value
		GameState newState(state);
		int movesAgain = newState.applyMove(moves[i]);
		if (movesAgain) {
			int hRow = moves[i].endRow;
			int hCol = moves[i].endCol;
			value = std::max(value, maxAction(newState, currDepth, alpha, beta, hRow, hCol));
		} else {
			value = std::max(value, minAction(newState, currDepth, alpha, beta, -1, -1));
		}
	}

	Move bestMove = moves[0];
	for (int i = 1; i < moves.size(); ++i) {
		if (moves[i].value > bestMove.value) {
			bestMove = moves[i];
		}
	}

	return bestMove;
}

int Opponent::maxAction(GameState &state, int currDepth, int alpha, int beta, int hRow, int hCol) {
	if(currDepth >= maxDepth || state.getWinner() != NULLTEAM) {
		return stateEval(state);
	}

	int value = -10000;
	++currDepth;

	// Make a vector of all the possible moves
	std::vector<Move> moves;
	if (hRow == -1) {
		state.getValidMoves(OPPONENTTEAM, moves);
	} else {
		state.getHopperValidMoves(OPPONENTTEAM, hRow, hCol, moves);
	}

	for (int i = 0; i < moves.size(); ++i) {
		GameState newState(state);
		int movesAgain = newState.applyMove(moves[i]);

		if (movesAgain) {
			int hRow = moves[i].endRow;
			int hCol = moves[i].endCol;
			value = std::max(value, maxAction(newState, currDepth, alpha, beta, hRow, hCol));
		} else {
			value = std::max(value, minAction(newState, currDepth, alpha, beta, -1, -1));
		}

		if (value >= beta) {
			return value;
		}

		alpha = std::max(alpha, value);
	}

	return value;
}

int Opponent::minAction(GameState &state, int currDepth, int alpha, int beta, int hRow, int hCol) {
	if (currDepth >= maxDepth || state.getWinner() != NULLTEAM) {
		return stateEval(state);
	}

	int value = 10000;
	++currDepth;

	// Make a vector of all the possible moves
	std::vector<Move> moves;
	if (hRow == -1) {
		state.getValidMoves(PLAYERTEAM, moves);
	} else {
		state.getHopperValidMoves(PLAYERTEAM, hRow, hCol, moves);
	}

   for (int i = 0; i < moves.size(); ++i) {
		GameState newState(state);
		int movesAgain = newState.applyMove(moves[i]);

		if (movesAgain) {
			int hRow = moves[i].endRow;
			int hCol = moves[i].endCol;
			value = std::min(value, minAction(newState, currDepth, alpha, beta, hRow, hCol));
		} else {
			value = std::min(value, maxAction(newState, currDepth, alpha, beta, -1, -1));
		}

		if (value <= alpha) {
			return value;
		}

		beta = std::min(beta, value);
	}

	return value;
}

int
Opponent::stateEval(GameState state) {
	if (state.getWinner() == OPPONENTTEAM) {
		return 100;	// Arbitrarily high number to bias computer towards winning
	}

	if (state.getWinner() == PLAYERTEAM) {
		return -100; // Arbitrarily low number to bias computer towards preventing player victory
	}

	// Get the total of the AI's pieces minus the total of the Player's pieces
	int value = 0;
	for (int r = 0; r < 8; ++r) {
		for (int c = 0; c < 8; ++c) {
			if (state.board[r][c].team == OPPONENTTEAM) {
				++value;
			} else if (state.board[r][c].team == PLAYERTEAM) {
				--value;
			}
		}
	}

	return value;
}

#endif

