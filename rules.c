#include "rules.h"

/*
@param [dim] rule dimensions
@param [color] rule color
@return RULE class instance
*/
RULE setRule(DIM dim, COLOR color)
{
    RULE rule = {1};

    rule.dim = dim;
    setColor(&rule, color);

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
