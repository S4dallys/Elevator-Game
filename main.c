#include "main.h"

#define EVENTS_PATH "EVENTS.txt"
#define DIALOGUE_PATH "dialogue.txt"


int main()
{
    ROOM cur_room = initRoom(ROOM1_1);
    PLAYER Plr = createPlayer((COORD) {2, 2});
    RULEARRAY r_array;
    int n_r_array;


    initRules(cur_room, r_array, &n_r_array);

    displayRules(r_array, n_r_array, 0);




    // displayRules(r_array, n_r_array, 0);

    // setRuleCh(&r_array[0], '`');



    char key;
    int i = 0;
    while(key != 'x')
    {
        i = !i;
        system("cls");
        textColor(i ? RED : MAG);
        printFrame(cur_room, r_array, n_r_array, Plr);
        resetColor();
        key = getch();

        if (key == 'g') disableAllRules(r_array, n_r_array);
        else if (key == 'h') enableAllRules(r_array, n_r_array);
        else if (key == 'y') cur_room = initRoom(ROOM1_2);

        Plr.dim.coord = getNextCoordinate(Plr.dim.coord, key, &Plr.direction);

    }
    
    




    


    





    return 0;
}