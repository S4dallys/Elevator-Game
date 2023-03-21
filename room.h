// includes
#include <string.h>
#include <stdio.h>
#include "player.h"
#include "E_string.h"


// room ids
#define ROOM1_1 0
#define ROOM1_2 1

typedef STRING_15 TXTFILE;


typedef struct ROOM
{
    TXTFILE f_path;
    TXTFILE f_rule;
    int f_default;
    DIM dim;
    COORD default_pos;
} ROOM, ELEVATOR_ROOM, SECRET_ROOM;

ROOM initRoom(int id);