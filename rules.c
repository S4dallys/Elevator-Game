#include "rules.h"

void setRuleColType(RULE *rule, int colType)
{
    rule->colType = colType;
}

void setRuleCh(RULE *rule, char ch)
{
    rule->ch = ch;
}

void setAllRulesTo(RULEARRAY R, int nR, COLOR color, int colType, char ch)
{
    int i;
    for (i=0; i<nR; i++)
    {
        strcpy(R[i].color, color);
        R[i].colType = colType;
        R[i].ch = ch;
    }
}

/*
@param [color] color code
@return none
*/
void strToAnsi(COLOR color)
{
    FILE *fstream;
    fstream = fopen("colors.txt", "r");
    char color_buffer[20];
    char ansi_buffer[20];

    int i=0;
    while (feof(fstream) == 0)
    {
        fseek(fstream, 8, SEEK_CUR);
        fscanf(fstream, "%s %s ", color_buffer, ansi_buffer);
        if (strcmp(color, color_buffer) == 0)
        {
            strcpy(color, ansi_buffer);
            break;
        }
    }
    fclose(fstream);
}

void ansiToStr(COLOR ansi, COLOR buffer)
{
    FILE *fstream;
    fstream = fopen("colors.txt", "r");
    char color_buffer[20];
    char ansi_buffer[20];

    int i=0;
    while (feof(fstream) == 0)
    {
        fseek(fstream, 8, SEEK_CUR);
        fscanf(fstream, "%s %s ", color_buffer, ansi_buffer);
        if (strcmp(ansi, ansi_buffer) == 0)
        {
            strcpy(buffer, color_buffer);
            break;
        }
    }
    fclose(fstream);
}

/*
@param [dim] rule dimensions
@param [color] rule color
@return RULE class instance
*/
// RULE setRule(DIM dim, COLOR color, int ruletype, int eventid)
// {
//     RULE rule = {1};

//     rule.dim = dim;
//     rule.ruleType = ruletype;
//     rule.eventid = eventid;
//     setRuleColor(&rule, color);

//     return rule;
// }

/*
@param [*rule] pointer to a RULE class
@param [color] color you want to set that rule to
@return none
*/
void setRuleColor(RULE *rule, COLOR color)
{
    strcpy(rule->color, color);
}

/*
@param [*rule] pointer to a RULE class
@return none
*/
void disableRule(RULE *rule)
{
    rule->isEnabled = 0;
}

/*
@param [*rule] pointer to a RULE class
@return none
*/
void enableRule(RULE *rule)
{
    rule->isEnabled = 1;
}

void disableAllRules(RULEARRAY R, int nR)
{
    int i;
    for (i=0; i<nR; i++)
    {
        disableRule(&R[i]);
    }
}

void enableAllRules(RULEARRAY R, int nR)
{
    int i;
    for (i=0; i<nR; i++)
    {
        enableRule(&R[i]);
    }
}

/*
INITIALIZE RULEARRAY with rules from rules.txt
@param [room] current room being rendered
@param [R] rules array to init rules in
@return none
*/
void initRules(ROOM room, RULEARRAY R, int *nR)
{
    int i = 0;
    RULE rule = {1};
    FILE *fstream;
    COLOR colorid;

    fstream = fopen(room.f_rule, "r");

    while (feof(fstream) == 0)
    {
        fscanf(fstream, "%d %d %d %d %s %d %d %d %c ", 
            &rule.dim.coord.row,
            &rule.dim.coord.col,
            &rule.dim.size.width,
            &rule.dim.size.height,
            colorid,
            &rule.colType,
            &rule.eventid,
            &rule.isEnabled,
            &rule.ch);

        strToAnsi(colorid);
        strcpy(rule.color, colorid);

        R[i++] = rule;
    } 

    fclose(fstream);
    *nR = i;
}

void textColor(COLOR color)
{
    printf("%s", color);
}

void resetColor()
{
    printf("\e[0m");
}

