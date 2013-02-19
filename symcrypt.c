/*
 * symcrypt.c
 * 
 * SymCrypt, a symmetric encryption library. Generates keys of variable
 * length and uses them to encrypt/decrypt information.
 *
 * Matt Mokary ( mxm6060@rit.edu )
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "symcrypt.h"
#include "mtwist.h"

#define DEFAULT_KEY_LENGTH (128)

KEY *generate_key( int bits ) {
  if ( ! mt_initialized() ) initialize_with_rand();
  int i, bytes;

  if ( bits % 8 != 0 ) {
    printf( "Invalid number of bits: %d (not divisible by 8)\n", bits );
    printf( "Rounding down to %d-bit key...", (bits / 8) * 8 );
  }

  KEY *key = malloc( sizeof(KEY) );
  key->bytes = bits / 8;
  key->key_chars = malloc( key->bytes + 1 );

  for ( i = 0; i < key->bytes; i++ ) {
    key->key_chars[i] = extract_number() >> 25;  // get last 7 bits ( 0 - 128 )
  }
  key->key_chars[key->bytes] = '\0';
  return key;
}

KEY *generate_key_with_seed( int bits, int seed ) {
  initialize_with_seed( seed );
  return generate_key( bits );
}

KEY *get_key_from_file( char *filename ) {
  char *key_string;
  FILE *key_file = fopen( filename, "rb" );
  if ( key_file == NULL ) {
    printf( "Error opening key file: %s\n", filename );
    exit(-1);
  }

  fseek( key_file, 0L, SEEK_END );
  int s = ftell( key_file );
  rewind( key_file );
  key_string = malloc( s );

  fread( key_string, s, 1, key_file );
  fclose( key_file ); key_file = NULL;

  KEY *key = malloc( sizeof(KEY) );
  key->bytes = s;
  key->key_chars = key_string;
  return key;
}

KEY *get_key_from_raw_string( char *key_string ) {
  KEY *new_key = malloc( sizeof(KEY) );
  new_key->bytes = strlen(key_string);
  new_key->key_chars = malloc( new_key->bytes + 1 );
  strcpy( new_key->key_chars, key_string );
  new_key->key_chars[ new_key->bytes ] = '\0';

  return new_key;
}

char *generate_key_string( int bits ) {
  KEY *key = generate_key( bits );
  char *key_string = key->key_chars;
  free(key);

  return key_string;
}

char *generate_key_string_with_seed( int bits, int seed ) {
  KEY *key = generate_key_with_seed( bits, seed );
  char *key_string = key->key_chars;
  free(key);

  return key_string;
}

char *crypt_with_key( char *msg, KEY *key ) {
  int i, key_index = 0;
  int msg_length = strlen( msg ), key_length = key->bytes;
  char new_char, *crypted_text = malloc( msg_length + 1 );
  strcpy( crypted_text, msg );
  
  for ( i = 0; i < msg_length; i++ ) {
    new_char = crypted_text[i] ^ key->key_chars[key_index];

    // TODO: Fix the bug where key[n] ^ msg[k*n] == 0 ('\0'),
    // which leads to the string being terminated early
    if ( new_char == '\0' ) {
      new_char = '?';
    }

    crypted_text[i] = new_char;

    if ( key_index + 1 == key_length ) {
      key_index = 0;
    } else {
      key_index++;
    }
  }
  
  return crypted_text;
}