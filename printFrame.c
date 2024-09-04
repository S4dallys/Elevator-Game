#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rules.h"

#define MROW 0
#define PROW 1
#define MCOL 2
#define PCOL 3

void printMainMenu()
{
    system("cls");
    printf("Thank you for Installing!\n");
    printf("Have fun playing \"\"!");
    printf("\n\n\nPress any key to start!\n(press p to leave game anytime)");
    printf("\n\n\n\nTeam BillySchmidht 2023\n");
}

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

int sprintFrame (ROOM room, RULEARRAY R, int nR, PLAYER player)
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

        if (line_number == player.dim.coord.row)
            buffer[player.dim.coord.col] = '@';

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

                // if colType custom
                if (current_rules[i].colType == CUSTOM)
                {
                    if (current_rules[i].ch == '`')
                    {
                        for (int j = 0; j < strlen(temp_string); j++)
                            if (temp_string[j] != '@')
                                temp_string[j] = ' ';
                    }
                    else
                    {
                        for (int j = 0; j < strlen(temp_string); j++)
                            if (temp_string[j] != '@')
                                temp_string[j] = current_rules[i].ch;
                    }
                }

                // apply color
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

int getRuleByCoord (RULEARRAY R, int nR, COORD coord)
{
    int i = 0;
    while (i < nR)
    {
        if (R[i].dim.coord.row == coord.row)
        {
            while (R[i].dim.coord.row == coord.row)
            {
                if (R[i].dim.coord.col <= coord.col && R[i].dim.coord.col + R[i].dim.size.width > coord.col
                            && R[i].isEnabled == 1)
                    return i;
                else i++;
            }
            return -1;
        } i++;
    }

    return -1;
}

int getDirectionMoved(COORD difference)
{
    if (difference.row == 0 && difference.col == 0)
        return -1;
    else if (difference.row != 0)
    {
        if (difference.row < 0)
            return MROW;
        else return PROW;
    }
    else
    {
        if (difference.col < 0)
            return MCOL;
        else return PCOL;
    }
}

COORD getNextValidCoord (COORD prev, int direction, int offset, COORD * stopper)
{
    *stopper = prev;

    switch (direction)
    {
    case MROW:
        prev.row -= 1 + offset;
        stopper->row = prev.row + 1;
        return prev;
        break;
    case PROW:
        prev.row += 1 + offset;
        stopper->row = prev.row - 1;
        return prev;
        break;
    case MCOL:
        prev.col -= 1 + offset;
        stopper->col = prev.col + 1;
        return prev;
        break;
    case PCOL:
        prev.col += 1 + offset;
        stopper->col = prev.col - 1;
        return prev;
        break;
    }
}

COORD evaluateMove (COORD prev, COORD next, ROOM *room, RULEARRAY R, int *nR, PLAYER * player)
{
    int rule_applied;
    COORD difference = {next.row - prev.row, next.col - prev.col};
    int diff = (next.row - prev.row) ? next.row - prev.row : next.col - prev.col; 
    COORD stopper;

    int direction = getDirectionMoved(difference);

    COORD coord_found;
    char char_found;

    int i = 0;
    while (i < abs(diff) && direction != -1)
    {
        coord_found = getNextValidCoord(prev, direction, i, &stopper);
        char_found = findChar(room->f_path, coord_found.row, coord_found.col);

        rule_applied = getRuleByCoord(R, *nR, coord_found);

        if (rule_applied == -1)
        {
            if (char_found != '|' && char_found != '_' && char_found != '.')
            {} // do nothing

            else if (char_found == '.')
            {
                killPlayer(room, R, nR, player);
                return room->default_pos;
            }
            else
            {
                return stopper;
            }
        }

        else 
        {
            if (R[rule_applied].colType == DEATH)
            {
                killPlayer(room, R, nR, player);
                return room->default_pos;
            }
            else if (R[rule_applied].colType == NONE)
            {
                // do nothing
            }
            else if (R[rule_applied].colType == DOOR)
            {
                return coord_found;
            }
            else if (R[rule_applied].colType == CUSTOM && R[rule_applied].ch == '`')
            {
                // do nothing
            }
            // ELEVATOR, NORMAL, LCKDOOR, CUSTOM
            else
            {
                return stopper;
            }
        }

        i++;
    }
    
    return next;
}

int sprintDialogueBox (TXTFILE dialogue_path, int dialogueNo)
{
    int maxCharsPerLine = 50;

    char cur_dlg[60] = "";
    char cur_dlg2[60] = "";
    char pressX[10] = "- - - -";


    int found = 0;
    char buffer[120];
    char temp_string[120];
    FILE *filestream;
    filestream = fopen (dialogue_path, "r");
    if (dialogueNo != 0)
    {
        strcpy(pressX, "PRESS X");

        // copy to cur_dlg and cur_dlg2

        int num;

        while (feof(filestream) == 0)
        {
            fscanf(filestream, "%d", &num);
            if (num == dialogueNo)
            {
                fseek(filestream, 1, SEEK_CUR);
                fgets(buffer, 120, filestream);
                found = 1;
                break;
            }
            else    
            {
                fgets(temp_string, 120, filestream);
            }
        }
    }

    fclose(filestream);

    // set dialogues
    if (found == 1)
    {
        memcpy(cur_dlg, buffer, maxCharsPerLine);
        memcpy(cur_dlg2, buffer + maxCharsPerLine, maxCharsPerLine);
    }

    // space
    printf("\n");

    printf("\t- %s -\n\n", pressX);
    printf("%s\n", cur_dlg);
    printf("%s", cur_dlg2);
}

COORD * createCoords(int row, int col, int width, int height)
{
    static COORD coord_array[50] = {0};

    int coord_ind = 0;
    for (int k = 0; k < height; k++)
    {
        for (int i = 0; i < width; i++)
        {
            coord_array[coord_ind++] = (COORD) {k + row, i + col};
        }
    }

    return coord_array;
}

void createDialogues(int start, int total, DIALOGUES d_array, int *nDialogues)
{
    int j = 0;
    for (int i = 0; i < total; i++)
    {
        d_array[j++] = start + i;
    }

    *nDialogues = j;
}

COORD frontCoord(PLAYER player)
{
    switch (player.dir)
    {
        case TOP:
            return (COORD) {player.dim.coord.row - 1, player.dim.coord.col};
        case LEFT:
            return (COORD) {player.dim.coord.row, player.dim.coord.col - 1};
        case BOTTOM:
            return (COORD) {player.dim.coord.row + 1, player.dim.coord.col};
        case RIGHT:
            return (COORD) {player.dim.coord.row, player.dim.coord.col + 1};
    }
}

int fillDialogues (DIALOGUES D, int *nD, int dlgNo)
{
    FILE *filestream = fopen("dlgid.txt", "r");

    char buffer[130] = "";

    int num, j = 0, dialogueNo = 1;
    while (feof(filestream) == 0)
    {
        fscanf(filestream, "%d", &num);
        if (num == dlgNo)
        {
            while (dialogueNo != 0)
            {
                fscanf(filestream, " %d", &dialogueNo);
                D[j++] = dialogueNo;
            }
            break;
        }
        else    
        {
            fgets(buffer, 130, filestream);
        }
    }

    *nD = j - 1;

    fclose(filestream);
}