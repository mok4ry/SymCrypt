SymCrypt (v0.1)
========

A symmetric encryption library and program.

Algorithm
--------
SymCrypt generates keys of variable bit length using a Mersenne Twist implementation
for generation of high-quality random numbers.

Encryption is a basic XOR cipher using a given or generated key:

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

Future Plans
------------
* Refactor for more logical code organization
  * Move anything dealing with KEY structs from main to symcrypt.h and symcrypt.c ?
* Encrypt image files


#### Author
* Matt Mokary (mxm6060@rit.edu)

#### Contributors
* ---
