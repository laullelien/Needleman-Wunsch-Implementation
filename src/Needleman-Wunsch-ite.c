#include "Needleman-Wunsch-ite.h"
#include "characters_to_base.h" /* mapping from char to base */

long EditDistance_NW_Ite(char *A, size_t lengthA, char *B, size_t lengthB) {
    _init_base_match();
    char *x, *y;
    int n, m;

    /* Set x, y, n and m such that x is the longest string*/
    if (lengthA < lengthB) {
        x = B;
        m = lengthB;
        y = A;
        n = lengthA;
    } else {
        x = A;
        m = lengthA;
        y = B;
        n = lengthB;
    }

    /* arrays used to store and compute values of phi(i, j) for 0 <= j <= n
     * and 2 values of i */
    long prev[n + 1];
    long curr[n + 1];
    long *p_prev = prev;
    long *p_curr = curr;

    // Sets the first line
    prev[n] = 0;
    for (int j = n - 1; j >= 0; j--) {
        prev[j] = (isBase(y[j]) ? INSERTION_COST : 0) +
                  prev[j + 1]; // i == m and j < n
    }

    // Computes the other n lines
    for (int i = m - 1; i >= 0; i--) {
        p_curr[n] =
            (isBase(x[i]) ? INSERTION_COST : 0) + p_prev[n]; // i < m and j == n
        for (int j = n - 1; j >= 0; j--) {
            if (!isBase(x[i])) { // β( xi ) = 0
                ManageBaseError(x[i]);
                p_curr[j] = p_prev[j];
            } else if (!isBase(y[j])) { // β( yj ) = 0
                ManageBaseError(y[j]);
                p_curr[j] = p_curr[j + 1];
            } else {
                p_curr[j] = 2 + p_curr[j + 1]; // 2 + φ(i, j + 1)
                long dx_cas = 2 + p_prev[j];   // 2 + φ(i + 1, j)
                if (p_curr[j] > dx_cas) {
                    p_curr[j] = dx_cas;
                }
                long trs_cas =
                    (isUnknownBase(x[i])
                         ? SUBSTITUTION_UNKNOWN_COST
                         : (isSameBase(x[i], y[j]) ? 0 : SUBSTITUTION_COST)) +
                    p_prev[j + 1]; // σxi ,yj + φ(i + 1, j + 1)
                if (p_curr[j] > trs_cas) {
                    p_curr[j] = trs_cas;
                }
            }
        }
        long *p_temp = p_prev;
        p_prev = p_curr;
        p_curr = p_temp;
    }
    return p_prev[0];
}
