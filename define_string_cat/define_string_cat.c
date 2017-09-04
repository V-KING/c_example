/**
 * 宏定义也能连接字符串 
 * */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>




#define READER_TYPE "807"
#define VERSION_STRING_TMP "svn243-DF"
#define ARM9SW_VERSION_INFO		READER_TYPE VERSION_STRING_TMP

int main(int argc, const char *argv[])
{
	char *buf=0;
	buf = (char *)malloc(100);

	int len = strlen(ARM9SW_VERSION_INFO)+1;
	
	memcpy(buf, ARM9SW_VERSION_INFO, len);

	printf("buf = %s\n",buf);	
	printf("ARM9SW_VERSION_INFO = %s\n",ARM9SW_VERSION_INFO);	
	free(buf);
	return 0;
}
