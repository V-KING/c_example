#include "SelectServer.h"
#include <sys/select.h>
#include <sys/ioctl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdlib.h>
#include "debug.h"
#include "tcp_net.h"


SelectServer::SelectServer(int port ) {
    this->port = port;
}
void  SelectServer::setIrpMsgDo(void(*IrpMsgDo)(int fd, unsigned char *buf, int len)){
    this->IrpMsgDo = IrpMsgDo;
}
void  SelectServer::setMaxConnetion(int MaxClient){
    this->MaxClient = MaxClient;
}

void SelectServer::run() {
    int ret;
    int i, maxi, maxfd, listenfd, connfd, sockfd;
    int nready, client[MaxClient];
    ssize_t n;
    fd_set      rset, allset;
    char    buf[MAXLINE];
    socklen_t           clilen;
    struct sockaddr_in  cliaddr, servaddr;
    signal(SIGPIPE, SIG_IGN);

    listenfd = tcpserver_starup(5084);

    maxfd = listenfd;           /* initialize */
    maxi = -1;                  /* index into client[] array */
    for (i = 0; i < MaxClient; i++)
        client[i] = -1;         /* -1 indicates available entry */
    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);

    /* end fig01 */
    for ( ; ; ) {
        rset = allset;      /* structure assignment */
        nready = select(maxfd + 1, &rset, NULL, NULL, NULL);

        if (FD_ISSET(listenfd, &rset)) {    /* new client connection */
            connfd = getClientSockfd(listenfd);
            if (count_client >= MaxClient) {
                print_err("too many clients, count_client = %d, MaxClient = %d\n", count_client, MaxClient);
                close(connfd);
                continue;
            }
            for (i = 0; i < MaxClient; i++) {
                if (client[i] < 0) {
                    client[i] = connfd; /* save descriptor */
                    count_client++;
                    print_dbg("total_clients = %d,client[%d] = %d\n", count_client, i, connfd);
                    break;
                }
            }

            FD_SET(connfd, &allset);    /* add new descriptor to set */
            if (connfd > maxfd)
                maxfd = connfd;         /* for select */
            if (i > maxi)
                maxi = i;               /* max index in client[] array */

            if (--nready <= 0)
                continue;               /* no more readable descriptors */
        }

        for (i = 0; i <= maxi; i++) {   /* check all clients for data */
            if ( (sockfd = client[i]) < 0)
                continue;
            if (FD_ISSET(sockfd, &rset)) {
                n = read(sockfd, buf, MAXLINE);
                if (n == 0) {
                    /*4connection closed by client */
                    close(sockfd);
                    FD_CLR(sockfd, &allset);
                    print_info("close fd = %d\n", sockfd);
                    client[i] = -1;
                    count_client--;
                } else if (n < 0) {
                    print_err("%s\n", strerror(errno));
                } else {
                    //write(sockfd, buf, n);
                    /* function pointer do*/
                    if(IrpMsgDo != NULL){
                        print_dbg("IrpMsgDo ...\n");
                        IrpMsgDo(sockfd, (unsigned char *)buf, n);
                    }else{
                        print_err("please 'setIrpMsgDo()' to a function\n");
                    }
                }
                if (--nready <= 0)
                    break;              /* no more readable descriptors */
            }
        }
    }
}


