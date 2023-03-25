#include "room.h"

ROOM createRoom(ROOM * R,
                TXTFILE f_path,
                TXTFILE f_rule,
                int f_default,
                DIM dim,
                COORD default_pos,
                int roomNo
                )
{
    strcpy(R->f_path, f_path);
    strcpy(R->f_rule, f_rule);
    R->f_default = f_default;
    R->dim = dim;
    R->default_pos = default_pos;
    R->roomNo = roomNo;
}

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
            createRoom(&room,
                "./maps/1-1.txt", "./maps/1-1r.txt", ROOM1_1,
                createDim(0, 0, 60, 20), 
                (COORD) {10, 36}, ROOM1_1
            );
            break;
        
        case ROOM1_2:
            createRoom(&room,
                "./maps/1-2.txt", "./maps/1-2r.txt", ROOM1_1,
                createDim(0, 0, 50, 20),
                (COORD) {22, 30}, ROOM1_2
            );
            break;

        case ROOM1_3:
            createRoom(&room,
                "./maps/1-3.txt", "./maps/1-3r.txt", ROOM1_1,
                createDim(0, 0, 50, 20),
                (COORD) {22, 30}, ROOM1_3
            );
            break;
    }


    return room;
}