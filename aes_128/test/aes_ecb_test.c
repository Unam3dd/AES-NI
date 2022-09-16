#include "aes_128.h"
#include "hex.h"
#include <stdio.h>
#include <string.h>
#include <stddef.h>

void print_m128i_with_string(char* string,__m128i data)
{
	unsigned char *pointer = (unsigned char*)&data;
	int i;
	
	printf("%-40s[0x",string);
	for (i=0; i<16; i++)
		printf("%02x",pointer[i]);
	printf("]\n");
}


int main(void)
{
	unsigned char	buf[0x100];
	unsigned char	dec[0x100];
	unsigned char	keys[0x100];
	unsigned char	data[] = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";
	unsigned char	keyy[] = "AAAAAAAAAAAAAAAA";
	size_t			len = 0;

	memset(buf, 0, sizeof(buf));
	memset(keys, 0, sizeof(keys));
	memset(dec, 0, sizeof(dec));

	aes_128_key_expansion(keyy, keys);

	for (int x = 0; x < 10; x++)
		print_m128i_with_string("KEY:", (((__m128i *)keys)[x]));

	aes_128_ecb_enc(data, buf, 17, keys, NULL);

	print_m128i_with_string("AES-DATA", (((__m128i *)buf)[0]));
	print_m128i_with_string("DATA", (((__m128i *)dec)[0]));

	aes_128_ecb_dec(buf, dec, 17, keys, NULL);

	print_m128i_with_string("DATA", (((__m128i *)dec)[0]));

	return (0);
}
