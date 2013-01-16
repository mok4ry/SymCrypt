#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "main.h"

#define DEFAULT_KEY_BITS (128)
#define TIMESTAMP_LENGTH (10)
#define CRYPT_FILENAME_LENGTH (TIMESTAMP_LENGTH + 6)
#define KEY_FILENAME_LENGTH (TIMESTAMP_LENGTH + 4)

int main( int argc, char *argv[] ) {
  int c, bits = DEFAULT_KEY_BITS, bits_specified = 0, generate = 0;
  char *key_file = NULL, *in_file = NULL, *options = "f:k:b:g";
  char *crypt_out_filename, *key_out_filename;

  extern char *optarg;
  extern int optind, optopt;

  while ( (c = getopt( argc, argv, options )) != -1 ) {
    switch ( c ) {
      case 'k':     // specify key file
        key_file = optarg;
        break;
      case 'b':     // specify number of bits for generated key
        bits = atoi( optarg );
        bits_specified = 1;
        break;
      case 'f':     // specify file to encrypt/decrypt
        in_file = optarg;
        break;
      case 'g':     // generate a new key
        generate = 1;
        break;
      case '?':
        printf( "Error with flag: %c (invalid or argument missing)\n",
          optopt );
        return -1;
      default:
        break;
    }
  }

  validate_args( in_file, key_file, bits_specified, generate );
  generate_filenames( &crypt_out_filename, &key_out_filename );

  if ( key_file != NULL ) {
    crypt_to_file( in_file, key_file, crypt_out_filename );
  } else if ( in_file != NULL ) {
    generate_key_and_crypt(
      in_file, bits, crypt_out_filename, key_out_filename );
  } else {
    generate_and_store_key( bits, key_out_filename );
  }

}

void generate_filenames( char **crypt_out, char **key_out ) {
  *crypt_out = malloc( CRYPT_FILENAME_LENGTH + 1 );
  *key_out = malloc( KEY_FILENAME_LENGTH + 1 );

  srand(time(NULL));
  int rand_num = rand();
  sprintf( *crypt_out, "%d", rand_num );
  sprintf( *key_out, "%d", rand_num );

  strcat( *crypt_out, ".crypt" );
  strcat( *key_out, ".key" );
}

void crypt_to_file( char *in_file, char *key_file, char *crypt_out ) {
  KEY *key = get_key_from_file( key_file );
  crypt_to_file_with_key( slurp(in_file), key, crypt_out );
  printf( "Saved crypted data to: %s\n", crypt_out );
}

void generate_key_and_crypt(
    char *in_file, int bits, char *crypt_out, char *key_out ) {
  KEY *key = generate_key(bits);
  crypt_to_file_with_key( slurp(in_file), key, crypt_out );
  write_to_file( key->key_chars, key_out );
  printf( "Saved %d-bit key to: %s\n", ( bits / 8 ) * 8, key_out );
  printf( "Saved crypted data to: %s\n", crypt_out );
}

void generate_and_store_key( int bits, char *key_out ) {
  write_to_file( generate_key_string(bits), key_out );
  printf( "Saved %d-bit key to: %s\n", ( bits / 8 ) * 8, key_out );
}

void validate_args( char *in_file, char *key_file, int bits_specified,
    int generate ) {
  if ( in_file == NULL && !generate ) {
    puts ( "No file to encrypt/decrypt. Use '-f <filename>' to specify" );
    puts ( "or use '-g' to generate a new key without crypting anything." );
    exit(-1);
  } else if ( key_file != NULL && bits_specified ) {
    puts ( "Key file provided and number of bits specified.");
    puts ( "Number of bits used only for generating new keys." );
    puts ( "These options are mutually exclusive; please pick only one." );
    exit(-1);
  } else if ( key_file != NULL && generate ) {
    puts ( "Key file provided (-k) and generation requested (-g)." );
    puts ( "These options are mutually exclusive; please pick only one." );
    exit(-1);
  }
}

void crypt_to_file_with_key( char *text, KEY *key, char *filename ) {
  write_to_file( crypt_with_key(text, key), filename );
}

void write_to_file( char *content, char *filename ) {
  FILE *out_file = fopen( filename, "wb" );
  fprintf( out_file, "%s", content );
  fclose(out_file);
}

char *slurp( char *filename ) {
  char *file_string;
  FILE *in_file = fopen( filename, "rb" );
  if ( in_file == NULL ) {
    printf( "Error opening file: %s\n", filename );
    exit(-1);
  }

  fseek( in_file, 0L, SEEK_END );
  int s = ftell( in_file );
  rewind( in_file );
  file_string = malloc( s );

  fread( file_string, s, 1, in_file );
  fclose( in_file );

  return file_string;
}
