
#include <stdio.h>
#include <errno.h>



int main(int argc, const char *argv[])
{	
	if (fork() == 0)
	{
		printf("\n##########\n");
		printf("Task \"ls\"");
		printf("\n##########\n");
		if(execl("/bin/ls","ls","-l",NULL)<0)
		{		
			perror("execl error!\n");
			exit(errno);
		}
		exit(0);
	}

	return 0;
}
