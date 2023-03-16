// includes
#include "file.h"
#include "object.h"
#include "global.h"

// macros

// structs and aliases
typedef struct ROOM
{
    STRING_10 file;
    int floor;
    int roomNo;
    DIM dim;
} ROOM, ELEVATOR_ROOM, SECRET_ROOM;

// func prototypes
ROOM createRoom(STRING_10 file, int floor, int roomNo, OBJECT dim);