#include "rules.h"

/*
@param [id] color code
@return none
*/
void strToAnsi(COLOR id)
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
        if (strcmp(id, color_buffer) == 0)
        {
            strcpy(id, ansi_buffer);
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
// RULE setRule(DIM dim, COLOR color)
// {
//     RULE rule = {1};

//     rule.dim = dim;
//     setColor(&rule, color);

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

/*
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
        fscanf(fstream, "%d %d %d %d %s %d %d ", 
            &rule.dim.coord.row,
            &rule.dim.coord.col,
            &rule.dim.size.width,
            &rule.dim.size.height,
            colorid,
            &rule.ruleType,
            &rule.eventid);

        strToAnsi(colorid);
        strcpy(rule.color, colorid);

        R[i++] = rule;
    } 

    fclose(fstream);
    *nR = i;
}

void applyRule(RULE rule, FILE *source, FILE *dest, char buffer[100], int * offset)
{
    
}

void applyRules(ROOM room, RULEARRAY R, int nR, TXTFILE CPATH)
{
    
}
