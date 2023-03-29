#include "main.h"

#define DIALOGUE_PATH "dialogue.txt"

// event flags (be careful to not reuse!)
int r1_1a = 0;
int r1_1b = 0;
int r1_3a = 0;
int r1_3b = 0;
int r2_1a = 0;
int r2_3a = 0;
int r3_2f = 1;
int r3_2a = 0;
int r3_3a = 0; 

int main()
{
    ROOM CUR_ROOM = initRoom(ROOM2_1);
    PLAYER PLAYER = createPlayer(CUR_ROOM.default_pos);

    //DEBUG
    //
    CUR_ROOM = initRoom(ROOM3_1);
    // PLAYER.dim.coord = CUR_ROOM.default_pos;
    //

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

        // door to room1_2
        if (compareCoords(PLAYER.dim.coord, createCoords(0, 35, 3, 1), 3))
        {
            CUR_ROOM = initRoom(ROOM1_2);
            initRules(CUR_ROOM, R_ARRAY, &nRULES);
            PLAYER.dim.coord = (COORD) {5, 10};
        }

        // introduction of Mark
        if (compareCoords(PLAYER.dim.coord, createCoords(9, 25, 23, 1), 23) && r1_1a == 0)
        {
            createDialogues(100, 5, DIALOGUES, &nDIALOGUES);
            r1_1a = 1;
        }

        // see you next room!
        if (compareCoords(PLAYER.dim.coord, createCoords(5, 35, 3, 1), 3) && r1_1b == 0)
        {
            createDialogues(105, 1, DIALOGUES, &nDIALOGUES);
            r1_1b = 1;
        }

        break;



        case ROOM1_2:

        // go to room1_3
        if (compareCoords(PLAYER.dim.coord, createCoords(2, 20, 1, 1), 1))
        {
            CUR_ROOM = initRoom(ROOM1_3);
            initRules(CUR_ROOM, R_ARRAY, &nRULES);
            PLAYER.dim.coord = (COORD) {3, 1};
        }

        break;


        case ROOM1_3:

        // go to room1_4
        if (compareCoords(PLAYER.dim.coord, createCoords(6, 55, 1, 1), 1))
        {
            CUR_ROOM = initRoom(ROOM1_4);
            initRules(CUR_ROOM, R_ARRAY, &nRULES);
            PLAYER.dim.coord = (COORD) {21, 2};
            
            createDialogues(143, 5, DIALOGUES, &nDIALOGUES);
        }

        // death!!
        if (compareCoords(PLAYER.dim.coord, createCoords(3, 2, 1, 1), 1) && r1_3a == 0)
        {
            createDialogues(106, 3, DIALOGUES, &nDIALOGUES);
            r1_3a = 1;
        }

        // death part 2!!
        if (compareCoords(PLAYER.dim.coord, createCoords(4, 39, 1, 1), 1) && r1_3b == 0)
        {
            createDialogues(109, 3, DIALOGUES, &nDIALOGUES);
            r1_3b = 1;
        }

        if (compareCoords(PLAYER.dim.coord, createCoords(0, 29, 3, 1), 3))
        {
            CUR_ROOM = initRoom(ROOM2_1);
            initRules(CUR_ROOM, R_ARRAY, &nRULES);
            PLAYER.dim.coord = (COORD) {15, 22};
        }


        break;

        case ROOM1_4:

        if (eventNo == 102 && PLAYER.hasKey)
        {
            CUR_ROOM = initRoom(ELV1);
            initRules(CUR_ROOM, R_ARRAY, &nRULES);
            PLAYER.dim.coord = CUR_ROOM.default_pos;

            createDialogues(152, 5, DIALOGUES, &nDIALOGUES);
        }

        // key!!
        if (compareCoords(PLAYER.dim.coord, createCoords(16, 24, 1, 1), 1))
        {
            setRuleColType(&R_ARRAY[16], 6);
            setRuleColor(&R_ARRAY[16], reset);
            setRuleDlgId(&R_ARRAY[16], 0);
            PLAYER.hasKey = 1;
        }

        // left lever
        if (eventNo == 100)
        {
            setRuleColType(&R_ARRAY[6], 6);
        }

        // right lever
        if (eventNo == 101)
        {
            setRuleColType(&R_ARRAY[7], 6);
            setRuleColType(&R_ARRAY[2], 6);
            setRuleColType(&R_ARRAY[4], 6);
            setRuleColor(&R_ARRAY[2], reset);
            setRuleColor(&R_ARRAY[4], reset);
            setRuleDlgId(&R_ARRAY[2], 0);
            setRuleDlgId(&R_ARRAY[4], 0);
        }

        break;

        case ELV1:

        if (eventNo == 90)
        {
            CUR_ROOM = initRoom(ROOM2_1);
            initRules(CUR_ROOM, R_ARRAY, &nRULES);
            PLAYER.dim.coord = CUR_ROOM.default_pos;

            PLAYER.hasKey = 0;

            createDialogues(219, 3, DIALOGUES, &nDIALOGUES);
        }

        break;

        case ROOM2_1:

        if (compareCoords(PLAYER.dim.coord, createCoords(9, 45, 1, 2), 2))
        {
            CUR_ROOM = initRoom(ROOM2_2);
            initRules(CUR_ROOM, R_ARRAY, &nRULES);
            PLAYER.dim.coord = (COORD) {10, 3};
        }

        // forced dialogue blood
        if (compareCoords(PLAYER.dim.coord, createCoords(9, 35, 1, 2), 2) && r2_1a == 0)
        {
            createDialogues(209, 1, DIALOGUES, &nDIALOGUES);
            r2_1a = 1;
        }

        break;

        case ROOM2_2:

        // door back to room2_1
        if (compareCoords(PLAYER.dim.coord, createCoords(9, 0, 1, 2), 2))
        {
            CUR_ROOM = initRoom(ROOM2_1);
            initRules(CUR_ROOM, R_ARRAY, &nRULES);
            PLAYER.dim.coord = (COORD) {10, 41};
        }

        if (compareCoords(PLAYER.dim.coord, createCoords(9, 87, 1, 2), 2))
        {
            CUR_ROOM = initRoom(ROOM2_3);
            initRules(CUR_ROOM, R_ARRAY, &nRULES);
            PLAYER.dim.coord = (COORD) {17, 3};

            if (r2_3a == 0)
                createDialogues(210, 7, DIALOGUES, &nDIALOGUES);
            
            r2_3a = 1;
        }

        break;
        
        case ROOM2_3:
        
        // elevator to floor 3
        if (compareCoords(PLAYER.dim.coord, createCoords(17, 0, 1, 2), 2))
        {
            CUR_ROOM = initRoom(ROOM2_2);
            initRules(CUR_ROOM, R_ARRAY, &nRULES);
            PLAYER.dim.coord = (COORD) {9, 84};
        }

        break;

        case ELV2:

        if (eventNo == 200)
        {
            CUR_ROOM = initRoom(ROOM3_1);
            initRules(CUR_ROOM, R_ARRAY, &nRULES);
            PLAYER.dim.coord = CUR_ROOM.default_pos;

            createDialogues(359, 5, DIALOGUES, &nDIALOGUES);
        }
        
        case ROOM3_1:
        
        // key!!!
        if (compareCoords(PLAYER.dim.coord, createCoords(4, 27, 1, 1), 1))
        {
            setRuleColType(&R_ARRAY[3], 6);
            setRuleDlgId(&R_ARRAY[3], 0);
            setRuleColor(&R_ARRAY[3], reset);
            PLAYER.hasKey = 1;
        }

        // go to room 3_4
        if (compareCoords(PLAYER.dim.coord, createCoords(5, 57, 1, 2), 2))
        {
            CUR_ROOM = initRoom(ROOM3_4);
            initRules(CUR_ROOM, R_ARRAY, &nRULES);
            PLAYER.dim.coord = (COORD) {6, 15};
        }

        // go to room 3_3
        if (compareCoords(PLAYER.dim.coord, createCoords(3, 48, 3, 1), 3))
        {
            CUR_ROOM = initRoom(ROOM3_3);
            initRules(CUR_ROOM, R_ARRAY, &nRULES);
            PLAYER.dim.coord = (COORD) {12, 57};
        }

        // go to room 3_2
        if (compareCoords(PLAYER.dim.coord, createCoords(3, 20, 3, 1), 3))
        {
            CUR_ROOM = initRoom(ROOM3_2);
            initRules(CUR_ROOM, R_ARRAY, &nRULES);
            PLAYER.dim.coord = (COORD) {14, 8};
        }

        // after getting wallet
        if (r3_3a && CUR_ROOM.roomNo == ROOM3_1)
        {
            setRuleColor(&R_ARRAY[1], WHTB);
            setRuleColor(&R_ARRAY[2], WHTB);

            setRuleColType(&R_ARRAY[1], 0);
            setRuleColType(&R_ARRAY[2], 0);

            setRuleColor(&R_ARRAY[4], reset);
            setRuleColType(&R_ARRAY[4], 6);
            setRuleDlgId(&R_ARRAY[7], 0);

            setRuleColType(&R_ARRAY[5], 6);
        }

        break;

        case ROOM3_2:

        // lever event
        if (eventNo == 300)
        {
            r3_2a = 1;
        }
        
        // flag for wires
        r3_2f = !r3_2f;

        // logic for wires
        if (r3_2f)
        {
            setRuleColor(&R_ARRAY[2], BBLU);
            setRuleColType(&R_ARRAY[2], 5);
            setRuleColor(&R_ARRAY[3], BBLU);
            setRuleColType(&R_ARRAY[3], 5);
    
            setRuleColor(&R_ARRAY[8], RED);
            setRuleColType(&R_ARRAY[8], 4);
            setRuleColor(&R_ARRAY[9], RED);
            setRuleColType(&R_ARRAY[9], 4);
            setRuleColor(&R_ARRAY[12], RED);
            setRuleColType(&R_ARRAY[12], 4);
            setRuleColor(&R_ARRAY[13], RED);
            setRuleColType(&R_ARRAY[13], 4);
            setRuleColor(&R_ARRAY[14], RED);
            setRuleColType(&R_ARRAY[14], 4);
        }
        else
        {
            setRuleColor(&R_ARRAY[3], RED);
            setRuleColType(&R_ARRAY[3], 4);
            setRuleColType(&R_ARRAY[2], 4);
            setRuleColor(&R_ARRAY[2], RED);

            setRuleColor(&R_ARRAY[8], BLU);
            setRuleColType(&R_ARRAY[8], 5);
            setRuleColor(&R_ARRAY[9], BLU);
            setRuleColType(&R_ARRAY[9], 5);
            setRuleColor(&R_ARRAY[12], BLU);
            setRuleColType(&R_ARRAY[12], 5);
            setRuleColor(&R_ARRAY[13], BLU);
            setRuleColType(&R_ARRAY[13], 5);
            setRuleColor(&R_ARRAY[14], BLU);
            setRuleColType(&R_ARRAY[14], 5);
        }

        // go to room 3_2
        if (compareCoords(PLAYER.dim.coord, createCoords(15, 7, 4, 1), 4))
        {
            CUR_ROOM = initRoom(ROOM3_1);
            initRules(CUR_ROOM, R_ARRAY, &nRULES);
            PLAYER.dim.coord = (COORD) {4, 21};
        }

        break;

        case ROOM3_3:

        // get wallet!!
        if (r3_2a)
        {
            setRuleColor(&R_ARRAY[2], BLU);
            setRuleColor(&R_ARRAY[5], BLU);
            setRuleColor(&R_ARRAY[8], BLU);
            setRuleColor(&R_ARRAY[9], BLU);
            setRuleColType(&R_ARRAY[2], 5);
            setRuleColType(&R_ARRAY[5], 5);
            setRuleColType(&R_ARRAY[8], 5);
            setRuleColType(&R_ARRAY[9], 5);
        }

        // teleport backu
        if (r3_3a)
        {
            CUR_ROOM = initRoom(ROOM3_1);
            initRules(CUR_ROOM, R_ARRAY, &nRULES);
            PLAYER.dim.coord = (COORD) {5, 49};

            setRuleColor(&R_ARRAY[1], WHTB);
            setRuleColor(&R_ARRAY[2], WHTB);

            setRuleColType(&R_ARRAY[1], 0);
            setRuleColType(&R_ARRAY[2], 0);

            setRuleColor(&R_ARRAY[4], reset);
            setRuleColType(&R_ARRAY[4], 6);
            setRuleDlgId(&R_ARRAY[7], 0);

            setRuleColType(&R_ARRAY[5], 6);

            createDialogues(340, 4, DIALOGUES, &nDIALOGUES);
        }

        // if get wallet
        if (compareCoords(PLAYER.dim.coord, createCoords(8, 36, 1, 1), 1))
        {
            createDialogues(337, 3, DIALOGUES, &nDIALOGUES);
            disableAllRules(R_ARRAY, nRULES);
            textColor(RED);

            r3_3a = 1;
        }

        
        // key!!!
        if (compareCoords(PLAYER.dim.coord, createCoords(13, 56, 3, 1), 3))
        {
            CUR_ROOM = initRoom(ROOM3_1);
            initRules(CUR_ROOM, R_ARRAY, &nRULES);
            PLAYER.dim.coord = (COORD) {4, 49};
        }

        break;

        case ROOM3_4:

        // go to room 3_1
        if (compareCoords(PLAYER.dim.coord, createCoords(6, 12, 1, 1), 1))
        {
            CUR_ROOM = initRoom(ROOM3_1);
            initRules(CUR_ROOM, R_ARRAY, &nRULES);
            PLAYER.dim.coord = (COORD) {5, 55};
        }

        // elevator!!!
        if (eventNo == 302 && PLAYER.hasKey)
        {
            CUR_ROOM = initRoom(ELV3);
            initRules(CUR_ROOM, R_ARRAY, &nRULES);
            PLAYER.dim.coord = CUR_ROOM.default_pos;

            disableAllRules(R_ARRAY, nRULES);
            textColor(YEL);

            createDialogues(347, 10, DIALOGUES, &nDIALOGUES);
        }

        break;

        case ELV3:

        if (1)
        {
            enableAllRules(R_ARRAY, nRULES);
        }

        if (eventNo == 303)
        {
            CUR_ROOM = initRoom(ROOM4_1);
            initRules(CUR_ROOM, R_ARRAY, &nRULES);
            PLAYER.dim.coord = CUR_ROOM.default_pos;

            createDialogues(445, 4, DIALOGUES, &nDIALOGUES);
        }

        break;

        }
    }
    return 0;
}