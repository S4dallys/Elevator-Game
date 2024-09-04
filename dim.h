#include "keypress.h"

#define TOP 0
#define LEFT 1
#define BOTTOM 2
#define RIGHT 3

#define ROW_SHF_SIZE 3
#define COL_SHF_SIZE 6

#define ROW_SIZE 1
#define COL_SIZE 1

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

typedef COORD COORDARRAY[50];

COORD getNextCoordinate(COORD currentCoord, KEY key, int *dir);
DIM createDim(int r, int c, int x, int y);
int compareCoords (COORD first, COORDARRAY second, int nSecond);