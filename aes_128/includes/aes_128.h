#ifndef AES_128_H
#define AES_128_H

//////////////////////////////////
//
//			INCLUDES
//
//////////////////////////////////

#include <stddef.h>
#include <stdint.h>

//////////////////////////////////
//
//			TYPEDEFS
//
//////////////////////////////////

typedef struct	aes_ctx_t 	aes_ctx_t;
typedef struct 	aes_buf_t	aes_buf_t;
typedef enum	aes_mod_t	aes_mod_t;

//////////////////////////////////
//
//			ENUM
//
//////////////////////////////////

enum aes_mod_t
{
	AES_128_ECB,
	AES_128_CBC
};

//////////////////////////////////
//
//			STRUCT
//
//////////////////////////////////

struct	aes_buf_t
{
	union {
		uint8_t	*ui8_buf;	// Pointer to the buffer
		char	*buf;		// Pointer to the buffer with char *format
	};
	union {
		int		idx;	// position on buffer
		size_t	len;	// Char writed into the buf
	};
	union {
		size_t	capacity;	// get size of buffer
		size_t	size;		// Same as above
	};
};

struct aes_ctx_t
{
	uint8_t		mod;
};

//////////////////////////////////
//
//			ASSEMBLY PART
//
//////////////////////////////////

__uint128_t	aes_encrypt_block(uint8_t *data, uint8_t *key);
void		xor_xmm_registers(void);
void		key_schedule_registers(char *key, size_t len);

//////////////////////////////////
//
//			CIPHER
//
//////////////////////////////////

int	aes_cipher(aes_ctx_t *a, aes_buf_t *data, aes_buf_t *out, uint8_t *key);

//////////////////////////////////
//
//			UNCIPHER
//
//////////////////////////////////

int	aes_uncipher(aes_ctx_t *a, aes_buf_t *data, aes_buf_t *out, uint8_t *key);

//////////////////////////////////
//
//			HEX ENCODE
//
//////////////////////////////////

uint8_t	*hex_encode(uint8_t	*data, uint8_t *out, size_t d_len, size_t o_len);
uint8_t	*hex_decode(uint8_t *data, uint8_t *out, size_t d_len, size_t o_len);

//////////////////////////////////
//
//			FORMAT
//
//////////////////////////////////

uint8_t	*to_lower(uint8_t *data);
uint8_t	*to_upper(uint8_t *data);

#endif
