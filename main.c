#include "main.h"

#define EVENTS_PATH "EVENTS.txt"
#define DIALOGUE_PATH "dialogue.txt"


int main()
{
    ROOM cur_room = initRoom(ROOM1_1);
    RULEARRAY r_array;
    int n_r_array;

    PLAYER Plr = createPlayer((COORD) {2, 2});

    initRules(cur_room, r_array, &n_r_array);


    char key;
    while(key != 'x')
    {
        system("cls");
        printFrame(cur_room, r_array, n_r_array, Plr);
        key = getch();

        Plr.dim.coord = getNextCoordinate(Plr.dim.coord, key, &Plr.direction);

    }
    
    




    


    





    return 0;
}