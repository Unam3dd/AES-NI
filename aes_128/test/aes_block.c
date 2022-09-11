#include "aes_128.h"
#include <stdio.h>
#include <string.h>


#define PRINT_XMM_REGISTER(idx, data) (printf("KEY[%d] : %llx%llx\n", idx, \
			(unsigned long long)(data >> 0x3F), (unsigned long long)(data & 0xFFFFFFFFFFFFFFFF)))

int main(int ac, char **av)
{
	aes_ctx_t	ctx;

	// REGISTERS
	xor_xmm_registers();
	
	//register __uint128_t xmm0 __asm__ ("xmm0");
	//register __uint128_t xmm1 __asm__ ("xmm1");
	//register __uint128_t xmm2 __asm__ ("xmm2");
	//register __uint128_t xmm3 __asm__ ("xmm3");
	//register __uint128_t xmm4 __asm__ ("xmm4");
	//register __uint128_t xmm5 __asm__ ("xmm5");
	//register __uint128_t xmm6 __asm__ ("xmm6");
	//register __uint128_t xmm7 __asm__ ("xmm7");
	//register __uint128_t xmm8 __asm__ ("xmm8");
	//register __uint128_t xmm9 __asm__ ("xmm9");
	//register __uint128_t xmm10 __asm__ ("xmm10");
	//register __uint128_t xmm11 __asm__ ("xmm11");
	//register __uint128_t xmm12 __asm__ ("xmm12");
	//register __uint128_t xmm13 __asm__ ("xmm13");
	//register __uint128_t xmm14 __asm__ ("xmm14");
	//register __uint128_t xmm15 __asm__ ("xmm15");

	if (ac < 2)
		return (1);
	ctx.mod = AES_128_CBC;

	key_schedule_registers(av[1], strlen(av[1]));

	__uint128_t	block = aes_encrypt_block((uint8_t *)av[2], (uint8_t *)av[1]);

	PRINT_XMM_REGISTER(0, block);
	
	return (0);
}
