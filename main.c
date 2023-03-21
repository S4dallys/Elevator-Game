#include "main.h"

#define EVENTS_PATH "EVENTS.txt"
#define DIALOGUE_PATH "dialogue.txt"


int main()
{
    ROOM cur_room = initRoom(ROOM1_2);
    PLAYER Plr = createPlayer((COORD) {2, 2});
    RULEARRAY r_array;
    int n_r_array;

    initRules(cur_room, r_array, &n_r_array);

    Plr.dim.coord = cur_room.default_pos;
    COORD next_coord = cur_room.default_pos;

    char key = '1';
    int i = 0;
    RULE action;

    while(key != 'x')
    {
        system("cls");
        
        if (key != INTERACT)
            printFrame(&cur_room, r_array, &n_r_array, next_coord, &Plr);

        key = getch();

        next_coord = getNextCoordinate(Plr.dim.coord, key, &Plr.x_dir, &Plr.y_dir);
        
        Plr.dim.coord = evaluateMove(&cur_room, Plr.dim.coord, next_coord, r_array, &n_r_array, key);
    }
    
    




    





    return 0;
}