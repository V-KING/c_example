#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <linux//tcp.h>

int main(){

    int s;
    int optval;
    socklen_t optlen=sizeof(optval);
    if((s=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))<0){
        perror("socket()");
        exit(1);    
    }       
   if(getsockopt(s, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen) < 0) {
      perror("getsockopt()");
      close(s);
      exit(EXIT_FAILURE);
   }
   printf("SO_KEEPALIVE is %s\n", (optval ? "ON" : "OFF"));
 
   /* Set the option active */
   optval = 1;
   optlen = sizeof(optval);
   if(setsockopt(s, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen) < 0) {
      perror("setsockopt()");
      close(s);
      exit(EXIT_FAILURE);
   }
   printf("SO_KEEPALIVE set on socket\n");
 
   /* Check the status again */
   if(getsockopt(s, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen) < 0) {
      perror("getsockopt()");
      close(s);
      exit(EXIT_FAILURE);
   }
   printf("SO_KEEPALIVE is %s\n", (optval ? "ON" : "OFF"));
   
   
   int keepAlive = 1; // 开启keepalive属性
   int keepIdle = 60; // 如该连接在60秒内没有任何数据往来,则进行探测 
   int keepInterval = 5; // 探测时发包的时间间隔为5 秒
   int keepCount = 3; // 探测尝试的次数.如果第1次探测包就收到响应了,则后2次的不再发.
   
   setsockopt(s, SOL_SOCKET, SO_KEEPALIVE, (void *)&keepAlive, sizeof(keepAlive));
   setsockopt(s, IPPROTO_TCP, TCP_KEEPIDLE, (void*)&keepIdle, sizeof(keepIdle));
   setsockopt(s, IPPROTO_TCP, TCP_KEEPINTVL, (void *)&keepInterval, sizeof(keepInterval));
   setsockopt(s, IPPROTO_TCP, TCP_KEEPCNT, (void *)&keepCount, sizeof(keepCount));




 
   close(s);
 
   exit(EXIT_SUCCESS);



}
