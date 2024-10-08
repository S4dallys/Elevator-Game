#include <stdio.h>
#include <string.h>
#include "E_string.h"
#include "room.h"
#include "ansi.h"


typedef STRING_10 COLOR;

// collision types

#define NORMAL   0
#define DOOR     1
#define LKD_DOOR 2
#define ELEVATOR 3
#define DEATH    4
#define NONE     5
#define CUSTOM   6



typedef struct RULE
{
    int isEnabled;
    DIM dim;
    COLOR color;
    int colType;
    int dlgid;
    int eventid;
    char ch;
} RULE;

typedef RULE RULEARRAY[150];
typedef int DIALOGUES[20]; 

// deprecated

// RULE setRule(DIM dim, COLOR color, int ruletype, int eventid);
// void addRule(RULE rule, RULEARRAY R, int *nR);

// important 

void setRuleColor(RULE *rule, COLOR color);
void setRuleColType(RULE *rule, int colType);
void setRuleCh(RULE *rule, char ch);
void enableRule(RULE *rule);
void disableRule(RULE *rule);
void setAllRulesTo(RULEARRAY R, int nR, COLOR color, int colType, char ch);

void enableAllRules(RULEARRAY R, int nR);
void disableAllRules(RULEARRAY R, int nR);

void initRules(ROOM room, RULEARRAY R, int *nR);
void sortRules(RULEARRAY R, int nR);

void strToAnsi(COLOR id);
void textColor(COLOR color);
void resetColor();

void displayRules(RULEARRAY R, int nR, int output);

char findChar(TXTFILE path, int row, int col);

int getRulesByRow (RULEARRAY R, int nR, RULEARRAY dest, int row_num);

void killPlayer(ROOM *room, RULEARRAY R, int *nR, PLAYER * player);

void setRuleDlgId(RULE *rule, int dlgId);