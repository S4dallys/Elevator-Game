#include "main.h"

#define EVENTS_PATH "EVENTS.txt"
#define DIALOGUE_PATH "dialogue.txt"


int main()
{
    ROOM CUR_ROOM = initRoom(ROOM1_2);
    PLAYER PLAYER = createPlayer((COORD) {2, 2});
    RULEARRAY R_ARRAY;
    int nRULES;

    initRules(CUR_ROOM, R_ARRAY, &nRULES);

    PLAYER.dim.coord = CUR_ROOM.default_pos;
    COORD next_coord = CUR_ROOM.default_pos;

    char key = '1';
    int i = 0;
    RULE action;

    while(key != 'x')
    {
        system("cls");
        
        if (key != INTERACT)
            sprintFrame(CUR_ROOM, R_ARRAY, nRULES, next_coord);
        printf("%d, %d", PLAYER.dim.coord.row, PLAYER.dim.coord.col);
        key = getch();

        next_coord = getNextCoordinate(PLAYER.dim.coord, key, &PLAYER.x_dir, &PLAYER.y_dir);
        
        PLAYER.dim.coord = next_coord;
        // PLAYER.dim.coord = evaluateMove(&CUR_ROOM, PLAYER.dim.coord, next_coord, R_ARRAY, &nRULES, key);
    }
    
    




    





    return 0;
}