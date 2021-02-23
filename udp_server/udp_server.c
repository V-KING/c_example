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
#include <pthread.h>
#include <semaphore.h>

void printTime(){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    printf("\033[31m%lld ms:",tv.tv_sec*1000 + tv.tv_usec/1000);  //毫秒
}
#if 0
#define print_dbg(fmt, arg...)
#define print_info(fmt, arg...)
#define print_err(fmt, arg...)
#define print_pAddr(p1, p2)
#define print_buf(buf, len) 
#else
#define print_dbg(fmt, arg...)      printTime();printf("\033[37m[DBG ][%s: %s:%d]"fmt, __FILE__, __FUNCTION__, __LINE__, ##arg);
#define print_info(fmt, arg...)     printTime();printf("\033[32m[INFO][%s: %s:%d]"fmt, __FILE__, __FUNCTION__, __LINE__, ##arg);
#define print_err(fmt, arg...)      printTime();printf("\033[31m[ERR ][%s: %s:%d]"fmt, __FILE__, __FUNCTION__, __LINE__, ##arg);
#define print_pAddr(p1, p2)         printTime();printf("\033[37m[Addr compare][%s: %s:%d][0x%x :: 0x%x]\n", __FILE__, __FUNCTION__, __LINE__, p1,p2);
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

#define SERVER_PORT 12800
#define BUFFER_SIZE 1024 
#define FILE_NAME_MAX_SIZE 512 


int                 Num;
int                 server_socket_fd;
struct sockaddr_in  client_addr; 
socklen_t           client_addr_length;

/*
 * 0x62
 */
void QueryUdpMode(){
    uint8_t sendbuf[7] = {0x00,0x03,0x62,0x50,0x00,0xdb,0xae,};// 0x50
    int     sendlen     = 7;
    print_buf(sendbuf, 7);
    int n = sendto(server_socket_fd, sendbuf, sendlen, 0, (struct sockaddr *)&client_addr, client_addr_length);
    if(n < 0){
        print_err("sendto err\n");
        exit(0);
    }
}
/*
 * 0x63
 */
void QueryServerList(){
    uint8_t sendbuf[7] = {0x00,0x03,0x62,0x51,0x00,0x5d,0xad,};// 0x51
    int     sendlen     = 7;
    int n = sendto(server_socket_fd, sendbuf, sendlen, 0, (struct sockaddr *)&client_addr, client_addr_length);
    if(n < 0){
        print_err("sendto err\n");
        exit(0);
    }
}

void QueryConnectProbes(){
    uint8_t sendbuf[7] = {0x00,0x03,0x62,0x52,0x00,0x57,0xad,};// 0x51
    int     sendlen     = 7;
    int n = sendto(server_socket_fd, sendbuf, sendlen, 0, (struct sockaddr *)&client_addr, client_addr_length);
    if(n < 0){
        print_err("sendto err\n");
        exit(0);
    }
}
void QueryIntervalReadTagParam(){
    uint8_t sendbuf[7] = {0x00,0x03,0x62,0x34,0x00,0x83,0xa8,};// 0x51
    int     sendlen     = 7;
    int n = sendto(server_socket_fd, sendbuf, sendlen, 0, (struct sockaddr *)&client_addr, client_addr_length);
    if(n < 0){
        print_err("sendto err\n");
        exit(0);
    }
}

void SetSysConfig_ModeServer(){
    uint8_t sendbuf[8] = {0x00,0x04,0x63,0x50,0x01,0x00,0x3f,0xb1,};//off
    //uint8_t sendbuf[8] = {0x00,0x04,0x63,0x50,0x01,0x01,0xbf,0xb4,};//on
    int     sendlen     = 8;
    int n = sendto(server_socket_fd, sendbuf, sendlen, 0, (struct sockaddr *)&client_addr, client_addr_length);
    if(n < 0){
        print_err("sendto err\n");
        exit(0);
    }
}
void SetSysConfig_ModeClient(){
    //uint8_t sendbuf[8] = {0x00,0x04,0x63,0x50,0x01,0x00,0x3f,0xb1,};//off
    uint8_t sendbuf[8] = {0x00,0x04,0x63,0x50,0x01,0x01,0xbf,0xb4,};//on
    int     sendlen     = 8;
    int n = sendto(server_socket_fd, sendbuf, sendlen, 0, (struct sockaddr *)&client_addr, client_addr_length);
    if(n < 0){
        print_err("sendto err\n");
        exit(0);
    }
}

void SetSysConfig_ServerList(){
    uint8_t sendbuf[25] = {0x00,0x15,0x63,0x51,0x12,0xc0,0xa8,0x01,0xfb,0x32,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x9d,0x83,};//on
    int     sendlen     = 25;
    int n = sendto(server_socket_fd, sendbuf, sendlen, 0, (struct sockaddr *)&client_addr, client_addr_length);
    if(n < 0){
        print_err("sendto err\n");
        exit(0);
    }
}

