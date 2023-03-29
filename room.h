// includes
#include <string.h>
#include <stdio.h>
#include "player.h"
#include "E_string.h"

typedef STRING_20 TXTFILE;

// room ids
#define ROOM1_1 0
#define ROOM1_2 1
#define ROOM1_3 2
#define ROOM1_4 3
#define ELV1    4
#define ROOM2_1 5
#define ROOM2_2 6
#define ROOM2_3 7
#define ELV2    8
#define ROOM3_1 9
#define ROOM3_2 10
#define ROOM3_3 11
#define ROOM3_4 12
#define ELV3    13
#define ROOM4_1 14
#define ROOM4_2 15
#define ROOM4_3 16
#define ROOM4_4 17
#define ELV4    18
#define ROOM5_1 19
#define ELV5    20
#define NEW4    21
#define NEW3    22
#define NEW2    23
#define NEW1    24

typedef struct ROOM
{
    TXTFILE f_path;
    TXTFILE f_rule;
    int f_default;
    DIM dim;
    COORD default_pos;
    int roomNo;
} ROOM, ELEVATOR_ROOM, SECRET_ROOM;

ROOM initRoom(int id);