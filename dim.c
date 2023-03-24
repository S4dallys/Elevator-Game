#include "dim.h"

int compareCoords (COORD first, COORDARRAY second, int nSecond)
{
    for (int i = 0; i < nSecond; i++)
    {
        if (first.row == second[i].row
                && first.col == second[i].col)
        {
            return 1;
        }
    }
    return 0;
}

/*
@param [r] row number
@param [c] col number
@param [w] object width
@param [h] object height
@return dim class instance
*/
DIM createDim(int r, int c, int w, int h) 
{
    DIM dim = {(COORD) {r, c}, (SIZE) {w, h}};

    return dim;
}

/*
@param [currentCoord] the current coord BEFORE keypress
@param [key] the keypress 
@param [*direction] PLAYER.direction pointer
@return returns COORD struct containing the coord AFTER keypress 
and returns {-1, -1} if [key] is invalid
*/ 
COORD getNextCoordinate(COORD currentCoord, KEY key, int * x_dir, int * y_dir)
{
    COORD nextCoord = currentCoord;

    switch (key)
    {
        case W_KEY:
            nextCoord.row = currentCoord.row - ROW_SIZE;
            nextCoord.col = currentCoord.col;
            *y_dir = TOP;
            break;
        case A_KEY:
            nextCoord.row = currentCoord.row;
            nextCoord.col = currentCoord.col - COL_SIZE;
            *x_dir = LEFT;
            break;
        case S_KEY:
            nextCoord.row = currentCoord.row + ROW_SIZE;
            nextCoord.col = currentCoord.col;
            *y_dir = BOTTOM;
            break;
        case D_KEY:
            nextCoord.row = currentCoord.row;
            nextCoord.col = currentCoord.col + COL_SIZE;
            *x_dir = RIGHT;
            break;

        case W_KEY_SHF:
            nextCoord.row = currentCoord.row - ROW_SHF_SIZE;
            nextCoord.col = currentCoord.col;
            *y_dir = TOP;
            break;
        case A_KEY_SHF:
            nextCoord.row = currentCoord.row;
            nextCoord.col = currentCoord.col - COL_SHF_SIZE;
            *x_dir = LEFT;
            break;
        case S_KEY_SHF:
            nextCoord.row = currentCoord.row + ROW_SHF_SIZE;
            nextCoord.col = currentCoord.col;
            *y_dir = BOTTOM;
            break;
        case D_KEY_SHF:
            nextCoord.row = currentCoord.row;
            nextCoord.col = currentCoord.col + COL_SHF_SIZE;
            *x_dir = RIGHT;
            break;

        default:
            nextCoord = currentCoord;
    }

    return nextCoord;
}