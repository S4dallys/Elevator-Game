#include "rules.h"
#include "coordinates.h"
#include "E_string.h"

typedef struct OBJECT
{
    DIM dim;
    RULE rules[5];
} OBJECT;