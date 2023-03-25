#include "main.h"

#define DIALOGUE_PATH "dialogue.txt"


int main()
{
    ROOM CUR_ROOM = initRoom(ROOM1_1);
    PLAYER PLAYER = createPlayer((COORD) {2, 2});
    RULEARRAY R_ARRAY;
    int nRULES;

    initRules(CUR_ROOM, R_ARRAY, &nRULES);

    PLAYER.dim.coord = CUR_ROOM.default_pos;
    COORD next_coord = CUR_ROOM.default_pos;

    while(key != 'x')
    {
        // game flow

        system("cls");
        
        sprintFrame(CUR_ROOM, R_ARRAY, nRULES, PLAYER);

        printf("%d, %d", PLAYER.dim.coord.row, PLAYER.dim.coord.col); // debug mode

        key = getch();

        next_coord = getNextCoordinate(PLAYER.dim.coord, key, &PLAYER.x_dir, &PLAYER.y_dir);
        
        PLAYER.dim.coord = evaluateMove(PLAYER.dim.coord, next_coord, &CUR_ROOM, R_ARRAY, &nRULES, &PLAYER);


        // interact

        if (key == INTERACT)
        {

        }



        // check events (based on coord)
        switch (CUR_ROOM.roomNo)
        {
        
        case ROOM1_1:

        // door 1
        if (compareCoords(PLAYER.dim.coord, (COORDARRAY) {{0, 29}, {0, 30}, {0, 31}}, 3))
        {
            CUR_ROOM = initRoom(ROOM1_2);
            initRules(CUR_ROOM, R_ARRAY, &nRULES);
            PLAYER.dim.coord = (COORD) {19, 30};
        }

        break;

        case ROOM1_2:

        // key
        if (compareCoords(PLAYER.dim.coord, (COORDARRAY) {{2, 22}}, 1))
        {
            setRuleColType(&R_ARRAY[1], 6);
            setRuleColor(&R_ARRAY[1], reset);
            PLAYER.hasKey = 1;
        }

        // door 1
        if (compareCoords(PLAYER.dim.coord, (COORDARRAY) {{20, 29}, {20, 30}, {20, 31}}, 3))
        {
            CUR_ROOM = initRoom(ROOM1_1);
            initRules(CUR_ROOM, R_ARRAY, &nRULES);
            PLAYER.dim.coord = (COORD) {1, 30};
        }

        break;
















        }
    }
    
    




    





    return 0;
}