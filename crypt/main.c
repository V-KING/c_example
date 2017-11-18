#define _XOPEN_SOURCE
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>



int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		fprintf(stderr, "%s pass salt\n", argv[0]);
		return 1;
	}
	char *encrypted = NULL;

	if((encrypted = crypt(argv[1], argv[2])) == NULL)
	{
		fprintf(stderr, "crypt error:%s\n", strerror(errno));
	}

	printf("[password, salt] = [%s, %s]\n", encrypted, argv[2]);

	return 0;
}

