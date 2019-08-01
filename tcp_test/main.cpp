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
#include "SelectServer.h"

SelectServer *pSelectServer;

void IrpMsgDo(int fd, unsigned char *buf, int len){
    write(fd, buf, len);
    print_dbg("pSelectServer->count_client = %d\n", pSelectServer->count_client);
}

//IO复用并发
int main(int argc, char **argv) {
    pSelectServer = new SelectServer(5084);
    pSelectServer->setIrpMsgDo(IrpMsgDo);
    pSelectServer->setMaxConnetion(2);
    pSelectServer->run();
    return 0;
}

