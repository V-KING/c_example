#ifndef __SelectServer_H
#define __SelectServer_H

/* for c++ include */


#define MAXLINE                 1024
#define CLIENTS_SIZE            2

typedef void(*tfpIrpMsgDo)(int fd,unsigned char *buf, int len);

class SelectServer {
private:
//     tfpIrpMsgDo IrpMsgDo;
    void(*IrpMsgDo)(int fd,unsigned char *buf, int len);
    int port;
    
public:
    int count_client;
    int MaxClient;

public:
    SelectServer(int port);
    void run();
    void setIrpMsgDo(void(*IrpMsgDo)(int fd, unsigned char *buf, int len));
    void setMaxConnetion(int MaxClient);
};


/* for C */
#ifdef __cplusplus
extern "C" {
#endif
/* function for C */
#ifdef __cplusplus
}
#endif

#endif
