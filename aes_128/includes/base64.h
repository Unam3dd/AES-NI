#ifndef BASE64_H
#define BASE64_H

//////////////////////////////////
//
//			INCLUDES
//
//////////////////////////////////

#include <stddef.h>
#include <stdint.h>

//////////////////////////////////
//
//			DEFINES
//
//////////////////////////////////

#define B64_SIZE_TABLE 0x40
#define B64D_SIZE_TABLE (B64_SIZE_TABLE << 2)

//////////////////////////////////
//
//			TABLES
//
//////////////////////////////////

extern const unsigned char	BASE64_TABLE[B64_SIZE_TABLE];
extern const unsigned char	BASE64D_TABLE[B64D_SIZE_TABLE];

//////////////////////////////////
//
//			ENCODER
//
//////////////////////////////////

uint8_t	*base64_encode(uint8_t *data, uint8_t *out, size_t len, size_t *len_enc);

//////////////////////////////////
//
//			DECODER
//
//////////////////////////////////

uint8_t	*base64_decode(uint8_t *data, uint8_t *out, size_t len, size_t *len_dec);
void	show_base64_decode_table(void);

#endif
