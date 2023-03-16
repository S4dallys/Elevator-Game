#include "E_string.h"
#include "color.h"
#include "dim.h"
#include "bool.h"

typedef struct RULE
{
    BOOL isEnabled;
    DIM dim;
    COLOR color;
} RULE;

void setColor(RULE *rule, COLOR color);
RULE createRule(DIM dim, COLOR color);
void disableRule(RULE *rule);
void enableRule(RULE *rule);