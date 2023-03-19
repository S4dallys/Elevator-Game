#include "main.h"

#define EVENTS_PATH "EVENTS.txt"
#define DIALOGUE_PATH "dialogue.txt"


int main()
{
    ROOM cur_room = initRoom(ROOM1_1);
    RULEARRAY r_array;
    int n_r_array;


    initRules(cur_room, r_array, &n_r_array);

    printFrame(cur_room, r_array, n_r_array);

    disableRule(&r_array[1]);

    printf("\n");
    printFrame(cur_room, r_array, n_r_array);

    enableRule(&r_array[1]);
    printf("\n");
    printFrame(cur_room, r_array, n_r_array);
    




    


    





    return 0;
}