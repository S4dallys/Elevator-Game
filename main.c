#include "main.h"

#define DIALOGUE_PATH "dialogue.txt"

// event flags (be careful to not reuse!)
int r1_3 = 0;










int main()
{
    ROOM CUR_ROOM = initRoom(ROOM1_1);
    PLAYER PLAYER = createPlayer((COORD) {2, 2});
    RULEARRAY R_ARRAY;
    int nRULES;

    initRules(CUR_ROOM, R_ARRAY, &nRULES);

    PLAYER.dim.coord = CUR_ROOM.default_pos;
    COORD next_coord = CUR_ROOM.default_pos;

    char key = ' ';

    DIALOGUES DIALOGUES = {0};
    int nDIALOGUES = 0;

    int nextEvent = 0;

    while(key != 'p')
    { 
        //drawing frame
        int y = 0;
        do
        {
            system("cls");
            sprintFrame(CUR_ROOM, R_ARRAY, nRULES, PLAYER);
            sprintDialogueBox(DIALOGUE_PATH, DIALOGUES[y]);

            key = getch();

            if (nDIALOGUES > 0)
            {
                if (key != 'x')
                    continue;
                y++;
            }
        }
        while (y < nDIALOGUES && nDIALOGUES > 0);

        // reset dialogues
        for (int h = 0; h < nDIALOGUES; h++)
            DIALOGUES[h] = 0;
        nDIALOGUES = 0;

        // reset events
        nextEvent = 0;

        // evaluating move
        next_coord = getNextCoordinate(PLAYER.dim.coord, key, &PLAYER.dir);
        PLAYER.dim.coord = evaluateMove(PLAYER.dim.coord, next_coord, &CUR_ROOM, R_ARRAY, &nRULES, &PLAYER);

        // interact
        int dlgNo = 0;
        int eventNo = 0;
        int ruleNo;
        if (key == INTERACT)
        {
            ruleNo = getRuleByCoord(R_ARRAY, nRULES, frontCoord(PLAYER));

            if (ruleNo == -1)
            {} // do nothing
            else
            {
                dlgNo = R_ARRAY[ruleNo].dlgid;
                eventNo = R_ARRAY[ruleNo].eventid;
            }

            if (dlgNo != 0)
            {
                fillDialogues (DIALOGUES, &nDIALOGUES, dlgNo);
            }

            if (eventNo != 0)
            {
                nextEvent = eventNo;
            }
        }

        


        ////////////////////////////////////////////////////////

        // check events (based on coord)
        switch (CUR_ROOM.roomNo)
        {
        
        case ROOM1_1:

        if (compareCoords(PLAYER.dim.coord, createCoords(0, 35, 3, 1), 3))
        {
            CUR_ROOM = initRoom(ROOM1_2);
            initRules(CUR_ROOM, R_ARRAY, &nRULES);
            PLAYER.dim.coord = (COORD) {22, 30};
        }

        break;



        case ROOM1_2:

        if (compareCoords(PLAYER.dim.coord, createCoords(8, 30, 1, 1), 1))
        {
            CUR_ROOM = initRoom(ROOM1_3);
            initRules(CUR_ROOM, R_ARRAY, &nRULES);
            PLAYER.dim.coord = (COORD) {8, 30};
        }

        break;


        case ROOM1_3:

        if (compareCoords(PLAYER.dim.coord, createCoords(8, 30, 1, 1), 1) && r1_3 == 0)
        {
            createDialogues(7, 2, DIALOGUES, &nDIALOGUES);
            r1_3 = 1;
        }

        if (compareCoords(PLAYER.dim.coord, createCoords(0, 29, 3, 1), 3))
        {
            CUR_ROOM = initRoom(ROOM2_1);
            initRules(CUR_ROOM, R_ARRAY, &nRULES);
            PLAYER.dim.coord = (COORD) {15, 22};
        }


        break;

        case ROOM2_1:

        if (compareCoords(PLAYER.dim.coord, createCoords(9, 45, 1, 2), 2))
        {
            CUR_ROOM = initRoom(ROOM2_2);
            initRules(CUR_ROOM, R_ARRAY, &nRULES);
            PLAYER.dim.coord = (COORD) {10, 3};
        }

        break;

        case ROOM2_2:

        if (compareCoords(PLAYER.dim.coord, createCoords(9, 87, 1, 2), 2))
        {
            CUR_ROOM = initRoom(ROOM2_3);
            initRules(CUR_ROOM, R_ARRAY, &nRULES);
            PLAYER.dim.coord = (COORD) {15, 22};
        }

        break;

        }
    }
    
    




    





    return 0;
}