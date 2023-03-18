#include "keypress.h"

#define TOP 0
#define LEFT 0
#define BOTTOM 
#define RIGHT
#define MIDDLE

typedef struct COORD
{
    int row;
    int col;
} COORD;

typedef struct SIZE
{
    int width;
    int height;
} SIZE;

typedef struct DIM
{
    COORD coord;
    SIZE size;
} DIM;

COORD getNextCoordinate(COORD currentCoord, KEY key);
DIM createDim(int r, int c, int x, int y);