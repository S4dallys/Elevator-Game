#include "room.h"

#define ROOM1_1 0
#define ROOM1_2 1

ROOM createRoom(ROOM * R,
                TXTFILE f_path,
                TXTFILE f_rule,
                DIM dim,
                int ePoints_count)
{
    strcpy(R->f_path, f_path);
    strcpy(R->f_rule, f_rule);
    R->dim = dim;
    R->ePoints_count = ePoints_count;
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
                "1-1.txt", "1-1r.txt",
                createDim(10, 40, 50, 50), 3
            );
            room.ePoints[0] = createDim(1, 1, 1, 1);
            room.ePoints[1] = createDim(1, 1, 1, 1);
            room.ePoints[2] = createDim(1, 1, 1, 1);
            break;
        
        case ROOM1_2:
            createRoom(&room,
                "1-2.txt", "1-1r.txt",
                createDim(10, 40, 50, 50), 3
            );
            room.ePoints[0] = createDim(1, 1, 1, 1);
            room.ePoints[1] = createDim(1, 1, 1, 1);
            room.ePoints[2] = createDim(1, 1, 1, 1);
            break;
    }


    return room;
}