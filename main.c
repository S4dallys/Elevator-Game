#include "main.h"

#define DIALOGUE_PATH "dialogue.txt"

// event flags (be careful to not reuse!)
int r1_1_1 = 0;










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

        // evaluating move
        next_coord = getNextCoordinate(PLAYER.dim.coord, key, &PLAYER.dir);
        PLAYER.dim.coord = evaluateMove(PLAYER.dim.coord, next_coord, &CUR_ROOM, R_ARRAY, &nRULES, &PLAYER);

        // interact
        int eventNo = 0;
        int ruleNo;
        if (key == INTERACT)
        {
            ruleNo = getRuleByCoord(R_ARRAY, nRULES, frontCoord(PLAYER));

            if (ruleNo == -1)
            {} // do nothing
            else
            {
                eventNo = R_ARRAY[ruleNo].eventid;
            }

            if (eventNo != 0)
            {
                DIALOGUES[0] = eventNo;
                nDIALOGUES = 1;
            }
        }

        


        ////////////////////////////////////////////////////////

        // check events (based on coord)
        switch (CUR_ROOM.roomNo)
        {
        
        case ROOM1_1:

        // door 1
        if (compareCoords(PLAYER.dim.coord, createCoords(0, 29, 3, 1), 3))
        {
            CUR_ROOM = initRoom(ROOM1_2);
            initRules(CUR_ROOM, R_ARRAY, &nRULES);
            PLAYER.dim.coord = (COORD) {19, 30};
        }

        // event 1
        if (compareCoords(PLAYER.dim.coord, createCoords(1, 1, 1, 1), 3) && r1_1_1 == 0)
        {
                createDialogues(2, 3, DIALOGUES, &nDIALOGUES);
                r1_1_1 = 1;
        }

        break;



        case ROOM1_2:

        // key
        if (compareCoords(PLAYER.dim.coord, (COORDARRAY) {{2, 22}}, 1))
        {
            setRuleColType(&R_ARRAY[1], 6);
            setRuleColor(&R_ARRAY[1], reset);
            setRuleEventId(&R_ARRAY[1], 0);
            PLAYER.hasKey = 1;
        }

        // door 1
        if (compareCoords(PLAYER.dim.coord, createCoords(20, 29, 3, 1), 3))
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