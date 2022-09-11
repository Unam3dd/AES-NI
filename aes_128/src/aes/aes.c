#include "aes_128.h"

//////////////////////////////////
//
//			AES CIPHER
//
//////////////////////////////////

int	aes_cipher(aes_ctx_t *a, aes_buf_t *data, aes_buf_t *out, uint8_t *key)
{
	if (!a || !data || !out || !key)
		return (1);
	if (a->mod != AES_128_CBC)
		return (1);
	return (0);
}

int	aes_uncipher(aes_ctx_t *a, aes_buf_t *data, aes_buf_t *out, uint8_t *key)
{
	if (!a || !data || !out || !key)
		return (1);
	if (a->mod != AES_128_CBC)
		return (1);
	return (0);
}
