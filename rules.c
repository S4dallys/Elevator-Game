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
RULE setRule(DIM dim, COLOR color, int ruletype, int eventid)
{
    RULE rule = {1};

    rule.dim = dim;
    rule.ruleType = ruletype;
    rule.eventid = eventid;
    setRuleColor(&rule, color);

    return rule;
}

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

/*
Prints exactly one frame WITH color rules
@param [room] cur_room instance
@param [R] rule array associated with room
@param [nR] no of items in R
*/
void printFrame(ROOM room, RULEARRAY R, int nR, PLAYER player)
{
    int line_ind = 0, R_ind = 0, total_rules = 0, buf_ind = 0, rulesbuf_ind = 0;
    char buffer[100] = {0};
    APRULE aprule_arr[15];
    FILE *fstream = fopen(room.f_path, "r");

    while (feof(fstream) == 0)
    {
        fgets(buffer, sizeof(buffer), fstream);
        
        total_rules = 0;
        while (R[R_ind].dim.coord.row == line_ind && R_ind < nR)
        {
            if (R[R_ind].isEnabled) 
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
            if (player.dim.coord.row == line_ind && player.dim.coord.col == buf_ind)
            {
                if (player.direction)
                    printf("\\%c", player.sprite);
                else
                    printf("%c/", player.sprite);
                buf_ind = buf_ind + 2;
                continue;
            }
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

/*
Can be used to log into another file via > operator
@param [R] rule array to diaplay
@param [nR] no of items in R
@param [output] 1 if writing to file, 0 if writing to terminal
@return none
*/
void displayRules(RULEARRAY R, int nR, int output)
{
    printf("\nIND     ROW  COL WIDTH      COLOR     RULETYPE  EVENTID  ISENABLED\n\n");
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

        printf("        %d", R[i].ruleType);

        printf("        %d", R[i].eventid);

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

void addRule(RULE rule, RULEARRAY R, int *nR)
{
    R[*nR] = rule;
    *nR = *nR + 1;
    sortRules(R, *nR);
}

// copy paste to add rule
// addRule(
//         setRule(
//             createDim(7, 50, 5, 1), YELB,
//             1, 1
//         ), r_array, &n_r_array
//     );