#include <string.h>
#include "E_string.h"
#include "color.h"
#include "dim.h"
#include "bool.h"

// rule types

#define DOOR     0
#define SCR_DOOR 1
#define NORMAL   2
#define ITEM     3
#define ELEVATOR 4
#define DEATH    5
#define CUSTOM   6


typedef int R_TYPE;

typedef struct RULE
{
    BOOL isEnabled;
    DIM dim;
    COLOR color;
    R_TYPE ruleType;
} RULE;

typedef RULE RULEARRAY[50];

void setRuleColor(RULE *rule, COLOR color);
RULE setRule(DIM dim, COLOR color);
void disableRule(RULE *rule);
void enableRule(RULE *rule);