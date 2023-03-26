// includes
#include <string.h>
#include <stdio.h>
#include "player.h"
#include "E_string.h"

typedef STRING_15 TXTFILE;

// room ids
#define ROOM1_1 0
#define ROOM1_2 1
#define ROOM1_3 2
#define ROOM1_4 3

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