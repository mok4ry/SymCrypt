/*
 * Public interface to SymCrypt, a symmetric encryption program.
 *
 * Matt Mokary ( mxm6060@rit.edu )
 */

#ifndef SYMCRYPT_H
#define SYMCRYPT_H

// data structure representing a key used to convert plaintext into ciphertext
// and vice versa
// TODO: change values in the key from chars (8 bits) to short ints (16 bits)
typedef struct crypt_key {
  int characters;
  wchar_t *key_chars;
} KEY;

// Generate a key of the given number of bits.
extern KEY *generate_key( int bits, int char_length );

// Generate a key of the given number of bits, using the given seed to
// initialize the pseudo-random number generator (PRNG)
extern KEY *generate_key_with_seed( int bits, int seed, int char_length );

// Get a KEY struct from the contents of a file
extern KEY *get_key_from_file( char *filename );

// Generate a key of the given number of bits and return the raw key string
extern wchar_t *generate_key_string( int bits, int char_length );

// Generate a key of the given number of bits using the given seed and return
// the raw key string
extern wchar_t *generate_key_string_with_seed(
  int bits, int seed, int char_length );

// Encrypts or decrypts the message (depending on whether plaintext or
// ciphertext is given, respectively) with the given key
extern wchar_t *crypt_with_key( wchar_t *msg, KEY *key );

#endif
