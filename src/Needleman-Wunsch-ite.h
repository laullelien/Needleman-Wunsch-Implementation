#include <stdlib.h> /* for size_t */

/*
 * Costs for operations on canonical bases
 * Three  operations: insertion and sustitution of one base by an another 
 * Note= substitution of an unknown base N by another one (known or unknown) as the same cost than substitution between 2 different known bases
 */
/** \def SUBSTITUTION_COST
 *  \brief Cost of substitution of one canonical base by another
 */
#define SUBSTITUTION_COST	1

/** \def SUBSTITUTION_UNKNOWN_COST
 *  \brief Cost of substitution of an unknown base (N) by another one (canonical or unknown)
 */
#define SUBSTITUTION_UNKNOWN_COST	1  /* Cost for sustitition of an Unknown bas N by another on -known or unkown- */ 

/** \def INSERTION_COST
 *  \brief Cost of insertion of a canonical base 
 */
#define INSERTION_COST		2

/********************************************************************************
 * Iterative implementation of NeedlemanWunsch with memoization
 */
/**
 * \fn long EditDistance_NW_Ite(char* A, size_t lengthA, char* B, size_t lengthB);
 * \brief computes the edit distance between A[0 .. lengthA-1] and B[0 .. lengthB-1]
 * \param A  : array of char represneting a genetic sequence A 
 * \param lengthA :  number of elements in A 
 * \param B  : array of char represneting a genetic sequence B
 * \param lengthB :  number of elements in B 
 * \return :  edit distance between A and B }
 *
 * editDistance_NW_Ite is an iterative immplementatioin of Needleman-Wunsch algorithm.
 *
 */
long EditDistance_NW_Ite(char* A, size_t lengthA, char* B, size_t lengthB);