SymCrypt (v0.1)
========

A symmetric encryption library and program.


Algorithm
--------
SymCrypt generates keys of variable bit length using a Mersenne Twist implementation
for generation of high-quality pseudorandom numbers.

Encryption is a basic XOR cipher using a given or generated key. A key whose
length is __less__ than the data is repeated until each data character is
encrypted, and a key whose length is __greater__ than the data is only used
until each data character is encrypted.

```
// For an n-byte key 'key' and input text 'txt', produce ciphertext 'enc'

key[0]    key[1]    key[2]  ...  key[n-1]    key[0]    key[1]   ...  etc.
 XOR       XOR       XOR           XOR        XOR       XOR
txt[0]    txt[1]    txt[2]  ...  txt[n-1]    txt[n]   txt[n+1]  ...  etc.
------    ------    ------       --------    ------   --------
enc[0]    enc[1]    enc[2]       enc[n-1]    enc[n]   enc[n+1]  ...  etc.
```

Since this is a symmetric encryption algorithm, feeding it ciphertext will result in plaintext
(provided the same key was used for encryption).

Usage
--------
First produce the binary `symcrypt` by running `make` then run `./symcrypt` with a valid
combination of options as specified below.

NOTE: All output files are given a random integer name followed by either `.key` or `.crypt`
depending on whether the file is a cipher key or crypted text, respectively. For keys and
crypted text generated in the same execution, this integer will be the same.

Options
--------
`-f <filename>`
* Generate a key of default bit length (128) and use it to cipher
the contents of `filename`. Output the new key and resulting text to files.

`-g`
* Generate a key of default bit length (128) and output it to a file.

`-b <bits>`
* Specify the bit length of a key to be generated.

`-k <filename>`
* Use the contents of `filename` as the key when ciphering.

### Examples
```
$ ./symcrypt 
No file to encrypt/decrypt. Use '-f <filename>' to specify
or use '-g' to generate a new key without crypting anything.

$ ./symcrypt -f encrypt.me
Saved 128-bit key to: 1560854361.key
Saved crypted data to: 1560854361.crypt

$ ./symcrypt -f encrypt.me -b 512
Saved 512-bit key to: 1561913202.key
Saved crypted data to: 1561913202.crypt

$ ./symcrypt -g
Saved 128-bit key to: 1562249342.key

$ ./symcrypt -f encrypt.me -k 1561913202.key
Saved crypted data to: 1562787166.crypt

$ ./symcrypt -f encrypt.me -k 1561913202.key -b 512
Key file provided and number of bits specified.
Number of bits used only for generating new keys.
These options are mutually exclusive; please pick only one.
```

Future Plans
------------
* Refactor for more logical code organization
  * Move anything dealing with KEY structs from main to symcrypt.h and symcrypt.c ?
* Encrypt image files


#### Author
* Matt Mokary (mxm6060@rit.edu)

#### Contributors
* ---
