#include <stdio.h>
#include <string.h>
#include "aes_128.h"

int main(int ac, char **av)
{
	if (ac < 2)
		return (fprintf(stderr, "usage : %s <data>\n", av[0]), 1);
	
	unsigned char	buf[0x100];
	unsigned char	decoded[0x100];

	if (!hex_encode((uint8_t *)av[1], buf, strlen((const char *)av[1]), sizeof(buf)))
		return (1);
	printf("Data str : %s | hex (%s)\n", av[1], buf);
	size_t len = strlen((const char *)buf);
	while (len) {
		buf[len] = (buf[len] >= 'A' && buf[len] <= 'F') ? buf[len] ^ 0x20 : buf[len];
		// for fun
		len = ~-len;
	}
	printf("Data lower : %s\n", buf);
	to_upper(buf);
	printf("Data Upper : %s\n", buf);
	to_lower(buf);
	printf("REData Lower : %s\n", buf);
	if (hex_decode(buf, decoded, strlen((const char *)buf), sizeof(decoded)))
		printf("Decoded %s\n", decoded);
	return (0);
}
