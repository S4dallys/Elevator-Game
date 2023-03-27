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
                (COORD) {8, 30}, ROOM1_3
            );
            break;

        case ROOM1_4:
            createRoom(&room,
                "./maps/1-4.txt", "./maps/1-4r.txt", ROOM1_1,
                createDim(0, 0, 50, 20),
                (COORD) {22, 30}, ROOM1_4
            );
            break;

        case ELV1:
            createRoom(&room,
                "./maps/elv1.txt", "./maps/elv1r.txt", ROOM1_1,
                createDim(0, 0, 50, 20),
                (COORD) {6, 21}, ELV1
            );
            break;

        case ROOM2_1:
            createRoom(&room,
                "./maps/2-1.txt", "./maps/2-1r.txt", ROOM2_1,
                createDim(0, 0, 50, 20),
                (COORD) {15, 22}, ROOM2_1
            );
            break;

        case ROOM2_2:
            createRoom(&room,
                "./maps/2-2.txt", "./maps/2-2r.txt", ROOM2_1,
                createDim(0, 0, 100, 100),
                (COORD) {10, 3}, ROOM2_2
            );
            break;

        case ROOM2_3:
            createRoom(&room,
                "./maps/2-3.txt", "./maps/2-3r.txt", ROOM2_1,
                createDim(0, 0, 100, 100),
                (COORD) {17, 3}, ROOM2_3
            );
            break;

    }


    return room;
}