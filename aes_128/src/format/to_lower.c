#include "aes_128.h"

//////////////////////////////////
//
//			TO LOWER
//
//////////////////////////////////

uint8_t	*to_lower(uint8_t *data)
{
	uint8_t	*tmp = NULL;

	if (!data)
		return (NULL);
	tmp = data;
	while (*tmp) {
		*tmp = (*tmp >= 'A' && *tmp <= 'Z') ? (*tmp ^ 0x20) : *tmp;
		tmp++;
	}
	return (data);
}
