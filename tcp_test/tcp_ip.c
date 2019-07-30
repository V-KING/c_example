#include "debug.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
int tcpserver_starup(int socketno)
{
    int sockfd;

    struct sockaddr_in server_sockaddr;

    /*创建socket连接*/
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        print_err("create socket err: %s", strerror(errno));
        sockfd = -1;
        goto exit;
    }

    int on;
    int ret;
    on = 1;
    ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if(ret < 0){
        print_err("[errno, err] = [%d, %s]\n", errno, strerror(errno));
    }

    /*设置sockaddr_in 结构体中相关参数*/
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(socketno);
    server_sockaddr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(server_sockaddr.sin_zero), 8);

    /*绑定函数bind*/
    if (bind(sockfd, (struct sockaddr *) &server_sockaddr,
            sizeof(struct sockaddr)) == -1)
    {
        print_err("bind err: %s", strerror(errno));
        sockfd = -1;
        goto exit;
    }

    /*调用listen函数*/
    if (listen(sockfd, 5) == -1)
    {
        print_err("listen err: %s", strerror(errno));
        sockfd = -1;
        goto exit;
    }

exit: 
    return sockfd;
}

/*
 * sockfd: server fd
 */
int getClientSockfd(int sockfd)
{
    __pBegin
    struct sockaddr_in client_sockaddr;
    memset(&client_sockaddr, 0, sizeof(struct sockaddr_in));
    socklen_t sin_size = sizeof(struct sockaddr);
    int newc_fd = accept(sockfd, (struct sockaddr *) &client_sockaddr, &sin_size);
    if(newc_fd < 0)
    {
        print_err("accept error: %s\n", strerror(errno));
        return -1;
    }

    print_dbg(" connect from %s\n", inet_ntoa(client_sockaddr.sin_addr));

    __pEnd
    return newc_fd;
}
