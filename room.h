// includes
#include "file.h"
#include "rules.h"
#include "global.h"

// room ids
#define ROOM1_1 0
#define ROOM1_2 1

// structs and aliases
typedef int TXTFILE;

typedef struct ROOM
{
    TXTFILE id;
    int floor;
    int roomNo;
    DIM dim;
} ROOM, ELEVATOR_ROOM, SECRET_ROOM;

// func prototypes
ROOM createRoom(TXTFILE id, TXTFILE objrules, int floor, int roomNo, DIM dim);