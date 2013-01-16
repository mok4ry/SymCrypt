/*
 * "The Mersenne twister is a pseudorandom number generator developed in 1997
 * by Makoto Matsumoto and Takuji Nishimura that is based on a matrix linear
 * recurrence over a finite binary field F_2. It provides for fast generation
 * of very high-quality pseudorandom numbers, having been designed specifically
 * to rectify many of the flaws found in older algorithms. Its name derives
 * from the fact that period length is chosen to be a Mersenne prime.
 * ...
 * For a k-bit word length, the Mersenne Twister generates numbers with an
 * almost uniform distribution in the range [0, 2^k - 1]."
 *                                                              - Wikipedia
 *
 * Matt Mokary ( mxm6060@rit.edu )
 */

#ifndef MTWIST_H
#define MTWIST_H

// initialize the generator from a seed
extern void initialize_with_seed( int seed );

// initialize the generator with a random seed
extern void initialize_with_rand();

// check to see if the generator has been initialized
// returns 1 if it has been initialized, 0 otherwise
extern int mt_initialized();

// get a pseudorandom number
extern unsigned int extract_number();

#endif
