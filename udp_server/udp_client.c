
#include<pthread.h>
#include<sys/types.h> 
#include<sys/socket.h> 
#include<unistd.h> 
#include<netinet/in.h> 
#include<arpa/inet.h> 
#include<stdio.h> 
#include<stdlib.h> 
#include<errno.h> 
#include<netdb.h> 
#include<stdarg.h> 
#include<string.h> 

#if 0
#define print_dbg(fmt, arg...)
#define print_info(fmt, arg...)
#define print_err(fmt, arg...)
#define print_pAddr(p1, p2)
#define print_buf(buf, len) 
#else
#define print_dbg(fmt, arg...)      printf("\033[37m[DBG ][%s: %s:%d]"fmt, __FILE__, __FUNCTION__, __LINE__, ##arg);
#define print_info(fmt, arg...)     printf("\033[32m[INFO][%s: %s:%d]"fmt, __FILE__, __FUNCTION__, __LINE__, ##arg);
#define print_err(fmt, arg...)      printf("\033[31m[ERR ][%s: %s:%d]"fmt, __FILE__, __FUNCTION__, __LINE__, ##arg);
#define print_pAddr(p1, p2)         printf("\033[37m[Addr compare][%s: %s:%d][0x%x :: 0x%x]\n", __FILE__, __FUNCTION__, __LINE__, p1,p2);
#define print_buf(buf, len)     do{         \
    int i = 0;                              \
    print_info("");                     \
    printf("buf data = {");                 \
    for(i = 0; i < len; i++)                \
        printf("0x%02x, ", *(buf+i));           \
    printf("}\n");                          \
}while(0)
#endif

#ifdef INVG_RELEASE
#define print_dbg(fmt, arg...)
#define print_info(fmt, arg...)
#define print_err(fmt, arg...)
#define print_pAddr(p1, p2)
#define print_buf(buf, len) 
#endif

#define SERVER_PORT 8888
#define BUFFER_SIZE 1024*2
#define FILE_NAME_MAX_SIZE 512 
int main(int argc, char *argv[]) 
{ 
    /* 服务端地址 */
    struct sockaddr_in server_addr; 
    bzero(&server_addr, sizeof(server_addr)); 
    server_addr.sin_family = AF_INET; 
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    if(argc == 2){
        server_addr.sin_addr.s_addr = inet_addr(argv[1]); 
    }
    server_addr.sin_port = htons(SERVER_PORT); 
    
    /* 创建socket */
    int client_socket_fd = socket(AF_INET, SOCK_DGRAM, 0); 
    if(client_socket_fd < 0) 
    { 
        perror("Create Socket Failed:"); 
        exit(1); 
    } 
    
    /* 输入文件名到缓冲区 */
    uint8_t file_name[FILE_NAME_MAX_SIZE+1]; 
    bzero(file_name, FILE_NAME_MAX_SIZE+1); 
    printf("Please Input File Name On Server:\t"); 
    scanf("%s", file_name); 
    
    uint8_t buffer[BUFFER_SIZE]; 
    bzero(buffer, BUFFER_SIZE); 
    strncpy(buffer, file_name, strlen(file_name)>BUFFER_SIZE?BUFFER_SIZE:strlen(file_name)); 
    

    
    /* 发送文件名 */
    if(sendto(client_socket_fd, buffer, BUFFER_SIZE,0,(struct sockaddr*)&server_addr,sizeof(server_addr)) < 0) 
    { 
        perror("Send File Name Failed:"); 
        exit(1); 
    } 
   
    /* 接收数据 */
    socklen_t addr_length = sizeof(server_addr); 
    bzero(buffer, BUFFER_SIZE); 
    int ret = recvfrom(client_socket_fd, buffer, BUFFER_SIZE,0,(struct sockaddr*)&server_addr, &addr_length);
    print_dbg("recv byte = %d\n", ret);
    if(ret == -1) 
    { 
        perror("Receive Data Failed:"); 
        exit(1); 
    } 
    
    print_buf(buffer, ret); 
    
    close(client_socket_fd); 
    return 0; 
} 
