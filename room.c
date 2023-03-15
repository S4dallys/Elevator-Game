#include <string.h>
#include "room.h"

/*
@param [file] relative path of file
@param [floor] floor number
@param [roomNo] room number
@param [dim] dimensions of room
@return returns ROOM class
*/
ROOM createRoom(STRING_10 file, int floor, int roomNo, OBJECT dim)
{
    ROOM room = {0};

    strcpy(room.file, file);
    room.floor = floor;
    room.roomNo = roomNo;
    room.dim = dim;

    return room;
}