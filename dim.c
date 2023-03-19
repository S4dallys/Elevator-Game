#include "dim.h"

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
COORD getNextCoordinate(COORD currentCoord, KEY key, int * direction)
{
    COORD nextCoord = currentCoord;

    switch (key)
    {
        case W_KEY:
            nextCoord.row = currentCoord.row - 1;
            nextCoord.col = currentCoord.col;
            break;
        case A_KEY:
            nextCoord.row = currentCoord.row;
            nextCoord.col = currentCoord.col - 2;
            *direction = 1;
            break;
        case S_KEY:
            nextCoord.row = currentCoord.row + 1;
            nextCoord.col = currentCoord.col;
            break;
        case D_KEY:
            nextCoord.row = currentCoord.row;
            nextCoord.col = currentCoord.col + 2;
            *direction = 0;
            break;

        case W_KEY_SHF:
            nextCoord.row = currentCoord.row - 4;
            nextCoord.col = currentCoord.col;
            break;
        case A_KEY_SHF:
            nextCoord.row = currentCoord.row;
            nextCoord.col = currentCoord.col - 8;
            *direction = 1;
            break;
        case S_KEY_SHF:
            nextCoord.row = currentCoord.row + 4;
            nextCoord.col = currentCoord.col;
            break;
        case D_KEY_SHF:
            nextCoord.row = currentCoord.row;
            nextCoord.col = currentCoord.col + 8;
            *direction = 0;
            break;

        default:
            nextCoord = currentCoord;
    }

    return nextCoord;
}