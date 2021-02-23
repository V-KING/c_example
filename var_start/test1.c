#include <sys/ioctl.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

// #define INVG_RELEASE

#ifdef INVG_RELEASE
#define print_dbg(fmt, arg...)
#define print_err(fmt, arg...)  printf(fmt, ##arg);
#define print_info(fmt, arg...) printf(fmt, ##arg);
#define print_pAddr(p1, p2)
#define print_buf(buf, len)
#define pBegin
#define pEnd
#define print_y(fmt, arg...) 
#else
#if 0 
#define print_dbg(fmt, arg...)
#define print_info(fmt, arg...) printf(fmt, ##arg);
#define print_err(fmt, arg...)  printf(fmt, ##arg);
#define print_pAddr(p1, p2)
#define print_buf(buf, len)
#define pBegin
#define pEnd
#define print_y(fmt, arg...)
#else
#define print_dbg(fmt, arg...)      printf("\033[37m[DBG ][%s: %s:%d]"fmt, __FILE__, __FUNCTION__, __LINE__, ##arg);
#define print_info(fmt, arg...)     printf("\033[32m[INFO][%s: %s:%d]"fmt, __FILE__, __FUNCTION__, __LINE__, ##arg);
#define print_err(fmt, arg...)      printf("\033[31m[ERR ][%s: %s:%d]"fmt, __FILE__, __FUNCTION__, __LINE__, ##arg);
#define print_pAddr(p1, p2)         printf("\033[37m[Addr compare][%s: %s:%d][0x%x :: 0x%x]\n", __FILE__, __FUNCTION__, __LINE__, p1,p2);
#define print_y(fmt, arg...)        printf("\033[33m[DBG ][%s: %s:%d]"fmt, __FILE__, __FUNCTION__, __LINE__, ##arg);
#define pBegin                      print_y("## Begin..\n")
#define pEnd                        print_y("## E n d..\n")

#define print_buf(buf, len)     do{         \
    int i = 0;                              \
    print_dbg("");                     \
    printf("buf data = {");                 \
    for(i = 0; i < len; i++)                \
        printf("0x%02x, ", *((unsigned char*)buf+i));           \
    printf("}\n");                          \
}while(0)
#endif

#endif

/*
 * @brief: two kind of cmd: get and set
 *  eg. AT+BAUD;   AT+BAUD=115200
 *  eg. AT+BTSEND=5,hello;   
 *  eg. AT+WFRECV=0,3
 *      AT+WFSEND=0,6,viking
 */
int AT_send(unsigned char *bufcmd,  ...){
    unsigned char buf[50]={0};
    int     n      = 0;
    int     lenPut = 0;
    
    /* AT+ */
    lenPut = strlen("AT+");
    memcpy(&buf[n], "AT+", lenPut);
    n += lenPut;
    
    
    /* cmd: eg. VER */
    lenPut = strlen(bufcmd);
    memcpy(&buf[n], bufcmd, lenPut);
    n += lenPut;
    
    /* 
     * optional for carry param */
    
    va_list vl;
    unsigned char    *str = NULL;
    
    va_start(vl, bufcmd);
    str = va_arg(vl, unsigned char*);
    if(str != NULL){
        print_dbg("%s\n", str);
        lenPut = strlen("=");
        memcpy(&buf[n], "=", lenPut);
        n += lenPut;
        do{
            lenPut = strlen(str);
            memcpy(&buf[n], str, lenPut);
            n += lenPut;
            str = (unsigned char *)va_arg(vl, unsigned char*);
            print_dbg("%s\n",str);
        } while(str != NULL);
    }
    va_end(vl);
    
    print_info("[n ,len, buf] = [%d, %d, %s]\n", n, strlen(buf),buf);
    /*send*/
    
    return 0;
}

int main()
{
	char *a = "ast";
	int b = 224;
	char c = 'x';

    AT_send("BUAD", NULL);
	AT_send("BUAD","115200", NULL);
    AT_send("WFSEND","0", "6", "viking", NULL);
	return 0;
}

