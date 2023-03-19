#include "main.h"

#define EVENTS_PATH "EVENTS.txt"
#define DIALOGUE_PATH "dialogue.txt"


int main()
{
    ROOM cur_room = initRoom(ROOM1_1);
    RULEARRAY r_array;
    int n_r_array;


    initRules(cur_room, r_array, &n_r_array);



    addRule(
        setRule(
            createDim(7, 50, 5, 1), YELB,
            1, 1
        ), r_array, &n_r_array
    );

    addRule(
        setRule(
            createDim(7, 12, 2, 1), MAGHB,
            1, 1
        ), r_array, &n_r_array
    );

    printFrame(cur_room, r_array, n_r_array);

    printf("\n");
    disableRule(&r_array[7]);

    printFrame(cur_room, r_array, n_r_array);


    // displayRules(r_array, n_r_array, 0);
    
    




    


    





    return 0;
}