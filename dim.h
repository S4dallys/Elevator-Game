#include "keypress.h"

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

COORD getNextCoordinate(COORD currentCoord, KEY key, int *direction);
DIM createDim(int r, int c, int x, int y);