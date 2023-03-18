#include "room.h"

#define ROOM1_1 0
#define ROOM1_2 1

/*
@param [id] room code, see maros:
@return returns ROOM class
*/
ROOM initRoom(int id)
{
    ROOM room = {0};

    switch (id)
    {
        case ROOM1_1:
            strcpy(room.f_path, "1-1.txt");
            strcpy(room.f_rule, "1-1r.txt");
            room.dim = createDim(TOP, LEFT, 50, 50);
            break;
        case ROOM1_2:
            strcpy(room.f_path, "1-2.txt");
            strcpy(room.f_path, "1-2.txt");
            room.dim = createDim(10, 40, 50, 50);
            break;
    }


    return room;
}