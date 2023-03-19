#include "rules.h"

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

void textColor(COLOR color)
{
    printf("%s", color);
}

void resetColor()
{
    printf("\e[0m");
}

APRULE createAprule(int start, int width, COLOR color)
{
    APRULE aprule = {0};

    aprule.start = start;
    aprule.width = width;
    strcpy(aprule.color, color);

    return aprule;
}

void printFrame(ROOM room, RULEARRAY R, int nR)
{
    int line_ind = 0, R_ind = 0, total_rules = 0, buf_ind = 0, rulesbuf_ind = 0;
    char buffer[100] = {0};
    APRULE aprule_arr[10];
    FILE *fstream = fopen(room.f_path, "r");

    while (feof(fstream) == 0)
    {
        fgets(buffer, sizeof(buffer), fstream);
        
        total_rules = 0;
        while (R[R_ind].dim.coord.row == line_ind && R_ind < nR)
        {
            
            aprule_arr[total_rules++] = createAprule(
                        R[R_ind].dim.coord.col,
                        R[R_ind].dim.size.width,
                        R[R_ind].color
            );

            R_ind++;
        }

        buf_ind = 0; 
        rulesbuf_ind = 0;
        while (buf_ind<strlen(buffer))
        {
            if (rulesbuf_ind < total_rules)
            {
                if (aprule_arr[rulesbuf_ind].start == buf_ind)
                {
                    textColor(aprule_arr[rulesbuf_ind].color);
                    for (int i=0; i<aprule_arr[rulesbuf_ind].width; i++)
                    {
                        printf("%c", buffer[buf_ind]);
                        buf_ind++;
                    }
                    resetColor();
                    rulesbuf_ind++;
                }
                else printf("%c", buffer[buf_ind++]);
            }
            else printf("%c", buffer[buf_ind++]);
        }

        // got to next line
        line_ind++;
    }

    fclose(fstream);
}

void applyRules(ROOM room, RULEARRAY R, int nR, TXTFILE CPATH)
{
    
}
