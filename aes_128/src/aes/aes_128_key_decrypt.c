#include "aes_128.h"
#include <stdio.h>

//////////////////////////////////
//
//	AES DECRYPT KEY SCHEDULE
//
//////////////////////////////////

void	aes_128_key_decrypt(const uint8_t *key, aes_ctx_t *ctx)
{
	aes_ctx_t		tmp;
	__m128i			*tmp_key_sched = (__m128i *)tmp.dec_schedule;
	__m128i			*dec = (__m128i *)ctx->dec_schedule;

	if (!key || !ctx)
		return ;

	aes_128_key_expansion(key, tmp.dec_schedule);

	for (int x = 0; x < AES_128_NROUND; x++)
		print_m128i_with_string("KEY EXPANSION IN FUNC", tmp_key_sched[x]);

	printf("\n\n");
	
	dec[AES_128_ECB] = tmp_key_sched[0];
	dec[AES_128_ECB - 1] = _mm_aesimc_si128(tmp_key_sched[1]);
	dec[AES_128_ECB - 2] = _mm_aesimc_si128(tmp_key_sched[2]);
	dec[AES_128_ECB - 3] = _mm_aesimc_si128(tmp_key_sched[3]);
	dec[AES_128_ECB - 4] = _mm_aesimc_si128(tmp_key_sched[4]);
	dec[AES_128_ECB - 5] = _mm_aesimc_si128(tmp_key_sched[5]);
	dec[AES_128_ECB - 6] = _mm_aesimc_si128(tmp_key_sched[6]);
	dec[AES_128_ECB - 7] = _mm_aesimc_si128(tmp_key_sched[7]);
	dec[AES_128_ECB - 8] = _mm_aesimc_si128(tmp_key_sched[8]);
	dec[AES_128_ECB - 9] = _mm_aesimc_si128(tmp_key_sched[9]);
	dec[0] = tmp_key_sched[AES_128_ECB];

	for (int i = 0; i < AES_128_NROUND; i++)
		print_m128i_with_string("DEC KEY IN FUNC", dec[i]);
}
