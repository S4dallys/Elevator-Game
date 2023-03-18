// includes
#include <string.h>
#include <stdio.h>
#include "file.h"
#include "rules.h"

// room ids
#define ROOM1_1 0
#define ROOM1_2 1

typedef STRING_10 TXTFILE;


typedef struct ROOM
{
    TXTFILE f_path;
    TXTFILE f_rule;
    DIM dim;
} ROOM, ELEVATOR_ROOM, SECRET_ROOM;

// func prototypes
ROOM initRoom(int id);
