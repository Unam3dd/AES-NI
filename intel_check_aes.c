#include <stdio.h>

#define cpuid(func,ax,bx,cx,dx)\
 __asm__ __volatile__ ("cpuid":\
 "=a" (ax), "=b" (bx), "=c" (cx), "=d" (dx) : "a" (func));

int Check_CPU_support_AES()
{
 unsigned int a,b,c,d;
 cpuid(1, a,b,c,d);
 return (c & 0x2000000);
}

int main(void)
{
	printf("%x\n", Check_CPU_support_AES());
	return (0);
}
