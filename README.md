# AES-NI
use of the AES-NI instruction set read aes_ni.pdf for more information

# Be careful

be careful words is considered as 32 bits chunks by FIPS197

AES Key expansion : https://www.brainkart.com/article/AES-Key-Expansion_8410/

# AES Key Length

| MOD |   Key Bytes |  NR |
|-----|:-----------:|----:|
| 128 |  16 Bytes   | 10  |
| 192 |  24 Bytes   | 12  |
| 256 |  32 Bytes   | 14  |

# AES-NI ?

Intel has implemented AES with a hardware implementation since March 2008
Reference : https://en.wikipedia.org/wiki/AES_instruction_set

# Why Intel do that ?

The Advanced Encryption Standard (AES) is the Federal Information Processing
Standard for symmetric encryption, and it is defined by FIPS Publication #197 (2001).
From the cryptographic perspective, AES is widely believed to be secure and efficient,
and is therefore broadly accepted as the standard for both government and industry
applications. In fact, almost any new protocol requiring symmetric encryption supports
AES, and many existing systems that were originally designed with other symmetric
encryption algorithms are being converted to AES. Given the popularity of AES and its
expected long term importance, improving AES performance and security has significant
benefits for the PC client and server platforms.
Intel is introducing a new set of instructions beginning with the all new 2010 Intel®
Core™ processor family based on the 32nm Intel® microarchitecture codename
Westmere.

The new architecture has six instructions: four instructions (AESENC, AESENCLAST,
AESDEC, and AESDELAST) facilitate high performance AES encryption and decryption,
and the other two (AESIMC and AESKEYGENASSIST) support the AES key expansion.
Together, these instructions provide full hardware support for AES, offering high
performance, enhanced security, and a great deal of software usage flexibility
The Intel AES New Instructions can support AES encryption and decryption with each
one of the standard key lengths (128, 192, and 256 bits), using the standard block size
of 128 bits (and potentially also other block sizes for generalized variants such as the
RIJNDAEL algorithms). They are well suited to all common uses of AES, including bulk
encryption/decryption using cipher modes such as ECB, CBC and CTR, data
authentication using CBC-MACs (e.g., CMAC), random number generation using
algorithms such as CTR-DRBG, and authenticated encryption using modes such as GCM.
It is believed that these instructions will be useful for a wide range of cryptographic
applications.

This paper provides an overview of the AES algorithm and guidelines for utilizing the
Intel AES New Instructions to achieve high performance and secure AES processing.
Some special usage models of this architecture are also described. This version of the
paper also provides a high performance library for implementing AES in the
ECB/CBC/CTR modes of operation, and discloses, for the first time, the performance
numbers for the provided code.

# FIPS197 ?

Federal Information Processing Standard is a standard in US like ANSI, ISO or IEEE.
https://nvlpubs.nist.gov/nistpubs/fips/nist.fips.197.pdf

# Keyword AES

# Cipher Key of AES

AES is a symmetric (same key to cipher/uncipher) key encryption algorithm.
It uses a cipher key whose length is 128 bits, 192 bits or 256 bits.
The AES algorithm with a cipher key of length 128, 192, 256 bits is denoted AES-128, AES-192, AES-256, respectively check the table as above.

# What is State ?

The process of encryption (decryption) of plaintext (ciphertext) to ciphertext (plaintext)
generates intermediate 128-bit results. These intermediate results are referred to as the
State. For those who do a little assembly keep in mind that the SSE extension on x86 CPUs have 16 registers of 128 bit called xmm register
we will see it a little later when we will test the implementation that intel made.

# What is Data blocks ?

AES operates on an input data block of 128 bits and its output is also a data block of
128 bits.

# Round Keys ?

AES-128, AES192, and AES-256 algorithms expand the cipher key to 10, 12, and 14
round keys, respectively.
The length of each round key is 128 bits.
The algorithm for deriving the round keys from the cipher key is the called the AES Key Expansion.

# AddRound Keys ?

AddRoundKey is a (128-bit, 128-bit) -> 128-bit transformation, which is defined as the
bit-wise xor of its two arguments.
In the AES flow, these arguments are the State and the round key. AddRoundKey is its own inverse.

# Counting the Rounds and the Round Keys ?

The AES algorithm starts with a whitening step, implemented by XOR-ing the input data
block with the first 128 bits of the cipher key. These 128 bits are the whitening key. The
algorithm continues with 10/12/14 rounds, each one using another round key. When
counting this way, the rounds and the round keys are counted from 1 to 10/12/14,
accordingly. However, sometimes the whitening step is also referred to as “Round 0”,
and the corresponding 128 bits of the whitening key are referred to as Round Key 0. In
that case, the count of the AES rounds and the round keys starts from 0 to 10/12/14.
We use these conventions interchangeably.

# What is S-Box ?

