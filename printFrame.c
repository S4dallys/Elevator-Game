#include <stdio.h>
#include <string.h>
#include "rules.h"

int getNextRuleRow (RULEARRAY R, int nR, int start)
{
    int i = 0;
    while (i < nR)
    {
        if (R[i].dim.coord.row > start)
            return R[i].dim.coord.row;
        else i++;
    }

    return -1;
}

int sprintFrame (ROOM room, RULEARRAY R, int nR, COORD player_coords)
{
    RULEARRAY current_rules;
    int num_rules;
    int stop_at_row;

    char buffer[100] = {0};
    int line_number = 0;

    // initializing rulearray for later
    num_rules = getRulesByRow(R, nR, current_rules, 0);
    stop_at_row = 0;

    FILE *filestream;
    filestream = fopen(room.f_path, "r");
    
    while (feof(filestream) == 0) 
    {
        fgets(buffer, sizeof(buffer), filestream);

        if (line_number == player_coords.row)
            buffer[player_coords.col] = '@';

        // line has rules
        char temp_string[100] = {0};
        int offset = 0;
        if (line_number == stop_at_row)
        {
            // apply rules
            for (int i = 0; i < num_rules; i++)
            {
                // print before part of string
                memcpy(temp_string, buffer + offset, current_rules[i].dim.coord.col - offset);
                printf("%s", temp_string);
                memset(temp_string, 0, sizeof(temp_string));
                offset = current_rules[i].dim.coord.col;


                // print formatted string
                memcpy(temp_string, buffer + offset, current_rules[i].dim.size.width);
                textColor(current_rules[i].color);
                printf("%s", temp_string);
                resetColor();
                memset(temp_string, 0, sizeof(temp_string));
                offset += current_rules[i].dim.size.width;
            }

            // print last part of string
            strcpy(temp_string, buffer + offset);
            printf("%s", temp_string);

            // after aoplying rules in current_rules
            stop_at_row = getNextRuleRow(R, nR, stop_at_row);
            if (stop_at_row != -1)
            {
                num_rules = getRulesByRow(R, nR, current_rules, stop_at_row);
            }
        }
        
        // if row has no rules
        else
        {
            printf("%s", buffer);
        }

        line_number++;
    }

    fclose(filestream);
}

RULE getRuleByCoord ()
{

}

COORD evaluateMove ()
{

}

