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