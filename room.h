// includes
#include <string.h>
#include <stdio.h>
#include "dim.h"
#include "E_string.h"


// room ids
#define ROOM1_1 0
#define ROOM1_2 1

typedef STRING_15 TXTFILE;


typedef struct ROOM
{
    TXTFILE f_path;
    TXTFILE f_rule;
    DIM dim;
    DIM ePoints[8];
    int ePoints_count;
} ROOM, ELEVATOR_ROOM, SECRET_ROOM;

// func prototypes
ROOM initRoom(int id);