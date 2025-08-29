#include "StringToRootsCount.h"
#include <stdio.h>
#include <string.h>


bool StringToRootsCount (char line[], TestParameters *test)
{
    if (strcmp(line, "INFINITE_ROOTS") == 0)
    {
        test -> values.number = INFINITE_ROOTS;
        return true;
    }
    if (strcmp(line, "ZERO_ROOTS") == 0)
    {
        test -> values.number = ZERO_ROOTS;
        return true;
    }
    if (strcmp(line, "ONE_ROOT") == 0)
    {
        test -> values.number = ONE_ROOT;
        return true;
    }
    if (strcmp(line, "TWO_ROOTS") == 0)
    {
        test -> values.number = TWO_ROOTS;
        return true;
    }
    return false;
}