void SetSysConfig_ConnectProbes(){
    
}
void SetSysConfig_IntervalReadTagParam(){
    
}
void ReadTagsEpc(){
    uint8_t sendbuf[] = {0x00,0x04,0x81,0x81,0x03,0x01,0x15,0xce};//on
    int     sendlen     = 8;
    int n = sendto(server_socket_fd, sendbuf, sendlen, 0, (struct sockaddr *)&client_addr, client_addr_length);
    if(n < 0){
        print_err("sendto err\n");
        exit(0);
    }
}
static void *process_input_thread(void *arg){
    pthread_detach(pthread_self());
    while(1){
        printf("###########################\n");
        printf("##  Please select a num:\n");
        printf("##  *) send: Query sys config\n");
        printf("##          6250: Query is udp client(1) or server(0) mode\n");
        printf("##          6251: Query server list\n");
        printf("##          6252: Query fail to connect times\n");
        printf("##          6234: Query interval read tag parameter\n");
        printf("##  *) send: Set   sys config\n");
        printf("##          63500 SetSysConfig_ModeServer 0\n");
        printf("##          63501 SetSysConfig_ModeClient 1\n");
        printf("##          6351  SetSysConfig_ServerList\n");
        printf("##  64) send: Query tag Operation\n");
        printf("##  65) send: Set   tag Operation\n");
        printf("##  81) send: Read Tags\n");
        printf("###########################\n");
        scanf("%d",&Num);
        switch(Num){
            case 6250:
                print_dbg("send: Query is udp client or server mode\n");
                QueryUdpMode();
                break;
            case 6251:
                print_dbg("send: Query server list\n");
                QueryServerList();
                break;
            case 6252:
                print_dbg("send: Query fail to connect times\n");
                QueryConnectProbes();
                break;
            case 6234:
                QueryIntervalReadTagParam();
                print_dbg("send: Query interval read tag parameter\n");
                break;
            case 63500:
                SetSysConfig_ModeServer();
                print_dbg("send: Query interval read tag parameter\n");
                break;
            case 63501:
                SetSysConfig_ModeClient();
                print_dbg("send: Query interval read tag parameter\n");
                break;
            case 6351:
                SetSysConfig_ServerList();
                print_dbg("send: Query interval read tag parameter\n");
                break;
            case 81:
                ReadTagsEpc();
                print_dbg("send: ReadTags\n");
                break;
        }
    }
}

void AckKeepAlive(){
    /* 
     * send to client
     * */
    uint8_t sendbuf[17] = {0x00,0x0d,0xe5,0x00,0x00,0x00,0x01,0x5A,0x60,0x56,0x59,0x00,0x00,0x00,0x00,0x97,0xa0};
    int     sendlen     = 17;
    int n = sendto(server_socket_fd, sendbuf, sendlen, 0, (struct sockaddr *)&client_addr, client_addr_length);
    //print_dbg("send byte = %d\n", n);
}


int main() 
{ 
    pthread_t tid_input;
    int ret = 0;
    
    ret = pthread_create(&tid_input, NULL, process_input_thread, NULL);
    if (ret < 0){
        return -1;
    }
    
    
    /* 创建UDP套接口 */
    struct sockaddr_in server_addr; 
    bzero(&server_addr, sizeof(server_addr)); 
    server_addr.sin_family = AF_INET; 
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
    server_addr.sin_port = htons(SERVER_PORT); 
    
    /* 创建socket */
    server_socket_fd = socket(AF_INET, SOCK_DGRAM, 0); 
    if(server_socket_fd == -1) { 
        perror("Create Socket Failed:"); 
        exit(1); 
    } 
    
    /* 绑定套接口 */
    if(-1 == (bind(server_socket_fd,(struct sockaddr*)&server_addr,sizeof(server_addr)))) { 
        perror("Server Bind Failed:"); 
        exit(1); 
    } 
    
    /* 数据传输 */
    while(1) {  
        /* 定义一个地址，用于捕获客户端地址 */
        
        client_addr_length = sizeof(client_addr); 
        
        /* 接收数据 */
        char buffer[BUFFER_SIZE]; 
        bzero(buffer, BUFFER_SIZE); 
        int ret = recvfrom(server_socket_fd, buffer, BUFFER_SIZE,0,(struct sockaddr*)&client_addr, &client_addr_length);
        if( ret == -1) { 
            perror("Receive Data Failed:"); 
            exit(1); 
        } 
      
        uint8_t cmdType = buffer[2];
        switch(cmdType){
            case 0xe5:
//                 print_dbg("Recived: keepalive\n");
                AckKeepAlive();
                //print_buf(buffer, ret);
                break;
            case 0x62:
                print_dbg("Recived: Query sys config\n");
                print_buf(buffer, ret);
                break;
            case 0x63:
                print_dbg("Recived: Set   sys config\n");
                print_buf(buffer, ret);
                break;
            case 0x64:
                print_dbg("Recived: Query tag Operation\n");
                print_buf(buffer, ret);
                break;
            case 0x65:
                print_dbg("Recived: Set   tag Operation\n");
                print_buf(buffer, ret);
                break;
            case 0x81:
                print_dbg("Recived: tag Data\n");
                print_buf(buffer, ret);
                break;
            default:
                print_err("Recived: err type\n");
                print_buf(buffer, ret);
                break;
        }
    } 
    
    close(server_socket_fd); 
    print_info("close socket\n");
    return 0; 
    
} 
