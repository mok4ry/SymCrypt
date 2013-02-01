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
#include <wchar.h>
#include <unistd.h>
#include "symcrypt.h"
#include "mtwist.h"

#define MAX_CHAR (65536)

KEY *generate_key( int bits, int char_length ) {
  if ( ! mt_initialized() ) initialize_with_rand();
  int i;

  if ( bits % char_length != 0 ) {
    printf( "Invalid number of bits: %d (not divisible by %d)\n", bits,
      char_length );
    printf( "Rounding down to %d-bit key...\n",
      (bits / char_length) * char_length );
  }

  KEY *key = malloc( sizeof(KEY) );
  key->characters = bits / char_length;
  key->key_chars = malloc( sizeof(wchar_t) * (key->characters + 1) );

  for ( i = 0; i < key->characters; i++ ) {
    key->key_chars[i] = extract_number() >> (32 - char_length) % MAX_CHAR;
  }
  key->key_chars[key->characters] = L'\0';
  return key;
}

KEY *generate_key_with_seed( int bits, int seed, int char_length ) {
  initialize_with_seed( seed );
  return generate_key( bits, char_length );
}

KEY *get_key_from_file( char *filename ) {
  wchar_t *key_string, current;

  FILE *key_file = fopen( filename, "rb" );
  if ( key_file == NULL ) {
    printf( "Error opening key file: %s\n", filename );
    exit(-1);
  }

  fseek( key_file, 0L, SEEK_END );
  int s = ftell( key_file ), index = 0;
  rewind( key_file );
  key_string = malloc( sizeof(wchar_t) * (s + 1) );

  while( (current = getwc( key_file )) != -1 ) {
    key_string[index] = current;
  }
  fclose( key_file ); key_file = NULL;
  key_string[s] = L'\0';
  KEY *key = malloc( sizeof(KEY) );
  key->characters = s;
  key->key_chars = key_string;
  return key;
}

wchar_t *generate_key_string( int bits, int char_length ) {
  KEY *key = generate_key( bits, char_length );
  wchar_t *key_string = key->key_chars;
  free(key);

  return key_string;
}

wchar_t *generate_key_string_with_seed( int bits, int seed, int char_length ) {
  KEY *key = generate_key_with_seed( bits, seed, char_length );
  wchar_t *key_string = key->key_chars;
  free(key);

  return key_string;
}

wchar_t *crypt_with_key( wchar_t *msg, KEY *key ) {
  int i, key_index = 0;
  int msg_length = wcslen( msg ), key_length = key->characters;
  wchar_t new_char, *crypted_text = malloc( sizeof(wchar_t)*(msg_length + 1) );
  wcscpy( crypted_text, msg );
  
  for ( i = 0; i < msg_length; i++ ) {
    new_char = crypted_text[i] ^ key->key_chars[key_index];

    // TODO: Fix the bug where key[n] ^ msg[k*n] == 0 ('\0'),
    // which leads to the string being terminated early
    if ( new_char == L'\0' ) {
      new_char = L'?';
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