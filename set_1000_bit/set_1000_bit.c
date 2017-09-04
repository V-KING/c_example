/**
 * 如何设置一个数组的第1000位的bit
 * 例如：
 *	1. set_bit(int n, uchar *array)
 *	2. clear_bit(int n, uchar *array)
 *	2. test_bit(int n, uchar *array)
 * */
#include <string.h>
#include <stdio.h>
#include <math.h>


#define BITS_PER_ULONG				32
#define DBG_VERSION_ARRAY_SIZE		(1024/ BITS_PER_ULONG)
static unsigned long sysdbg_logout_bitmap[DBG_VERSION_ARRAY_SIZE] = {0};
#define ULONG unsigned long


static void set_bit(unsigned int offset, unsigned long *addr)
{
	//offset=100,最多也就只能移动PER_ULONG_BITS-1, 不管是100&31 还是10000&0x1f最大值也就31, 其他的位相与后为0
	unsigned long mask = 1UL << (offset & (BITS_PER_ULONG - 1));
	printf("mask = %30lu\n", mask);
	unsigned long *p = addr + (offset >> (sizeof(unsigned long) + 1));// >>5 相当于/32
	unsigned long old = *p;
	printf("old  = %30lu\n", old);
	*p = old | mask;
	printf("*p   = %30lu\n\n\n", *p);
	
}

static void clear_bit(unsigned int offset, unsigned long *addr)
{
	unsigned long mask = 1UL << (offset & (BITS_PER_ULONG - 1));
	unsigned long *p = addr + (offset >> (sizeof(unsigned long) + 1));
	unsigned long old = *p;
	*p = old & ~mask;
}


static int test_bit(unsigned int offset, unsigned long *addr)
{
	unsigned long mask = 1UL << (offset & (BITS_PER_ULONG - 1));
	
	unsigned long *p = addr + (offset >> (sizeof(unsigned long) + 1));
	unsigned long old = *p;
	return old & mask;
}

int main(int argc, const char *argv[])
{
	int i=0;
	set_bit(100, sysdbg_logout_bitmap);
	set_bit(11, sysdbg_logout_bitmap);
	for(i=0; i<=100; i++){
 		printf("%.8x\n", sysdbg_logout_bitmap[i]);
	}
	
	printf("100&31          = %lu\n", (100&31));
	printf("1UL<<(100&0x1f) = %lu\n", 1UL<<(100&0x1f));
	printf("(sizeof(unsigned long) + 1) = %lu\n", (sizeof(unsigned long) + 1));

#ifdef RELEASE
	printf("--RELEASE------------------------\n");
	printf("--RELEASE------------------------\n");
	printf("--RELEASE------------------------\n");
	printf("--RELEASE------------------------\n");
#endif

	return 0;
}
