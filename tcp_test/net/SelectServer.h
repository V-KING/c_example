#ifndef __SelectServer_H
#define __SelectServer_H

#define MAXLINE                 1024
#define CLIENTS_SIZE            1

class SelectServer {
private:

public:
    int count_client;

public:
    SelectServer(int port);
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
