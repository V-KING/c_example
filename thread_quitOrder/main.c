#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>

#if 0
#define print_dbg(fmt, arg...)
#define print_info(fmt, arg...)
#define print_err(fmt, arg...)
#else
#define print_dbg(fmt, arg...)      printf("\033[36m[DBG][%s: %s:%d]"fmt, __FILE__, __FUNCTION__, __LINE__, ##arg)
#define print_info(fmt, arg...)     printf("\033[32m[INFO][%s: %s:%d]"fmt, __FILE__, __FUNCTION__, __LINE__, ##arg)
#define print_err(fmt, arg...)      printf("\033[31m[ERR][%s: %s:%d]"fmt, __FILE__, __FUNCTION__, __LINE__, ##arg)
#define print_pAddr(p1, p2)         printf("\033[37m[Addr compare][%s: %s:%d][0x%x :: 0x%x]\n", __FILE__, __FUNCTION__, __LINE__, p1,p2)
#endif

#ifdef INVG_RELEASE
#define print_dbg(fmt, arg...)
#define print_info(fmt, arg...)
#define print_err(fmt, arg...)
#define print_pAddr(p1, p2)
#endif


pthread_t pid1;
pthread_t pid2;

void *thread_fun2(void *arg){
    pthread_detach(pthread_self());
    print_info("pid = %d\n",*((int *)arg));
    sleep(5);
    print_info("pid2 quit\n");
}

void *thread_fun1(void *arg){
    pthread_detach(pthread_self());
    print_info("pid = %d\n",*((int *)arg));
    
    int err2 = pthread_create(&pid2, NULL , thread_fun2, &pid2);
    if (err2 < 0){
        print_err("Can't create thread: %s\n", strerror(errno));
    }
    
    //sleep(1);
    print_info("pid1 quit\n");
}



int main(int argc, const char *argv[])
{
    int err = pthread_create(&pid1, NULL , thread_fun1, &pid1);
    if (err < 0){
        print_err("Can't create thread: %s\n", strerror(errno));
    }
//     while(1);
    
    /*
     * TODO: if the real main thread is exit, program will exit too
     * It's mean that all the thread will exit*/
    pthread_join(pid1, NULL);
    while(1);
    return 0;
}
