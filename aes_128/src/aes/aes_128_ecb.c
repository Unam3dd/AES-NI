#include "aes_128.h"

//////////////////////////////////
//
//	AES 128 ECB (Electronics code Books)
//
//////////////////////////////////

int	aes_128_ecb_enc(const uint8_t *in, uint8_t *out, size_t length, char *key, uint8_t ivec[16])
{
	if (!in || !out || !key || !length)
		return (1);

	(void)ivec;
	__m128i	tmp;
	int i, j;
	length >>= 4;
	for (i = 0; i < (int)length; i++)
	{
		tmp = _mm_loadu_si128(&((__m128i*)in)[i]);
		tmp = _mm_xor_si128(tmp, ((__m128i *)key)[0]); // First xor per block
		for (j = 1; j < AES_128_NROUND; j++)
			tmp = _mm_aesenc_si128(tmp, ((__m128i *)key)[j]);
		tmp = _mm_aesenclast_si128(tmp, ((__m128i *)key)[j]); // Last round without MixColumns transformation
		_mm_storeu_si128(&((__m128i *)out)[i], tmp);
	}
	return (0);
}

int	aes_128_ecb_dec(const uint8_t *in, uint8_t *out, size_t length, char *key, uint8_t ivec[16])
{
	if (!in || !out || !length || !key)
		return (1);
	
	(void)ivec;
	__m128i	tmp;
	int	i, j;
	length >>= 4;
	for (i = 0; i < (int)length; i++)
	{
		tmp = _mm_loadu_si128(&((__m128i *)in)[i]);
		tmp = _mm_xor_si128(tmp, ((__m128i *)key)[0]);
		for (j=1; j < AES_128_NROUND; j++)
			tmp = _mm_aesdec_si128(tmp, ((__m128i *)key)[j]);
		tmp = _mm_aesdeclast_si128(tmp, ((__m128i *)key)[j]);
		_mm_storeu_si128(&((__m128i *)out)[i], tmp);
	}
	return (0);
}
