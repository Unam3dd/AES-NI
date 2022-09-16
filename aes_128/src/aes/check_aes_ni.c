#include "aes_128.h"

int	check_cpu_support_aes(void)
{
	unsigned int a,b,c,d;
	cpuid(1, a,b,c,d);
	return (c & 0x2000000);
}
