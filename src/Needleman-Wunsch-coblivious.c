#include <stdio.h>

#include "Needleman-Wunsch-coblivious.h"
#include "characters_to_base.h" /* mapping from char to base */

static long *values;
char *x, *y;
int m, n;

void EditDistance_NW_Coblivious_rec(int m_b, int m_e, int n_b, size_t n_e)
{
    int m_diff = (m_e - m_b);
    int n_diff = (n_e - n_b);
    if (m_diff <= S && n_diff <= S)
    {
        for (int i = m_e; i >= m_b; i--)
        {
            for (int j = n_e; j >= n_b; j--)
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
    else
    {
        if (m_diff > n_diff)
        {
            int half_diff = m_diff / 2;
            EditDistance_NW_Coblivious_rec(m_b + half_diff + 1, m_e, n_b, n_e);
            EditDistance_NW_Coblivious_rec(m_b, m_b + half_diff, n_b, n_e);
        }
        else
        {
            int half_diff = n_diff / 2;
            EditDistance_NW_Coblivious_rec(m_b, m_e, n_b + half_diff + 1, n_e);
            EditDistance_NW_Coblivious_rec(m_b, m_e, n_b, n_b + half_diff);
        }
    }
}

long EditDistance_NW_Coblivious(char *A, size_t lengthA, char *B, size_t lengthB)
{
    _init_base_match();
    x = A;
    y = B;
    m = lengthA;
    n = lengthB;
    values = malloc((n + 1) * (m + 1) * sizeof(long));
    if (!values)
    {
        fprintf(stderr, "EditDistance_NW_Caware: malloc of values\n");
    }

    // Set first line
    values[m * (n + 1) + n] = 0;
    for (int j = n - 1; j >= 0; j--)
    {
        values[m * (n + 1) + j] = (isBase(y[j]) ? INSERTION_COST : 0) +
                                  values[m * (n + 1) + j + 1]; // i == m and j < n
    }

    EditDistance_NW_Coblivious_rec(0, m - 1, 0, n);
    long ans = values[0];
    free(values);
    return ans;
}
