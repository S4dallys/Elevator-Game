#include "keypress.h"

#define RIGHT 0
#define LEFT 1
#define TOP 0
#define BOTTOM 1

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

typedef COORD COORDARRAY[10];

COORD getNextCoordinate(COORD currentCoord, KEY key, int *x_dir, int *y_dir);
DIM createDim(int r, int c, int x, int y);
int compareCoords (COORD first, COORDARRAY second, int nSecond);