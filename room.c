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
        
        case ELV2:
            createRoom(&room,
                "./maps/elv2.txt", "./maps/elv2r.txt", ROOM2_1,
                createDim(0, 0, 100, 100),
                (COORD) {6, 21}, ELV2
            );
            break;

        case ROOM3_1:
            createRoom(&room,
                "./maps/3-1.txt", "./maps/3-1r.txt", ROOM3_1,
                createDim(0, 0, 100, 100),
                (COORD) {13, 31}, ROOM3_1
            );
            break;

        case ROOM3_2:
            createRoom(&room,
                "./maps/3-2.txt", "./maps/3-2r.txt", ROOM3_1,
                createDim(0, 0, 100, 100),
                (COORD) {13, 31}, ROOM3_2
            );
            break;

        case ROOM3_3:
            createRoom(&room,
                "./maps/3-3.txt", "./maps/3-3r.txt", ROOM3_1,
                createDim(0, 0, 100, 100),
                (COORD) {13, 31}, ROOM3_3
            );
            break;

        case ROOM3_4:
            createRoom(&room,
                "./maps/3-4.txt", "./maps/3-4r.txt", ROOM3_1,
                createDim(0, 0, 100, 100),
                (COORD) {13, 31}, ROOM3_4
            );
            break;

        case ELV3:
            createRoom(&room,
                "./maps/elv3.txt", "./maps/elv3r.txt", ROOM3_1,
                createDim(0, 0, 100, 100),
                (COORD) {6, 21}, ELV3
            );
            break;

        case ROOM4_1:
            createRoom(&room,
                "./maps/4-1.txt", "./maps/4-1r.txt", ROOM4_1,
                createDim(0, 0, 100, 100),
                (COORD) {6, 21}, ROOM4_1
            );
            break;

        case ROOM4_2:
            createRoom(&room,
                "./maps/4-2.txt", "./maps/4-2r.txt", ROOM4_1,
                createDim(0, 0, 100, 100),
                (COORD) {6, 21}, ROOM4_2
            );
            break;
        
        case ROOM4_3:
            createRoom(&room,
                "./maps/4-3.txt", "./maps/4-3r.txt", ROOM4_1,
                createDim(0, 0, 100, 100),
                (COORD) {6, 21}, ROOM4_3
            );
            break;

        case ROOM4_4:
            createRoom(&room,
                "./maps/4-4.txt", "./maps/4-4r.txt", ROOM4_1,
                createDim(0, 0, 100, 100),
                (COORD) {6, 21}, ROOM4_4
            );
            break;

        case ELV4:
            createRoom(&room,
                "./maps/elv4.txt", "./maps/elv4r.txt", ROOM4_1,
                createDim(0, 0, 100, 100),
                (COORD) {6, 21}, ELV4
            );
            break;

        case ROOM5_1:
            createRoom(&room,
                "./maps/5-1.txt", "./maps/5-1r.txt", ROOM5_1,
                createDim(0, 0, 100, 100),
                (COORD) {15, 40}, ROOM5_1
            );
            break;

        case ELV5:
            createRoom(&room,
                "./maps/elv5.txt", "./maps/elvr.txt", ROOM5_1,
                createDim(0, 0, 100, 100),
                (COORD) {6, 21}, ELV5
            );
            break;

        case NEW4:
            createRoom(&room,
                "./maps/new4.txt", "./maps/new4r.txt", ROOM5_1,
                createDim(0, 0, 100, 100),
                (COORD) {5, 35}, NEW4
            );
            break;

        case NEW3:
            createRoom(&room,
                "./maps/new3.txt", "./maps/new3r.txt", ROOM5_1,
                createDim(0, 0, 100, 100),
                (COORD) {6, 21}, NEW3
            );
            break;

        case NEW2:
            createRoom(&room,
                "./maps/new2.txt", "./maps/new2r.txt", ROOM5_1,
                createDim(0, 0, 100, 100),
                (COORD) {6, 21}, NEW2
            );
            break;

        case NEW1:
            createRoom(&room,
                "./maps/new1.txt", "./maps/new1r.txt", ROOM5_1,
                createDim(0, 0, 100, 100),
                (COORD) {6, 21}, NEW1
            );
            break;
            
    }


    return room;
}