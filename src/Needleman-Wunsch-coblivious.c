#include <stdio.h>

#include "Needleman-Wunsch-coblivious.h"
#include "characters_to_base.h" /* mapping from char to base */

char *x, *y;
int m, n;
static long *prev, *curr, *memo;
static int i, j, idx;

static inline void initialize_memo() {
    memo[m] = 0;
    for (i = m - 1; i >= 0; i--) {
        memo[i] = (isBase(x[i]) ? INSERTION_COST : 0) +
                  memo[i + 1]; // i == m and j < n
    }
}

static inline void swap() {
    long *temp = curr;
    curr = prev;
    prev = temp;
}

static inline void initialize_prev_using_memo() {
    prev[idx] = (isBase(y[j]) ? INSERTION_COST : 0) + memo[m]; // i == m and j < n
    idx--;
    j--;
}

static inline void initialize_prev() {
    for (; idx >= 0 && j >= 0; idx--, j--) {
        prev[idx] = (isBase(y[j]) ? INSERTION_COST : 0) +
                    prev[idx + 1]; // i == m and j < n
    }
}

static inline void compute_current_using_memo() {
    if (!isBase(x[i])) { // β( xi ) = 0
        ManageBaseError(x[i]);
        curr[idx] = prev[idx];
    } else if (!isBase(y[j])) { // β( yj ) = 0
        ManageBaseError(y[j]);
        curr[idx] = memo[i];
    } else {
        curr[idx] = 2 + memo[i]; // 2 + φ(i, j + 1)
        long sd_case = 2 + prev[idx];  // 2 + φ(i + 1, j)
        if (curr[idx] > sd_case) {
            curr[idx] = sd_case;
        }
        long trd_case =
                (isUnknownBase(x[i])
                 ? SUBSTITUTION_UNKNOWN_COST
                 : (isSameBase(x[i], y[j]) ? 0 : SUBSTITUTION_COST)) +
                memo[i + 1]; // σxi ,yj + φ(i + 1, j + 1)
        if (curr[idx] > trd_case) {
            curr[idx] = trd_case;
        }
    }
    idx--;
    j--;
}

static inline void compute_current() {
    for (; idx >= 0 && j >= 0; j--, idx--) {
        if (!isBase(x[i])) { // β( xi ) = 0
            ManageBaseError(x[i]);
            curr[idx] = prev[idx];
        } else if (!isBase(y[j])) { // β( yj ) = 0
            ManageBaseError(y[j]);
            curr[idx] = curr[idx + 1];
        } else {
            curr[idx] = 2 + curr[idx + 1]; // 2 + φ(i, j + 1)
            long sd_case = 2 + prev[idx];  // 2 + φ(i + 1, j)
            if (curr[idx] > sd_case) {
                curr[idx] = sd_case;
            }
            long trd_case =
                    (isUnknownBase(x[i])
                     ? SUBSTITUTION_UNKNOWN_COST
                     : (isSameBase(x[i], y[j]) ? 0 : SUBSTITUTION_COST)) +
                    prev[idx + 1]; // σxi ,yj + φ(i + 1, j + 1)
            if (curr[idx] > trd_case) {
                curr[idx] = trd_case;
            }
        }
    }
}

static inline void set_memo() {
    memo[i + 1] = prev[0];
}

void EditDistance_NW_Coblivious_rec(int n_b, int n_e) {
    int diff = n_e - n_b + 1;
    if (diff > S) {
        int half = (n_e - n_b) / 2;
        EditDistance_NW_Coblivious_rec(n_b + half + 1, n_e);
        EditDistance_NW_Coblivious_rec(n_b, n_b + half);
    } else {
        j = n_e;
        idx = diff - 1;
        initialize_prev_using_memo();
        initialize_prev();
        for (i = m - 1; i >= 0; i--) {
            j = n_e;
            idx = diff - 1;
            compute_current_using_memo();
            compute_current();
            set_memo();
            swap();
        }
        set_memo();
    }
}

long EditDistance_NW_Coblivious(char *A, size_t lengthA, char *B, size_t lengthB) {
    _init_base_match();

    /* Set x, y, n and m such that x is the longest string */
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

    prev = malloc(S * sizeof(long));
    if (!prev) {
        fprintf(stderr, "EditDistance_NW_Caware: malloc of prev\n");
    }

    curr = malloc(S * sizeof(long));
    if (!curr) {
        fprintf(stderr, "EditDistance_NW_Caware: malloc of curr\n");
    }

    memo = malloc((m + 1) * sizeof(long));
    if (!memo) {
        fprintf(stderr, "EditDistance_NW_Caware: malloc of memo\n");
    }

    initialize_memo();
    EditDistance_NW_Coblivious_rec(0, n - 1);

    long ans = prev[0];
    free(curr);
    free(prev);
    free(memo);
    return ans;
}
