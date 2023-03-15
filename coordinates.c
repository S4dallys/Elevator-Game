#include "coordinates.h"
#include "keypress.h"

/*
@param [currentCoord] the current coord BEFORE keypress
@param [key] the keypress 
@return returns COORD struct containing the coord AFTER keypress 
and returns {-1, -1} if [key] is invalid
*/ 
COORD getNextCoordinate(COORD currentCoord, KEY key)
{
    COORD nextCoord = {-1, -1};

    switch (key)
    {
        case W_KEY:
            nextCoord.row = currentCoord.row - 1;
            nextCoord.col = currentCoord.col;
            break;
        case A_KEY:
            nextCoord.row = currentCoord.row;
            nextCoord.col = currentCoord.col - 1;
            break;
        case S_KEY:
            nextCoord.row = currentCoord.row + 1;
            nextCoord.col = currentCoord.col;
            break;
        case D_KEY:
            nextCoord.row = currentCoord.row;
            nextCoord.col = currentCoord.col + 1;
            break;
    }

    return nextCoord;
}