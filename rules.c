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

void setRuleEventId(RULE *rule, int eventId)
{
    rule->eventid = eventId;
}

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
        char temp, buffer[100];
        fscanf(fstream, "%c", &temp);
        if (temp == '/')
        {
            fgets(buffer, sizeof(buffer), fstream);
            continue;
        } else fseek(fstream, -1, SEEK_CUR);
        
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

int getRulesByRow (RULEARRAY R, int nR, RULEARRAY dest, int row_num)
{
    int i = 0, j = 0;
    while (i < nR)
    {
        if (R[i].dim.coord.row == row_num)
        {
            while (R[i].dim.coord.row == row_num)
            {
                if (R[i].isEnabled == 1)
                    dest[j++] = R[i++];
                else i++;
            }
            return j;
        } i++;
    }

    return j;
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

void killPlayer(ROOM *room, RULEARRAY R, int *nR, PLAYER * player)
{
    *room = initRoom(room->f_default);
    initRules(*room, R, nR);
    player->hasKey = 0;
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