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

    // We compute how many long can fit in a square taking less storage than Z
    int step = 0;
    int size;
    while (size <= Z)
    {
        step++;
        size = (step * sizeof(long));
        size *= size;
    }
    step--;

    // Set first line
    values[m * (n + 1) + n] = 0;
    for (int j = n - 1; j >= 0; j--)
    {
        values[m * (n + 1) + j] = (isBase(y[j]) ? INSERTION_COST : 0) +
                                  values[m * (n + 1) + j + 1]; // i == m and j < n
    }

    // values[i][j] -> values[i * (n + 1) + j]

    for (int I = m / step * step; I >= 0; I -= step)
    {
        int IMAX = (I + step - 1) < m - 1 ? (I + step - 1) : m - 1;
        for (int J = n / step * step; J >= 0; J -= step)
        {
            int JMAX = (J + step - 1) < n ? (J + step - 1) : n;
            for (int i = IMAX; i >= I; i--)
            {
                for (int j = JMAX; j >= J; j--)
                {
                    if (j == n)
                    {
                        values[i * (n + 1) + j] = (isBase(x[i]) ? INSERTION_COST : 0) + values[(i + 1) * (n + 1) + j];
                    }
                    else if (!isBase(x[i]))
                    { // β( xi ) = 0
                        ManageBaseError(x[i]);
                        values[i * (n + 1) + j] = values[(i + 1) * (n + 1) + j];
                    }
                    else if (!isBase(y[j]))
                    { // β( yj ) = 0
                        ManageBaseError(y[j]);
                        values[i * (n + 1) + j] = values[i * (n + 1) + j + 1];
                    }
                    else
                    {
                        values[i * (n + 1) + j] = 2 + values[i * (n + 1) + j + 1]; // 2 + φ(i, j + 1)
                        long sd_case = 2 + values[(i + 1) * (n + 1) + j];          // 2 + φ(i + 1, j)
                        if (values[i * (n + 1) + j] > sd_case)
                        {
                            values[i * (n + 1) + j] = sd_case;
                        }
                        long trd_case =
                            (isUnknownBase(x[i])
                                 ? SUBSTITUTION_UNKNOWN_COST
                                 : (isSameBase(x[i], y[j]) ? 0 : SUBSTITUTION_COST)) +
                            values[(i + 1) * (n + 1) + j + 1]; // σxi ,yj + φ(i + 1, j + 1)
                        if (values[i * (n + 1) + j] > trd_case)
                        {
                            values[i * (n + 1) + j] = trd_case;
                        }
                    }
                }
            }
        }
    }
    long ans = values[0];
    free(values);
    return ans;
}