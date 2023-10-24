#include <stdio.h>

#include "Needleman-Wunsch-coblivious.h"
#include "characters_to_base.h" /* mapping from char to base */
static long *values;

long EditDistance_NW_Coblivious_rec(char *x, size_t m, char *y, size_t n)
{
    if (m <= S && n <= S)
    {
    }
    else
    {
        if (m > n)
        {
        }
    }
}

long EditDistance_NW_Coblivious(char *x, size_t m, char *y, size_t n)
{
    _init_base_match();
    values = malloc((n + 1) * (m + 1) * sizeof(long));
    if (!values)
    {
        fprintf(stderr, "EditDistance_NW_Caware: malloc of values\n");
    }
    long ans = EditDistance_NW_Coblivious_rec(x, m, y, n);
    free(values);
    return ans;
}
