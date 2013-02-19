
#ifndef MAIN_H
#define MAIN_H

#include "symcrypt.h"

// Checks that the arguments given are valid. Prints error message and exits
// with code -1 if any invalid argument combinations are found
extern void validate_args(
  char *in_file, char *key_file, int bits_specified, int generate );

// Create file names for crypt and key output files using rand() seeded with
// current UNIX time
extern int generate_filenames( char **crypt_out, char **key_out );

// Generate a key of the given length and store it in a file named `filename`
extern void generate_and_store_key( int bits, char *key_out );

// Writes `content` to a file named `filename`
extern void write_to_file( char *content, char *filename );

// Cipher contents of `in_file` using key from `key_file` and store the result
// in a file named `crypt_out`
extern void crypt_to_file( char *in_file, char *key_file, char *crypt_out );

// Cipher contents of `in_file` using the given raw key string and store the
// result in a file named `crypt_out`
extern void crypt_to_file_with_key_string( char *in_file, char *key_string,
    char *crypt_out );

// Cipher `text` using `key` and store the result in a file named `filename`
extern void crypt_to_file_with_key( char *text, KEY *key, char *filename );

// Generate a key with specified number of bits and use it to cipher contents
// of `in_file`. Store the generated key in a file named `key_out` and the
// result of the cipher in a file named `crypt_out`.
extern void generate_key_and_crypt(
    char *in_file, int bits, char *crypt_out, char *key_out );

// Returns only the string part of a cipher key
extern char *generate_key_string( int bits );

// Read an entire file into one string
extern char *slurp( char *filename );

#endif