In cryptography, an S-box (substitution-box) is a basic component of symmetric key algorithms which performs substitution.
In block ciphers, they are typically used to obscure the relationship between the key and the ciphertext, thus ensuring Shannon's property of confusion. Mathematically, an S-box is a vectorial Boolean function.[1]
In general, an S-box takes some number of input bits, m, and transforms them into some number of output bits, n, where n is not necessarily equal to m.
An m×n S-box can be implemented as a lookup table with 2m words of n bits each. Fixed tables are normally used, as in the Data Encryption Standard (DES), but in some ciphers the tables are generated dynamically from the key (e.g. the Blowfish and the Twofish encryption algorithms).
is like a substitution table.

Example usage of S-BOX and inverse S-BOX

The S-Box and InvS-Box transformations can also be defined by lookup table as follows.
The input to the lookup tables is a byte B [7-0] where x and y denote its low and high
nibbles: x [3-0] = B [7-4], y [3-0] = B [3-0].The output byte is encoded in the table as
a two digit number in hexadecimal notation. For example, S-Box lookup for the input 85
(x=8; y=5 in hexadecimal notation) yields 97 in hexadecimal notation. InvS-Box lookup
for the input 97 yields 85. we can determine bytes like that : 97 & 0xF for y and 97 >> 4 for x

# Example of S-Box:

S-Box lookup table:

```c
					y
|     	  0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f	|
|	0 63 7c 77 7b f2 6b 6f c5 30 01 67 2b fe d7 ab 76	|
|	1 ca 82 c9 7d fa 59 47 f0 ad d4 a2 af 9c a4 72 c0	|
|	2 b7 fd 93 26 36 3f f7 cc 34 a5 e5 f1 71 d8 31 15	|
|	3 04 c7 23 c3 18 96 05 9a 07 12 80 e2 eb 27 b2 75	|
|	4 09 83 2c 1a 1b 6e 5a a0 52 3b d6 b3 29 e3 2f 84	|
|	5 53 d1 00 ed 20 fc b1 5b 6a cb be 39 4a 4c 58 cf	|
|x	6 d0 ef aa fb 43 4d 33 85 45 f9 02 7f 50 3c 9f a8	|
|	7 51 a3 40 8f 92 9d 38 f5 bc b6 da 21 10 ff f3 d2	|
|	8 cd 0c 13 ec 5f 97 44 17 c4 a7 7e 3d 64 5d 19 73	|
|	9 60 81 4f dc 22 2a 90 88 46 ee b8 14 de 5e 0b db	|
|	a e0 32 3a 0a 49 06 24 5c c2 d3 ac 62 91 95 e4 79	|
|	b e7 c8 37 6d 8d d5 4e a9 6c 56 f4 ea 65 7a ae 08	|
|	c ba 78 25 2e 1c a6 b4 c6 e8 dd 74 1f 4b bd 8b 8a	|
|	d 70 3e b5 66 48 03 f6 0e 61 35 57 b9 86 c1 1d 9e	|
|	e e1 f8 98 11 69 d9 8e 94 9b 1e 87 e9 ce 55 28 df	|
|	f 8c a1 89 0d bf e6 42 68 41 99 2d 0f b0 54 bb 16	|
```

Inversed S-Box lookup table:

```
					y
  	  0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
	0 52 09 6a d5 30 36 a5 38 bf 40 a3 9e 81 f3 d7 fb 
	1 7c e3 39 82 9b 2f ff 87 34 8e 43 44 c4 de e9 cb
	2 54 7b 94 32 a6 c2 23 3d ee 4c 95 0b 42 fa c3 4e
	3 08 2e a1 66 28 d9 24 b2 76 5b a2 49 6d 8b d1 25
	4 72 f8 f6 64 86 68 98 16 d4 a4 5c cc 5d 65 b6 92
	5 6c 70 48 50 fd ed b9 da 5e 15 46 57 a7 8d 9d 84
x	6 90 d8 ab 00 8c bc d3 0a f7 e4 58 05 b8 b3 45 06
	7 d0 2c 1e 8f ca 3f 0f 02 c1 af bd 03 01 13 8a 6b
	8 3a 91 11 41 4f 67 dc ea 97 f2 cf ce f0 b4 e6 73
	9 96 ac 74 22 e7 ad 35 85 e2 f9 37 e8 1c 75 df 6e
	a 47 f1 1a 71 1d 29 c5 89 6f b7 62 0e aa 18 be 1b
	b fc 56 3e 4b c6 d2 79 20 9a db c0 fe 78 cd 5a f4
	c 1f dd a8 33 88 07 c7 31 b1 12 10 59 27 80 ec 5f
	d 60 51 7f a9 19 b5 4a 0d 2d e5 7a 9f 93 c9 9c ef
	e a0 e0 3b 4d ae 2a f5 b0 c8 eb bb 3c 83 53 99 61
	f 17 2b 04 7e ba 77 d6 26 e1 69 14 63 55 21 0c 7d
```

# Details of Each round

1 - One AddRoundkey is applied before the first round
2 - The MixColumns transformation is missing in the last round

| STEP |   Details     |
|------|:-------------:|
|  0   |   State       |
|  1   |   SubBytes    |
|  2   |   ShiftRows   |
|  3   |   MixColumns  |
|  4   |   AddRoundKey |
|  5   |  Output State |
