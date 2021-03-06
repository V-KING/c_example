#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include<errno.h>
#include<string.h>
#include<sys/socket.h>
#include<stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>  

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
        printf("0x%02x, ", *((unsigned char*)buf+i));           \
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

int fd_sock;
int                 Num;

int connect_to_server(char* ip, int port){
    print_dbg("Begin..\n");
    int sock = 0;
    
    struct sockaddr_in server;
    bzero(&server,sizeof(server));
    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_family = AF_INET;
    server.sin_port = htons( port );
    //Create socket
    if ((sock = socket(AF_INET , SOCK_STREAM , 0)) == -1){
        print_err("Could not create socket\n");
        return -1;
    }
 
    int opt = 1;
    
    if(setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt)) < 0){
        print_err("setsockopt err\n");
        return -1;
    }
    struct sockaddr_in client;
    bzero(&client,sizeof(client));
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = htonl(INADDR_ANY);
    client.sin_port = htons(12345);
    if (bind(sock,(struct sockaddr *)&client, sizeof(client)) ){
        print_err("bind err\n");
        return -1;
    }
    
    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0) {
        print_err("connect failed: %s\n", strerror(errno));
        return -1;
    }
    
    print_dbg("Connected\n");
    return sock;
}


void *Thread_Recv(void *arg){
    pthread_detach( pthread_self());
    print_dbg("Begin..\n");
    uint8_t buf[2048] = {0};
    
    //int flags = fcntl(fd_sock, F_GETFL, 0);
    //fcntl(fd_sock, F_SETFL, flags|O_NONBLOCK);
 
    while(1) {
        int n = read(fd_sock, buf, 200);
        if(n > 0){
            print_buf(buf, n);
//             n = write(fd_sock, buf, n);
//             if(n < 0){
//                 print_dbg("err: %s\n", strerror(errno)); 
//             }
        }else if(n < 0){
            print_dbg("err: %s\n", strerror(errno)); 
        } else if(n == 0){
            print_dbg("peer close connect\n");
            break;
        }
    }
    
    
}


/*
 * 0x62
 */
void OpenRfPower(){
//     uint8_t sendbuf[11] = {0x55, 0x00, 0x06, 0x06, 0x10, 0x00, 0x00, 0x00, 0x00, 0x11, 0xe6,};// 0x50
    uint8_t sendbuf[11] = {0x55, 0x00, 0x03, 0x09, 0x11, 0x01, 0xb6, 0x47,};// 0x50
    int     sendlen     = 8;
    print_buf(sendbuf, sendlen);
    int n = write(fd_sock, sendbuf, sendlen);
    if(n < 0){
        print_err("err: %s\n", strerror(errno));
    }
}

//stop readtag 0x55, 0x00, 0x02, 0x09, 0x12, 0xb6, 0x47
void StopReadTags(){
    uint8_t sendbuf[7] = {0x55, 0x00, 0x02, 0x09, 0x12, 0xb6, 0x47,};// 0x50
    int     sendlen    = 7;
    print_buf(sendbuf, sendlen);
    int n = write(fd_sock, sendbuf, sendlen);
    if(n < 0){
        print_err("err: %s\n", strerror(errno));
    }
}
void TwoSameFrame(){
    uint8_t sendbuf[14] = {0x55, 0x00, 0x02, 0x09, 0x12, 0xb6, 0x47,  0x55, 0x00, 0x02, 0x09, 0x12, 0xb6, 0x47};// 0x50
    int     sendlen    = 14;
    print_buf(sendbuf, sendlen);
    int n = write(fd_sock, sendbuf, sendlen);
    if(n < 0){
        print_err("err: %s\n", strerror(errno));
    }
}

