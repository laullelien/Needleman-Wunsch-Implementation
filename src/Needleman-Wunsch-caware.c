#include <stdio.h>

#include "Needleman-Wunsch-caware.h"
#include "characters_to_base.h" /* mapping from char to base */

long EditDistance_NW_Caware(char *A, size_t lengthA, char *B, size_t lengthB)
{
    _init_base_match();
    char *x, *y;
    int n, m;

    /* Set x, y, n and m such that x is the longest string*/
    if (lengthA < lengthB)
    {
        x = B;
        m = lengthB;
        y = A;
        n = lengthA;
    }
    else
    {
        x = A;
        m = lengthA;
        y = B;
        n = lengthB;
    }

    long *values = malloc((n + 1) * (m + 1) * sizeof(long));
    if (!values)
    {
        fprintf(stderr, "EditDistance_NW_Caware: malloc of values\n");
    }

    return values[0];
}