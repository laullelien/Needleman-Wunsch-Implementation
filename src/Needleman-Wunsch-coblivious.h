#include <stdlib.h> /* for size_t */

/*
 * Costs for operations on canonical bases
 * Three  operations: insertion and substitution of one base by another
 * Note= substitution of an unknown base N by another one (known or unknown) as the same cost than substitution between 2 different known bases
 */
/** \def SUBSTITUTION_COST
 *  \brief Cost of substitution of one canonical base by another
 */
#define SUBSTITUTION_COST 1

/** \def SUBSTITUTION_UNKNOWN_COST
 *  \brief Cost of substitution of an unknown base (N) by another one (canonical or unknown)
 */
#define SUBSTITUTION_UNKNOWN_COST 1 /* Cost for substitution of an Unknown bas N by another on -known or unknown- */

/** \def INSERTION_COST
 *  \brief Cost of insertion of a canonical base
 */
#define INSERTION_COST 2

/** \def S
 *  \brief Threshold under which both string length must be to compute values
 */
#define S 800

/********************************************************************************
 * Cache oblivious implementation of NeedlemanWunsch with memoization
 */
/**
 * \fn long EditDistance_NW_Coblivious(char* A, size_t lengthA, char* B, size_t lengthB);
 * \brief computes the edit distance between A[0 .. lengthA-1] and B[0 .. lengthB-1]
 * \param A  : array of char representing a genetic sequence A
 * \param lengthA :  number of elements in A
 * \param B  : array of char representing a genetic sequence B
 * \param lengthB :  number of elements in B
 * \return :  edit distance between A and B }
 *
 * editDistance_NW_Coblivious is a cache aware implementation of Needleman-Wunsch algorithm.
 *
 */
long EditDistance_NW_Coblivious(char *A, size_t lengthA, char *B, size_t lengthB);