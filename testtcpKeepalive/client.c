#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <linux/tcp.h>

#define PORT 3333
#define MAXLINE 4096

int main(int argc,char ** argv){
    int sockfd, num;
    char buff[MAXLINE];
    struct hostent *he;
    struct sockaddr_in server;
    if(argc != 2){
        printf("Usage: ./<IP Address>\n");
        exit(1);
    }
    he = gethostbyname(argv[1]);
    if(he == NULL){
        printf("gethostbyname error\n");
        exit(1);
    }
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd == -1){
        printf("socket error\n");
        exit(1);
    }
    
    /**/
    int keepAlive = 1; // 开启keepalive属性
    int keepIdle = 60; // 如该连接在60秒内没有任何数据往来,则进行探测 
    int keepInterval = 5; // 探测时发包的时间间隔为5 秒
    int keepCount = 3; // 探测尝试的次数.如果第1次探测包就收到响应了,则后2次的不再发.
    setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, (void *)&keepAlive, sizeof(keepAlive));
    setsockopt(sockfd, IPPROTO_TCP, TCP_KEEPIDLE, (void*)&keepIdle, sizeof(keepIdle));
    setsockopt(sockfd, IPPROTO_TCP, TCP_KEEPINTVL, (void *)&keepInterval, sizeof(keepInterval));
    setsockopt(sockfd, IPPROTO_TCP, TCP_KEEPCNT, (void *)&keepCount, sizeof(keepCount));

    bzero(&server,sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr = *((struct in_addr*)he->h_addr);
    if(connect(sockfd,(struct sockaddr *)&server,sizeof(server))== -1){
        printf("connect error\n");
        exit(1);
    }
    
    printf("send msg to server: \n");
    fgets(buff,MAXLINE,stdin);
    if(write(sockfd,buff,strlen(buff)) == -1){
        printf("send msg error: %s \n",strerror(errno));
        exit(1);
    }
    close(sockfd);
    return 0;
}
