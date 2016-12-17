#ifndef OPPONENT
#define OPPONENT
#define NULLMOVEVAL -696969

#include "defs.hpp"
#include "gameState.hpp"

#include <algorithm>
#include <vector>

class Opponent {
private:
	int thinkTime;
	GamePiece nullPiece;
	Move moveHelper(GameState state, int maxDepth);
	int maxAction(GameState &state, GamePiece &hopper, int currDepth, int maxDepth, int alpha, int beta);
	int minAction(GameState &state, GamePiece &hopper, int currDepht, int maxDepth, int alpha, int beta);
	int stateEval(GameState state);
public:
	Move move;
	Opponent(int difficulty);
	void getMove(GameState state);
};

Opponent::Opponent(int difficulty) {
	thinkTime = 4 * difficulty; // The AI arbitrarily gets 4 seconds per difficulty level to think
	move.value = 0;
	nullPiece.team = -1;
}

void Opponent::getMove(GameState state) {
	// Set the timer to limit how long the AI can think for
	// TODO

	for (int i = 1; TRUE; ++i) {
		Move bestMove = moveHelper(state, i);
		state.applyMove(bestMove);
		move = bestMove;
	}
}

Move Opponent::moveHelper(GameState state, int maxDepth) {
	// Initalize alpha, beta, and value to arbitrarily large values
	int alpha = -10000;
	int beta = 10000;
	int value = -10000;

	int currDepth = 1;

	// Get a vector of the possible moves and their boardEval values
	std::vector<Move> moves;
	// TODO: Add all valid moves to the map with a default value of -10000 (arbitrary)

	for (int i = 0; i < moves.size(); ++i) {
		GameState newState(state);
		int movesAgain = newState.applyMove(moves[i]);
		if (movesAgain) {
			GamePiece hopper;
			hopper = state.boardState[moves[i].end.row][moves[i].end.col];
			value = std::max(value, maxAction(newState, hopper, currDepth, maxDepth, alpha, beta));
		} else {
			value = std::max(value, minAction(newState, nullPiece, currDepth, maxDepth, alpha, beta));
		}
	}
}

int Opponent::maxAction(GameState &state, GamePiece &hopper, int currDepth, int maxDepth, int alpha, int beta) {
	// TODO: Make state.getWinner() == -1 better
	if(currDepth >= maxDepth && state.getWinner() == -1) {
		return stateEval(state);
	}

	int value = -10000;
	++currDepth;

	// Make a vector of all the possible moves
	std::vector<Move> moves;
	// TODO: Get all possible moves. If hopper.team != -1, hopper can be the only starting position

	for (int i = 0; i < moves.size(); ++i) {
		GameState newState(state);
		int movesAgain = newState.applyMove(moves[i]);
		if (movesAgain) {
			GamePiece hopper;
                        hopper = state.boardState[moves[i].end.row][moves[i].end.col];
			value = std::max(value, maxAction(newState, hopper, currDepth, maxDepth, alpha, beta));
		} else {
			value = std::max(value, minAction(newState, nullPiece, currDepth, maxDepth, alpha, beta));
		}

		if (value >= beta) {
			return value;
		}

		alpha = std::max(alpha, value);
	}

	return value;
}

int Opponent::minAction(GameState &state, GamePiece &hopper, int currDepth, int maxDepth, int alpha, int beta) {
	// TODO: make state.getWinner() == -1 better
	if (currDepth >= maxDepth && state.getWinner() == -1) {
		return stateEval(state);
	}

	int value = 10000;
	++currDepth;

        // Make a vector of all the possible moves
        std::vector<Move> moves;
        // TODO: Get all possible moves. If hopper.team != -1, hopper can be the only starting position

        for (int i = 0; i < moves.size(); ++i) {
                GameState newState(state);
                int movesAgain = newState.applyMove(moves[i]);
                if (movesAgain) {
                        GamePiece hopper;
                        hopper = state.boardState[moves[i].end.row][moves[i].end.col];
                        value = std::min(value, minAction(newState, hopper, currDepth, maxDepth, alpha, beta));
                } else {
                        value = std::min(value, maxAction(newState, nullPiece, currDepth, maxDepth, alpha, beta));
                }

                if (value <= alpha) {
                        return value;
                }

                beta = std::min(beta, value);
        }

        return value;
}

int Opponent::stateEval(GameState state) {
	if (state.getWinner() == OPPONENTTEAM) {
		return 100;	// Arbitrarily high number to bias computer towards winning
	}

	int value = state.opponentPieces - state.playerPieces;

	// Possibly add in bias towards king pieces
	// TODO

	return value;
}

#endif

