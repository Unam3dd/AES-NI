#include <stdio.h>
#include <string.h>
#include "aes_128.h"
#include "base64.h"

int main(int ac, char **av)
{
	if (ac < 2)
		return (fprintf(stderr, "usage : %s <data>\n", av[0]), 1);
	
	unsigned char	buf[0x100];
	memset(buf, 0, sizeof(buf));
	unsigned char	decoded[0x100];
	memset(decoded, 0, sizeof(decoded));
	unsigned char	base64_buf[0x100];
	size_t			writed = 0;
	size_t			readed = 0;

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
	base64_encode(av[1], base64_buf, strlen((const char *)av[1]), &writed);
	printf("%s\n", base64_buf);
	show_base64_decode_table();
	memset(decoded, 0, sizeof(decoded));
	readed = writed;
	base64_decode(base64_buf, decoded, readed, &writed);
	printf("%s\n", decoded);
	for (int i = 0; i < strlen((const char *)decoded); i++)
		printf("%d\n", decoded[i]);
	return (0);
}
