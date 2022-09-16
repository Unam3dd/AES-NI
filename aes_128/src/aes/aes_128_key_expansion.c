#include "aes_128.h"

//////////////////////////////////
//
//	KEY EXPANSION | KSA Algorithm
//
//////////////////////////////////

void	aes_128_key_expansion(const uint8_t *key, uint8_t *keysched)
{
	__m128i 	tmp1, tmp2;
	__m128i		*key_schedule = (__m128i *)keysched;

	// Generate derived key for each round with round constant and aeskeygenassist from AES-NI
	// See intel documentation

	tmp1 = _mm_load_si128((__m128i *)key);
	key_schedule[0] = tmp1;

	tmp2 = _mm_aeskeygenassist_si128 (tmp1, 0x1);
	tmp1 = AES_128_ASSIST (tmp1, tmp2);
	key_schedule[1] = tmp1;

	tmp2 = _mm_aeskeygenassist_si128 (tmp1, 0x2);
	tmp1 = AES_128_ASSIST (tmp1, tmp2);
	key_schedule[2] = tmp1;
	
	tmp2 = _mm_aeskeygenassist_si128 (tmp1, 0x4);
	tmp1 = AES_128_ASSIST (tmp1, tmp2);
	key_schedule[3] = tmp1;

	tmp2 = _mm_aeskeygenassist_si128 (tmp1, 0x8);
	tmp1 = AES_128_ASSIST (tmp1, tmp2);
	key_schedule[4] = tmp1;

	tmp2 = _mm_aeskeygenassist_si128 (tmp1, 0x10);
	tmp1 = AES_128_ASSIST (tmp1, tmp2);
	key_schedule[5] = tmp1;

	tmp2 = _mm_aeskeygenassist_si128 (tmp1, 0x20);
	tmp1 = AES_128_ASSIST (tmp1, tmp2);
	key_schedule[6] = tmp1;

	tmp2 = _mm_aeskeygenassist_si128 (tmp1, 0x40);
	tmp1 = AES_128_ASSIST (tmp1, tmp2);
	key_schedule[7] = tmp1;

	tmp2 = _mm_aeskeygenassist_si128 (tmp1, 0x80);
	tmp1 = AES_128_ASSIST (tmp1, tmp2);
	key_schedule[8] = tmp1;

	tmp2 = _mm_aeskeygenassist_si128 (tmp1, 0x1b);
	tmp1 = AES_128_ASSIST (tmp1, tmp2);
	key_schedule[9] = tmp1;

	tmp2 = _mm_aeskeygenassist_si128 (tmp1, 0x36);
	tmp1 = AES_128_ASSIST (tmp1, tmp2);
	key_schedule[10] = tmp1;
}
