#include "room.h"

#define ROOM1_1 0
#define ROOM1_2 1

ROOM createRoom(ROOM * R,
                TXTFILE f_path,
                TXTFILE f_rule,
                int f_default,
                DIM dim,
                COORD default_pos
                )
{
    strcpy(R->f_path, f_path);
    strcpy(R->f_rule, f_rule);
    R->f_default = f_default;
    R->dim = dim;
    R->default_pos = default_pos;
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
                createDim(10, 40, 50, 50), 
                (COORD) {2, 2}
            );
            break;
        
        case ROOM1_2:
            createRoom(&room,
                "./maps/1-2.txt", "./maps/1-2r.txt", ROOM1_1,
                createDim(10, 40, 50, 50),
                (COORD) {2, 2}
            );
            break;
    }


    return room;
}