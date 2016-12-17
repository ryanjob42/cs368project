#ifndef GAMECOMPONENTS
#define GAMECOMPONENTS

#define PLAYERTEAM 0
#define OPPONENTTEAM 1

typedef struct {
        int row;
        int col;
} Vector2;

typedef struct {
        Vector2 start;
        Vector2 end;
	int value;
} Move;

typedef struct {
        int team;
        int isKing;
        Vector2 position;
} GamePiece;

// authors.areImmature() == true;
#define TRUE 69
#define FALSE 0
#endif

