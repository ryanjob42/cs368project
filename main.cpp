#include "gameState.hpp"
#include "opponent.hpp"
#include "player.hpp"
#include "main.hpp"

#include <iostream>
#include <string>

int
main() {
	std::system("clear"); // Clear the console
	int difficulty = getDifficulty();
	std::system("clear"); // Clear the console
	Opponent computer (difficulty);
	Player player;
	GameState board;

	while (board.getWinner() == NULLTEAM) {
		//Display the board
		if (board.turn == PLAYERTEAM) {
			// Player's move
			int goesAgain = 0;
			Move move;
			move.endRow = -1; // Indicate the player didn't jump a piece
			do {
				printBoard(board);
				move = player.getMove(board, move);
				goesAgain = applyMove(move, board);
				std::system("clear"); // Clear the console
			} while (goesAgain);
			board.turn = OPPONENTTEAM;
		} else {
			// Opponent's move
			int goesAgain = 0;
			Move move;
			move.endRow = -1; // Indicate the AI didn't jump a piece
			do {
				move = computer.getMove(board, move);
				goesAgain = applyMove(move, board);
				displayMove(move);
			} while (goesAgain);
			board.turn = PLAYERTEAM;
		}
	}

	if (board.getWinner() == PLAYERTEAM)
		std::cout << "You did it! You beat the computer! Yay~" << std::endl;
	if (board.getWinner() == OPPONENTTEAM)
		std::cout << "Aww, you lost. Better luck next time!" << std::endl;
	return 0;
}

int
getDifficulty() {
	int difficulty = -1;
	std::string input;

	std::cout << "///////////////////////////////////////////////" << std::endl;
	std::cout << "//         Welcome to text checkers!         //" << std::endl;
	std::cout << "//                                           //" << std::endl;
	std::cout << "//  What difficulty would you like to play?  //" << std::endl;
	std::cout << "//     1) Easy Peasy      2) Medium          //" << std::endl;
	std::cout << "//     3) Really Hard     4) IMPOSSIBLE!     //" << std::endl;
	std::cout << "//         (Enter the number please)         //" << std::endl;
	std::cout << "///////////////////////////////////////////////" << std::endl;

	while (difficulty == -1) {
		std::cout << "Difficulty: ";
		std::cin >> input;
		difficulty = ((int)input.at(0)) - 48; // 48 is ASCII value for 0
		if (difficulty < 1 || difficulty > 4) {
			std::cin.clear();
			std::cin.ignore(2000000, '\n'); // If the user enters more than this, they deserve to break everything
			std::cout << "That is not a difficulty. Please enter a difficulty (1 to 4)" << std::endl;
			difficulty = -1;
		}
	}
}

void
displayMove(Move move) {
	std::cout << "The computer moved from ";
	std::cout << (char)(move.startCol + 65);
	std::cout << (char)(move.startRow + 49) << " to ";
	std::cout << (char)(move.endCol + 65);
	std::cout << (char)(move.endRow + 49) << std::endl;
}

void
printBoard(GameState board) {
	//Player pieces are designated with an o, opponent pieces with an x, null pieces are a space
	//A capital letter will designate that piece as a king piece

	std::cout << "   A   B   C   D   E   F   G   H  " << std::endl;
	for (int r = 0; r < 8; ++r) {
		std::cout << "  --- --- --- --- --- --- --- --- " << std::endl;
		std::cout << r + 1;
		for (int c = 0; c < 8; ++c) {
			std::cout << "| ";
			GamePiece piece = board.board[r][c];

			char pieceChar;
			if (piece.team == OPPONENTTEAM) {
				pieceChar = (piece.isKing) ? 'X' : 'x';
			} else if (piece.team == PLAYERTEAM) {
				pieceChar = (piece.isKing) ? 'O' : 'o';
			} else {
				pieceChar = ' ';
			}
			std::cout << pieceChar << " ";
		}
		std::cout << "|" << std::endl;
	}
	std::cout << "  --- --- --- --- --- --- --- --- " << std::endl;
	std::cout << "   A   B   C   D   E   F   G   H  " << std::endl;
}

int
applyMove(Move move, GameState& state) {
	// Move the piece
	int oldTeam = state.board[move.startRow][move.startCol].team;
	int oldIsKing = state.board[move.startRow][move.startCol].isKing; 

	state.board[move.endRow][move.endCol].team = oldTeam;
	state.board[move.endRow][move.endCol].isKing = oldIsKing;

	state.board[move.startRow][move.startCol].team = NULLTEAM;
	state.board[move.startRow][move.startCol].isKing = 0;

	// Make the starting space empty
	int rowDiff = move.endRow - move.startRow;
	int colDiff = move.endCol - move.startCol;

	// If the moved piece moves onto either end of the board, it's definitely a king
	if (move.endRow == 0 || move.endRow == 7) {
		state.board[move.endRow][move.endCol].isKing = 1;
	}

	// If no piece was hopped, return 0 saying the move wasn't a jump
	// AKA the person who moved doesn't get to go again
	if (rowDiff == 1 || rowDiff == -1) {
		return 0;
	}

	// Since a piece was hopped at this point, set it to be the empty piece
	int killedRow = move.startRow + (rowDiff / 2);
	int killedCol = move.startCol + (colDiff / 2);

	state.board[killedRow][killedCol].team = NULLTEAM;
	state.board[killedRow][killedCol].isKing = 0;

	// Return 1, saying that the person gets to go again since they hopped a piece
	std::vector<Move> validMoves;
	state.getHopperValidMoves(oldTeam, move.endRow, move.endCol, validMoves);
	return validMoves.size() > 0;
} 
