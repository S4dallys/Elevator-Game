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

COORD getNextCoordinate(COORD currentCoord, KEY key);