void send_cmd1Half_cmd2full_1(){
    uint8_t sendbuf[40] = {0x54, /*0x00,0x02, 0x09, 0x12, 0xb6, 0x47,*/ 0x55, 0x00, 0x02, 0x09, 0x12, 0xb6, 0x47,};// 0x50
    int     sendlen    = 8;
    print_buf(sendbuf, sendlen);
    int n = write(fd_sock, sendbuf, sendlen);
    if(n < 0){
        print_err("err: %s\n", strerror(errno));
    }
}
void send_cmd1Half_cmd2full_2(){
    uint8_t sendbuf[40] = {0x55, 0x00,/*0x02, 0x09, 0x12, 0xb6, 0x47,*/ 0x55, 0x00, 0x02, 0x09, 0x12, 0xb6, 0x47,};// 0x50
    int     sendlen    = 9;
    print_buf(sendbuf, sendlen);
    int n = write(fd_sock, sendbuf, sendlen);
    if(n < 0){
        print_err("err: %s\n", strerror(errno));
    }
}

void send_cmd1Half_cmd2full_3(){
    uint8_t sendbuf[40] = {0x55, 0x00, 0x02, /*0x09, 0x12, 0xb6, 0x47,*/ 0x55, 0x00, 0x02, 0x09, 0x99, 0xb6, 0x47,};// 0x50
    int     sendlen    = 10;
    print_buf(sendbuf, sendlen);
    int n = write(fd_sock, sendbuf, sendlen);
    if(n < 0){
        print_err("err: %s\n", strerror(errno));
    }
}
void send_cmd1Half_cmd2full_4(){
    uint8_t sendbuf[40] = {0x55, 0x00, 0x02, 0x09,/* 0x12, 0xb6, 0x47,*/ 0x55, 0x00, 0x02, 0x09, 0x12, 0xb6, 0x47,};// 0x50
    int     sendlen    = 11;
    print_buf(sendbuf, sendlen);
    int n = write(fd_sock, sendbuf, sendlen);
    if(n < 0){
        print_err("err: %s\n", strerror(errno));
    }
}
void send_cmd1Half_cmd2full_5(){
    uint8_t sendbuf[40] = {0x55, 0x00, 0x02, 0x09,0x12,/*0xb6, 0x47,*/ 0x55, 0x00, 0x02, 0x09, 0x12, 0xb6, 0x47,};// 0x50
    int     sendlen    = 12;
    print_buf(sendbuf, sendlen);
    int n = write(fd_sock, sendbuf, sendlen);
    if(n < 0){
        print_err("err: %s\n", strerror(errno));
    }
}


static void *process_input_thread(void *arg){
    pthread_detach(pthread_self());
    while(1){
        printf("###########################\n");
        printf("##  Please select a num:\n");
        printf("##     11: (0912)Stop ReadTags\n");
        printf("##     22: (0911)OpenRfPower\n");
        printf("##     33: 2 same frame\n");
        printf("###########################\n");
        scanf("%d",&Num);
        switch(Num){
            case 11:
                StopReadTags();
                break;
            case 22:
                OpenRfPower();
                break;
            case 33:
                TwoSameFrame();
                break;
            case 1:
                send_cmd1Half_cmd2full_1();
                break;
            case 2:
                send_cmd1Half_cmd2full_2();
                break;
            case 3:
                send_cmd1Half_cmd2full_3();
                break;
            case 4:
                send_cmd1Half_cmd2full_4();
                break;
            case 5:
                send_cmd1Half_cmd2full_5();
                break;
            default:
                break;
        }
    }
}

int main(int argc, char *argv[])
{
    int ret;
    char ip[20] = "127.0.0.1";
    if(argc == 2){
        memcpy(ip, argv[1], strlen(argv[1])+1);
    }
    print_dbg("usage: tcp_client 127.0.0.1\n");
    fd_sock = connect_to_server(ip, 5084);
    if(fd_sock < 0){
        print_err("err: %s\n", strerror(errno)); 
        return -1;
    }
    
    
    pthread_t thread_t_recv; 
    ret = pthread_create(&thread_t_recv,  NULL, Thread_Recv, NULL);

     
    ret = pthread_create(&thread_t_recv,  NULL, process_input_thread, NULL);
    if(ret < 0){
        print_err("process_input_thread create err\n");
    }
     
     
    while(1){
        
    }
    
    
    
    return 0;
}
