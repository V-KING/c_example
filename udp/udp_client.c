#include <sys/types.h>
#include <sys/socket.h>
#include<pthread.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
	char buff[512];

	printf("This is a UDP client\n");
	struct sockaddr_in addr;
	int sock;

	if ( (sock=socket(AF_INET, SOCK_DGRAM, 0)) <0)
	{
		perror("socket");
		exit(1);
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1234);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	if (addr.sin_addr.s_addr == INADDR_NONE)
	{
		printf("Incorrect ip address!");
		close(sock);
		exit(1);
	}

	while (1)
	{
		/* 接受用户输入
		 * */
		bzero(buff, 512);
		if (fgets(buff, 511, stdin) == (char *) EOF)//从键盘输入内容
			exit(0);
		if( sendto(sock, buff, strlen(buff), 0, (struct sockaddr *)&addr, sizeof(addr)) < 0){
			perror("sendto");
			close(sock);
			break;
		}else{
			printf("clinet send success!\n");
		}

	}

	return 0;
}