/*
Prints exactly one frame WITH color rules
@param [room] cur_room instance
@param [R] rule array associated with room
@param [nR] no of items in R
*/
void printFrame(ROOM *room, RULEARRAY R, int *nR, COORD next_coord, PLAYER *player)
{
    int line_ind = 0, R_ind = 0, total_rules = 0, buf_ind = 0, rulesbuf_ind = 0, rule_applied = 0;
    char buffer[100] = {0};
    RULE aprule_arr[15];
    FILE *fstream = fopen(room->f_path, "r");

    while (feof(fstream) == 0)
    {
        fgets(buffer, sizeof(buffer), fstream);
        
        // gets line i from file
        total_rules = 0;
        while (R[R_ind].dim.coord.row == line_ind && R_ind < *nR)
        {
            // adds rule to array if rule is in line i
            if (R[R_ind].isEnabled) 
                aprule_arr[total_rules++] = R[R_ind];

            R_ind++;
        }

        // iterates through each char in line i
        buf_ind = 0; 
        rulesbuf_ind = 0;
        while (buf_ind<strlen(buffer))
        {
            // if char is PLAYER
            if (player->dim.coord.row == line_ind && player->dim.coord.col == buf_ind)
            {
                printf("%c", player->sprite);
            }

            // if there are still rules related to line i
            else if (rulesbuf_ind < total_rules)
            {
                // if rule column is same as char
                if (aprule_arr[rulesbuf_ind].dim.coord.col == buf_ind)
                {
                    // apply rule color
                    textColor(aprule_arr[rulesbuf_ind].color);
                    // iterate through chars until rule is over
                    for (int i=0; i<aprule_arr[rulesbuf_ind].dim.size.width; i++)
                    {
                        rule_applied = 1;

                        if (aprule_arr[rulesbuf_ind].colType == CUSTOM)
                            printf("%c", (aprule_arr[rulesbuf_ind].ch != '`')
                            ? aprule_arr[rulesbuf_ind].ch : ' ');
                        else
                            printf("%c", buffer[buf_ind]);
                        buf_ind++;
                    }
                    // resete color
                    resetColor();
                    rulesbuf_ind++;
                }
                // if rule column is not same as char
                else goto def;
            }
            // if no more rules
            else
            {
                def:
                if (buffer[buf_ind] == '.')
                {
                textColor(MAG);
                printf("%c", buffer[buf_ind]);
                resetColor();
                }
                else printf("%c", buffer[buf_ind]);
            }

            // go to next char
            if (rule_applied == 0)
                buf_ind++;
            else 
                rule_applied = 0;
        }

        // got to next line
        line_ind++;
    }

    fclose(fstream);
}

/*
Can be used to log into another file via > operator
@param [R] rule array to diaplay
@param [nR] no of items in R
@param [output] 1 if writing to file, 0 if writing to terminal
@return none
*/
void displayRules(RULEARRAY R, int nR, int output)
{
    printf("\nIND     ROW  COL WIDTH      COLOR     COLTYPE  EVENTID  CHAR  ISENABLED\n\n");
    for (int i=0; i<nR; i++)
    {
        printf("%2d.", i);

        printf("     (%-2d, %2d)  (%-2d)", 
        R[i].dim.coord.row, 
        R[i].dim.coord.col,
        R[i].dim.size.width);

        char buffer[13] = {0};
        ansiToStr(R[i].color, buffer);
        printf("      ");

        if (!output)
            textColor(R[i].color);

        printf("%-6s", buffer);

        if (!output)
            resetColor();

        printf("       %d", R[i].colType);

        printf("        %d", R[i].eventid);

        if (R[i].colType == 6 || output)
            printf("      %c", R[i].ch);
        else
        {
            printf("      ");
            textColor(BLK);
            printf("%c", R[i].ch);
            resetColor();
        }

        printf("        %d\n\n", R[i].isEnabled);
    }
}

void swapRules(RULE *a, RULE *b) {
  RULE temp = *a;
  *a = *b;
  *b = temp;
}

void sortRules(RULEARRAY R, int nR) {
    int i;
    for (int step = 0; step < nR - 1; step++) {
        int min_idx = step;
        for (i = step + 1; i < nR; i++) {
            if (R[i].dim.coord.row < R[min_idx].dim.coord.row)
                min_idx = i;
            else if (R[i].dim.coord.row == R[min_idx].dim.coord.row)
                if (R[i].dim.coord.col < R[min_idx].dim.coord.col)
                    min_idx = i;
        }
        if (min_idx != i)
            swapRules(&R[min_idx], &R[step]);
    }
}

