#include "aes_128.h"

const	aes_mod_t	aes_table[AES_N_MOD] = {
	{ AES_128_ECB, aes_128_ecb_enc, aes_128_ecb_dec},
	{ 0, NULL, NULL }
};
