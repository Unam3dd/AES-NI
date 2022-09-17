#ifndef AES_128_H
#define AES_128_H

//////////////////////////////////
//
//			INCLUDES
//
//////////////////////////////////

#include <stddef.h>
#include <stdint.h>
#include <wmmintrin.h> // AES-128 key expansion

//////////////////////////////////
//
//			DEFINES
//
//////////////////////////////////

#define AES_128_NROUND 10
#define AES_N_MOD 0x2

//////////////////////////////////
//
//			TYPEDEFS
//
//////////////////////////////////

typedef struct	aes_ctx_t 		aes_ctx_t;
typedef struct 	aes_buf_t		aes_buf_t;
typedef struct	aes_mod_t		aes_mod_t;
typedef enum	aes_mod_flag_t	aes_mod_flag_t;

//////////////////////////////////
//
//			CALLBACK
//
//////////////////////////////////

typedef	int	(*callback_t)(const uint8_t *in, uint8_t *out, size_t length, char *key, uint8_t iv[16]);

//////////////////////////////////
//
//			ENUM
//
//////////////////////////////////

enum aes_mod_flag_t
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
	uint8_t		keys_schedule[0x10 << 4];
	uint8_t		dec_schedule[0x10 << 4];
	uint8_t		mod;
};

struct aes_mod_t
{
	aes_mod_flag_t	mod;
	callback_t		enc;
	callback_t		dec;
};

//////////////////////////////////
//
//			CPUID
//
//////////////////////////////////

#define AES_CPUID_VALUE 0x2000000
#define cpuid(func,ax,bx,cx,dx)\
 __asm__ __volatile__ ("cpuid":\
 "=a" (ax), "=b" (bx), "=c" (cx), "=d" (dx) : "a" (func));

int	check_cpu_support_aes(void);

//////////////////////////////////
//
//			KEY EXPANSION
//
//////////////////////////////////

inline	__m128i AES_128_ASSIST (__m128i tmp1, __m128i tmp2)
{
	__m128i tmp3;

	tmp2 = _mm_shuffle_epi32(tmp2, 0xff); // function started by _ is gcc builtins
	tmp3 = _mm_slli_si128(tmp1, 0x4);
	tmp1 = _mm_xor_si128(tmp1, tmp3);

	tmp3 = _mm_slli_si128(tmp3, 0x4);
	tmp1 = _mm_xor_si128(tmp1, tmp3);
	tmp3 = _mm_slli_si128(tmp3, 0x4);
	tmp1 = _mm_xor_si128(tmp1, tmp3);
	tmp1 = _mm_xor_si128(tmp1, tmp2);
	return (tmp1);
}

//////////////////////////////////
//
//		KEY SCHEDULING
//
//////////////////////////////////

void	aes_128_key_decrypt(const uint8_t *key, aes_ctx_t	*ctx);
void	aes_128_key_expansion(const uint8_t *key, uint8_t *keysched);

//////////////////////////////////
//
//			ECB
//
//////////////////////////////////

int		aes_128_ecb_enc(const uint8_t *in, uint8_t *out, size_t length, char *key, uint8_t iv[16]);
int		aes_128_ecb_dec(const uint8_t *in, uint8_t *out, size_t length, char *key, uint8_t iv[16]);

//////////////////////////////////
//
//			CIPHER
//
//////////////////////////////////

int		aes_cipher(aes_ctx_t *a, aes_buf_t *data, aes_buf_t *out, uint8_t *key);

//////////////////////////////////
//
//			UNCIPHER
//
//////////////////////////////////

int		aes_uncipher(aes_ctx_t *a, aes_buf_t *data, aes_buf_t *out, uint8_t *key);

//////////////////////////////////
//
//		UTILS AES FUNCTIONS
//
//////////////////////////////////

void print_m128i_with_string(char* string, __m128i data);

//////////////////////////////////
//
//		MOD OPERATION TABLE
//
//////////////////////////////////

extern const	aes_mod_t	aes_cb_table[AES_N_MOD];

#endif