// void addRule(RULE rule, RULEARRAY R, int *nR)
// {
//     R[*nR] = rule;
//     *nR = *nR + 1;
//     sortRules(R, *nR);
// }

void killPlayer(ROOM *room, RULEARRAY R, int *nR)
{
    *room = initRoom(room->f_default);
    initRules(*room, R, nR);
}


RULE getAction(RULEARRAY R, int nR, COORD nextCoord, ROOM room)
{
    int i = 0;
    RULE rule; 
    rule.isEnabled = -1;
    while (i<nR)
    {
        if (R[i].dim.coord.row == nextCoord.row && 
            nextCoord.col >= R[i].dim.coord.col && nextCoord.col < R[i].dim.size.width + R[i].dim.coord.col
            && R[i].isEnabled == 1)
                return R[i];
        i++;
    }

    FILE *fp = fopen(room.f_path, "r");
    char buffer[100];
    i = 0;
    while (fgets(buffer, sizeof(buffer), fp)) 
    { 
        if(i == nextCoord.row) 
        { 
            rule.ch = buffer[nextCoord.col];
            break;
        } 
        i++; 
    } 
    fclose(fp);
    return rule;
}

char findChar(TXTFILE path, int row, int col)
{
    FILE *fp = fopen(path, "r");
    char buffer[100];
    int i = 0;
    while (fgets(buffer, sizeof(buffer), fp)) 
    { 
        if(i == row) 
        { 
            break;
        } 
        i++; 
    } 
    return buffer[col];
    fclose(fp);
}


COORD evaluateMove(ROOM *room, COORD playerCoord, COORD nextCoord, RULEARRAY R, int *nR, char key)
{
    RULE action = getAction(R, *nR, nextCoord, *room);
    if (action.isEnabled != -1)
        switch (action.colType)
        {
            case NORMAL:
                return playerCoord;
                break;
            case DOOR:
                // enterNextRoom();
                break;
            case LKD_DOOR:
                break;
            case ELEVATOR:
                break;
            case DEATH:
                goto death;
                break;
            case NONE:
                return nextCoord;
                break;
            case CUSTOM:
                if (action.ch == '`')
                    return nextCoord;
                else
                    return playerCoord;
                break;
        }
    
    else
        switch (action.ch)
        {
            case '.':
                death:
                killPlayer(room, R, nR);
                return room->default_pos;
                break;
            case '|':
            case '_':
                return playerCoord;
                break;
        }

    int diff;
    int i;
    char ch;
    COORD pos = nextCoord;
    switch (key)
    {
        case W_KEY_SHF:
            for (i=1; i<=ROW_SHF_SIZE; i++)
                if (findChar(room->f_path, playerCoord.row - i, playerCoord.col) != ' ') 
                {
                    pos = (COORD) {playerCoord.row - i + 1, playerCoord.col};
                    break;
                }
            break;
        case A_KEY_SHF:
            for (i=1; i<=COL_SHF_SIZE; i++)
                if (findChar(room->f_path, playerCoord.row, playerCoord.col - i) != ' ') 
                {
                    pos = (COORD) {playerCoord.row, playerCoord.col - i + 1};
                    break;
                }
            break;
        case S_KEY_SHF:
            for (i=1; i<=ROW_SHF_SIZE; i++)
                if (findChar(room->f_path, playerCoord.row + i, playerCoord.col) != ' ') 
                {
                    pos = (COORD) {playerCoord.row + i - 1, playerCoord.col};
                    break;
                }
            break;
        case D_KEY_SHF:
            for (i=1; i<=COL_SHF_SIZE; i++)
                if (findChar(room->f_path, playerCoord.row, playerCoord.col + i) != ' ') 
                {
                    pos = (COORD) {playerCoord.row, playerCoord.col + i - 1};
                    break;
                }
            break;
    }

    // if (last.row == -1)
    //     return nextCoord;
    
    return pos;
}