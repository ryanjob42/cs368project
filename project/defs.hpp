#ifndef GAMECOMPONENTS
#define GAMECOMPONENTS

#define NULLTEAM 0
#define PLAYERTEAM 1
#define OPPONENTTEAM 2

typedef struct {
	int startRow;
	int startCol;
	int endRow;
	int endCol;
	int value;
} Move;

typedef struct {
	int team;
	int isKing;
} GamePiece;

#endif

