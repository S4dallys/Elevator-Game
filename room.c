#include <string.h>
#include "room.h"

/*
@param [file] relative path of file
@param [floor] floor number
@param [roomNo] room number
@param [dim] dimensions of room
@return returns ROOM class
*/
ROOM createRoom(TXTFILE id, int floor, int roomNo, DIM dim)
{
    ROOM room = {0};

    room.id = id;
    room.floor = floor;
    room.roomNo = roomNo;
    room.dim = dim;

    return room;
}