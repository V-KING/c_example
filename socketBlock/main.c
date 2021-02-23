#include<stdio.h>
#include<stdlib.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<netdb.h>
#include<errno.h>
#include "./debug.h"


int main(int argc , char *argv[])
{
    int socket_desc;
    struct sockaddr_in server;
    char *message;
    
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        print_dbg("Could not create socket");
    }
    
    char ip[20] = {0};
    char *hostname = "192.168.7.134";
    struct hostent *hp;
    if ((hp = gethostbyname(hostname)) == NULL)
        return 1;
    //  #define h_addr h_addr_list[0]
    strcpy(ip, inet_ntoa(*(struct in_addr *)hp->h_addr_list[0]));
    
    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_family = AF_INET;
    server.sin_port = htons( 80 );
    
    
    //Connect to remote server
    if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("connect error");
        return 1;
    }
    
    puts("Connected\n");
    
    //Send some data
    message = "GET /?st=1 HTTP/1.1\r\nHost: 192.168.7.134\r\n\r\n";
    if( send(socket_desc , message , strlen(message) , 0) < 0)
    {
        puts("Send failed");
        return 1;
    }
    puts("Data Send\n");
    
    struct timeval timeout = {5, 0};
    setsockopt(socket_desc, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(struct timeval));
    
    //Receive a reply from the server
    //loop
    int size_recv , total_size = 0;
    char chunk[512];
    while(1)
    {
        memset(chunk , 0 , 512); //clear the variable
        if((size_recv =  recv(socket_desc , chunk , 512 , 0) ) == -1)
        {
            if (errno == EWOULDBLOCK || errno == EAGAIN)
            {
                print_dbg("recv timeout ...\n");
                break;
            }
            else if (errno == EINTR)
            {
                print_dbg("interrupt by signal...\n");
                continue;
            }
            else if (errno == ENOENT)
            {
                print_dbg("recv RST segement...\n");
                break;
            }
            else
            {
                print_dbg("unknown error!\n");
                exit(1);
            }
        }
        else if (size_recv == 0)
        {
            print_dbg("peer closed ...\n");
            break;
        }
        else
        {
            total_size += size_recv;
            print_dbg("%s\n" , chunk);
        }
    }
    
    print_dbg("Reply received, total_size = %d bytes\n", total_size);
    
    return 0;
}
