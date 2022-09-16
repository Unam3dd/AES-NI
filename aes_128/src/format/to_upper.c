#include "aes_128.h"

//////////////////////////////////
//
//			TO UPPER
//
//////////////////////////////////

uint8_t	*to_upper(uint8_t *data)
{
	uint8_t	*tmp = NULL;

	if (!data)
		return (NULL);
	tmp = data;
	while (*tmp) {
		*tmp = ((*tmp >= 'a' && *tmp <= 'z') ? (*tmp ^ 0x20) : *tmp);
		tmp++;
	}
	*tmp = 0;
	return (data);
}
