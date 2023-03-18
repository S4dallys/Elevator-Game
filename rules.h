#include <stdio.h>
#include <string.h>
#include "E_string.h"
#include "room.h"
#include "bool.h"


typedef STRING_10 COLOR;
typedef int R_TYPE;

// rule types

#define DOOR     0
#define SCR_DOOR 1
#define NORMAL   2
#define ITEM     3
#define ELEVATOR 4
#define DEATH    5
#define CUSTOM   6



typedef struct RULE
{
    BOOL isEnabled;
    DIM dim;
    COLOR color;
    R_TYPE ruleType;
    int eventid;
} RULE;

typedef RULE RULEARRAY[50];

void setRuleColor(RULE *rule, COLOR color);
// RULE setRule(DIM dim, COLOR color);
void disableRule(RULE *rule);
void enableRule(RULE *rule);
void initRules(ROOM room, RULEARRAY R, int *nR);
void strToAnsi(COLOR id);