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

