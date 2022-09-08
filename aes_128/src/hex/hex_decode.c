#include "aes_128.h"

//////////////////////////////////
//
//			HEX DECODE
//
//////////////////////////////////

static unsigned char get_nibble_byte(char c)
{
	return ((c - 0x61 >= 0x0 && c - 0x61 <= 0xF) ? (0xA + (c - 0x61))
			: (c - 0x41 >= 0x0 && c - 0x41 <= 0xF) ? (0xA + (c - 0x41))
			: (c & 0xF)
			);
}

uint8_t	*hex_decode(uint8_t *data, uint8_t *buf, size_t d_len, size_t o_len)
{
	uint8_t	*tmp = NULL;

	if (o_len <= d_len)
		return (NULL);
	if (!data || !buf)
		return (NULL);
	tmp = buf;
	while (d_len) {
		*tmp = get_nibble_byte(*data++);
		*tmp <<= 4;
		*tmp++ |= get_nibble_byte(*data++);
		d_len--;
	}
	*tmp = 0;
	return (buf);
}
