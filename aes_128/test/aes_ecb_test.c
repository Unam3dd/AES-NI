#include "aes_128.h"
#include "hex.h"
#include <stdio.h>
#include <string.h>
#include <stddef.h>

int main(void)
{
	unsigned char	buf[0x100];
	unsigned char	dec[0x100];
	unsigned char	keys[0x100];
	unsigned char	data[] = "hello world on est la mon gars ouais ouais la 6t";
	unsigned char	keyy[] = "AZTOBD51EFN8QP9C";
	aes_ctx_t		ctx;
	//size_t		len = 0;

	memset(buf, 0, sizeof(buf));
	memset(keys, 0, sizeof(keys));
	memset(dec, 0, sizeof(dec));

	aes_128_key_expansion(keyy, ctx.keys_schedule);
	aes_128_key_decrypt(keyy, &ctx);

	printf("\n\n");

	for (int x = 0; x < AES_128_NROUND; x++)
		print_m128i_with_string("KEY ENC:", ((__m128i *)ctx.keys_schedule)[x]);
	printf("\n");
	printf("\n");

	for (int x = 0; x < AES_128_NROUND; x++)
		print_m128i_with_string("KEY-INV:", (((__m128i *)ctx.dec_schedule)[x]));

	printf("\n\nOutput:\n");

	aes_128_ecb_enc(data, buf, 32, (char *)ctx.keys_schedule, NULL);

	print_m128i_with_string("AES-DATA", (((__m128i *)buf)[0]));
	print_m128i_with_string("AES-DATA", (((__m128i *)buf)[1]));

	aes_128_ecb_dec(buf, dec, 32, (char *)ctx.dec_schedule, NULL);

	print_m128i_with_string("DATA", (((__m128i *)dec)[0]));
	print_m128i_with_string("DATA", (((__m128i *)dec)[1]));


	return (0);
}
