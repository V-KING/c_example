/*
 * 对NULL 空指针free多次，就不会报错
 * 安全起见：释放之前
 * 			1. 将那一块地址都设置为NULL, memset(addr, 0, size);
 * 			2. addr = NULL;
 */

#include <stdio.h>
#include <errno.h>

#define TEST0
#define TEST1
#define TEST2
#define TEST3

void freePointer(char *a){
	printf("addr, a=%d\n",a);
	free(a);
	a = NULL;
}
#if 0
int main(int argc, const char *argv[])
{
	char *a=NULL;
	a=(char *)malloc(10);
	strcpy(a,"testtest");
	printf("%s\n",a);

	//destruct
#ifdef TEST0
	memset(a, 0, 10);
#endif


#ifdef TEST1
	a=NULL;
#endif

#ifdef TEST2
	free(NULL);
	free(NULL);
	free(NULL);
#endif
	free(a);
	free(a);


#ifdef TEST3
	char *p = freePointer(a);
	free(p);
#endif

	return 0;
}
#endif
#if 1
int main(int argc, const char *argv[])
{
	char *a=NULL;
	a=(char *)malloc(10);
	strcpy(a,"testtest");
	printf("%s\n",a);

	memset(a, 0, 10);



	freePointer(a);
	printf("1addr, a=%d\n",a);
	free(a);

	return 0;
}
#endif

