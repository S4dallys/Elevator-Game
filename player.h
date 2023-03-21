#include "dim.h"

// sprite types for npcs and player
#define S_PLAYER 0
#define S_ENEMY 1;
#define S_FRIEND 2;

typedef int S_TYPE;

typedef struct SPRITE 
{
    DIM dim;
    S_TYPE s_type;
    char sprite;
    int x_dir;
    int y_dir;
} PLAYER, ENEMY, FRIEND;

PLAYER createPlayer(COORD def_coord);