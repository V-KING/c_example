#ifndef __tcp_net_H
#define __tcp_net_H

#ifdef __cplusplus
extern "C" {
#endif
    
int tcpserver_starup(int socketno);
int getClientSockfd(int sockfd);

#ifdef __cplusplus
}
#endif
#endif
