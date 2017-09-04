#include <stdio.h>  
#include <unistd.h>  
#include <sys/socket.h>  
#include <sys/types.h>  
#include <linux/if_ether.h>  
#include <linux/in.h>  
#include <errno.h>

#define BUFFER_MAX 2048  

int main(int argc, char *argv[])  
{        
	int sock, n_read, eth_type;          
	char buffer[BUFFER_MAX];  
	char  *eth_head;  

// 	if((sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0)  
	if((sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_802_3))) < 0)  
	{  
		fprintf(stdout, "create socket error:%s\n",strerror(errno));  
		exit(0);  
	}  

	while(1)   
	{  
		n_read = recvfrom(sock, buffer, 2048, 0, NULL, NULL);  
		if(n_read < 42)   
		{  
			fprintf(stdout, "Incomplete header, packet corrupt\n");  
			continue;  
		}  

		eth_head = buffer;  
		eth_type=((unsigned char)eth_head[16])*16*16+(unsigned char)eth_head[17];  

		//if(eth_type==0x88ba){    //judge wether the eth_type is iec61850 sv  
// 		if(eth_type==0x0800)
		{    //judge wether the eth_type is iec61850 sv  
			printf("\n----------------IEC61850-9-2 SV---------------------\n");  
			int i=0;  
			for(i=0;i<n_read;i++){  
				printf("%.2X ",(unsigned char)eth_head[i]);  
				if(((i+1)%16)==0) printf("\n");  
			}  
			printf("\n----------------------------------------------------\n");  
		}  
	}  
	printf("exit\n");
}  

