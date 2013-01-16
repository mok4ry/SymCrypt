
#include <fcntl.h>
#include <stdlib.h>
#include "mtwist.h"

#define MAX_LEN (624)
#define UPPER (0x80000000)
#define LOWER (0x7fffffff)

void generate_numbers();

unsigned int state[MAX_LEN];
int mt_index = 0, initialized = 0;

void initialize_with_seed( int seed ) {
  initialized = 1;
  state[0] = seed;
  int i;
  for ( i = 1; i < MAX_LEN; i++ ) {
    state[i] = ( 0x6c078965U * ( state[i-1] ^ ( state[i-1] >> 30 ) ) + 1 ) % 0x100000000U;
  }
}

void initialize_with_rand() {
  initialized = 1;
  int random_data = open( "/dev/random", O_RDONLY );
  int random_seed;
  read( random_data, &random_seed, sizeof(random_seed) );
  close( random_data );
  initialize_with_seed( random_seed );
}

int mt_initialized() {
    return initialized;
}

unsigned int extract_number() {
  if ( mt_index == 0 ) generate_numbers();

  unsigned int num = state[mt_index];
  num = num ^ ( num >> 11 );
  num = num ^ ( (num << 7) & 0x9d2c5680U );
  num = num ^ ( (num << 15) & 0xefc60000U );
  num = num ^ ( num >> 18 );

  mt_index++;
  return num;
}

void generate_numbers() {
  int i;
  for ( i = 0; i < MAX_LEN; i++ ) {
    int num = ( state[i] & UPPER ) + ( state[ (i+1) % MAX_LEN ] & LOWER );
    state[i] = state[ (i+397) % MAX_LEN ] ^ ( num >> 1 );
    if ( num % 2 == 1 ) state[i] = state[i] ^ 0x9908b0dfU;
  }
}
