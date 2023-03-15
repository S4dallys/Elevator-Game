#include "keypress.h"

typedef struct COORD
{
    int row;
    int col;
} COORD;

COORD getNextCoordinate(COORD currentCoord, KEY key);