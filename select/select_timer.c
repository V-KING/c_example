#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <time.h>
#include <stdarg.h>
int main()    
{    
	struct timeval tv;    

	while(1)  
	{  
		tv.tv_sec = 1;  // 定时1秒  
		tv.tv_usec = 0;    

		switch(select(0, NULL, NULL, NULL, &tv))   
		{  
		case -1:  // 错误  
			printf("Error!\n");  
			break;  
		case 0: //超时  
			printf("timeout expires.\n");  
			break;  
		default:  
			printf("default\n");  
			break;  
		}  
	}  

	return 0;    
}    

