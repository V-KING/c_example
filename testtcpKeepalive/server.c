#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <linux/tcp.h>

#define PORT 3333
#define BACK_LOG 10

int main(){
    int listenfd,connectfd;
    struct sockaddr_in server;
    struct sockaddr_in client;
    pid_t childpid;
    socklen_t addrlen;
    char buff[4096];  
    listenfd = socket(AF_INET,SOCK_STREAM,0);
    if(listenfd == -1){
        perror("socker created failed");
        exit(0);
    }
    

    
    int option;
        option = SO_REUSEADDR;
        setsockopt(listenfd,SOL_SOCKET,option,&option,sizeof(option));
        bzero(&server,sizeof(server));
        server.sin_family = AF_INET;
        server.sin_port = htons(PORT);
        server.sin_addr.s_addr = htonl(INADDR_ANY);
        if(bind(listenfd,(struct sockaddr *)&server,sizeof(server)) == -1){
            perror("Bind error!");
            exit(1);
        }
        if(listen(listenfd,BACK_LOG) == -1){
            perror("listend error");
            exit(1);
        }
    printf("waiting for clinet's request.....\n");
    while(1){
            int n;
            addrlen = sizeof(client);
            connectfd = accept(listenfd,(struct sockaddr*)&client,&addrlen);
            if(connectfd == -1){
                perror("accept error");
                exit(0);
            }else{
                printf("client connected\n");
            }

            
            if((childpid = fork()) == 0){   
                /* keepAlive */
                int keepAlive = 1; // 开启keepalive属性
                int keepIdle = 10; // 如该连接在60秒内没有任何数据往来,则进行探测 
                int keepInterval = 5; // 探测时发包的时间间隔为5 秒
                int keepCount = 3; // 探测尝试的次数.如果第1次探测包就收到响应了,则后2次的不再发.
                setsockopt(connectfd, SOL_SOCKET, SO_KEEPALIVE, (void *)&keepAlive, sizeof(keepAlive));
                setsockopt(connectfd, IPPROTO_TCP, TCP_KEEPIDLE, (void*)&keepIdle, sizeof(keepIdle));
                setsockopt(connectfd, IPPROTO_TCP, TCP_KEEPINTVL, (void *)&keepInterval, sizeof(keepInterval));
                setsockopt(connectfd, IPPROTO_TCP, TCP_KEEPCNT, (void *)&keepCount, sizeof(keepCount));
                close(listenfd);
                printf("client from %s\n",inet_ntoa(client.sin_addr));
                //memset(buff,'\0',sizeof(buff));   
                printf("ready to read\n");
                //while((n = read(connectfd,buff,4096)) > 0){
                while((n = recv(connectfd,buff,4096, 0)) > 0){
                    buff[n] = '\0';
                    printf("recv msg from client: %s\n",buff);  
                }
                if(n<0){
                    printf(" n = %d\n", n);
                    //ETIMEDOUT == 110
                    printf("errno = %d\n", errno);
                }
                printf("end read\n");
                exit(0);
            }else if(childpid < 0)
                printf("fork error: %s\n",strerror(errno));
            close(connectfd);
    }
    return 0;
}
