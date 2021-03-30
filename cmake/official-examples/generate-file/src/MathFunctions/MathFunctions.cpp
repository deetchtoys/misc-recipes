#include "Table.h"
#include "MathFunctions.h"

#include <cstdio>

double mysqrt1(double value)
{
    fprintf(stdout, "mysqrt, ori value: %d\n", static_cast<int>(value));
    return sqrtTable[static_cast<int>(value)];
}
