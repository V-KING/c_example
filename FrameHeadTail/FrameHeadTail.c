#include <stdio.h>
#include <string.h>

#define MAX_SIZE 1024


#if 0
#define print_dbg(fmt, arg...)
#define print_info(fmt, arg...)
#define print_err(fmt, arg...)
#define print_pAddr(p1, p2)
#define print_buf(buf, len)
#define pBegin
#define pEnd
#define print_y(fmt, arg...)
#else
#define print_y(fmt, arg...)        printf("\033[33m[DBG ][%s: %s:%d]"fmt, __FILE__, __FUNCTION__, __LINE__, ##arg);
#define print_dbg(fmt, arg...)      printf("\033[37m[DBG ][%s: %s:%d]"fmt, __FILE__, __FUNCTION__, __LINE__, ##arg);
#define print_info(fmt, arg...)     printf("\033[32m[INFO][%s: %s:%d]"fmt, __FILE__, __FUNCTION__, __LINE__, ##arg);
#define print_err(fmt, arg...)      printf("\033[31m[ERR ][%s: %s:%d]"fmt, __FILE__, __FUNCTION__, __LINE__, ##arg);
#define print_pAddr(p1, p2)         printf("\033[37m[Addr compare][%s: %s:%d][0x%x :: 0x%x]\n", __FILE__, __FUNCTION__, __LINE__, p1,p2);
#define pBegin print_y("begin ..\n");
#define pEnd   print_y("end   ..\n");
#define print_buf(buf, len)     do{         \
    int i = 0;                              \
    print_info("");                     \
    printf("buf data = {");                 \
    for(i = 0; i < len; i++)                \
        printf("0x%02x, ", *((unsigned char*)buf+i));           \
    printf("}\n");                          \
}while(0)
#endif

#ifdef INVG_RELEASE
#define print_dbg(fmt, arg...)
#define print_info(fmt, arg...)
#define print_err(fmt, arg...)  
#define print_pAddr(p1, p2)
#define print_buf(buf, len)
#define pBegin
#define pEnd
#define print_y(fmt, arg...)
#endif


int bw_getFrame(unsigned char *buf, int len)
{
    pBegin;
    int     i = 0;    
    int     ret;
    
    unsigned char head[5] = {0x0d, 0x0a, '+', 'r','='};   /*头帧标志符号*/
    unsigned char tail[2] = {0x0d, 0x0a};   /*尾帧标志符号*/
    int           len_head = 5;
    int           len_tail = 2;
    unsigned char *pData   = NULL;
    int           iData    = 0;
    unsigned char *pDataEnd= NULL;
    int           bHasHead = 0;
    unsigned char Payload[MAX_SIZE]    = {0};
    int           lenPayload       = 0;
    unsigned char tmp[MAX_SIZE]         = {0};
    int           lentmp           = 0;
    
    
    
    print_dbg("[i, len] = [%d, %d]\n", i, len);
    if(len <= len_head + len_tail){
        memcpy(tmp, buf, len);
        lentmp += len;
        
        /* TODO: read time out */
        unsigned char more[6] = {'=',  0x33, 0x34, 0x35  ,0x0d, 0x0a};
        ret = 6;
        if(ret <= 0){
            return -1;
        }
        memcpy(&tmp[lentmp], more, ret);
        lentmp += ret;
        print_buf(tmp, lentmp);
        bw_getFrame(tmp, lentmp);
        return 0;
    }
   
    while(i < len){
        if(!bHasHead){
            ret = memcmp(head, &buf[i], len_head);
            if(ret == 0){
                i        += len_head;
                pData    = &buf[i];
                iData    = i;
                bHasHead = 1;
                continue;
            }else{
                
                goto next;
            }
        }else{
            ret = memcmp(tail, &buf[i], len_tail);
            if(ret == 0){
                pDataEnd = &buf[i];
                /* complete a frame */
                //print_dbg("[i] = [%d]\n", i);
                print_buf(pData, (pDataEnd-pData));
                i        += len_tail;
                if(i+1 < len){
                    print_dbg("has more\n");
                    /* reset var*/
                    bw_getFrame(&buf[i], len-i);
                    return 0;
                }
            }else{
                Payload[lenPayload++] = buf[i];
                goto next;
            }
        }
next:
        i++;
    }
    
    
    pEnd;
    return 0;
}

int main()
{      
    /*输入一个带头帧和尾帧的字符串*/
    //char str[MAX_SIZE];
    //printf("Please input str");
    //scanf("%s",str);
    unsigned char buf[100] =  {0x0d, 0x0a, '+', 'r'};
    unsigned char buf0[100] = {0x0d, 0x0a, '+', 'r', '='};
    unsigned char buf1[100] = {0x0d, 0x0a, '+', 'r','=',  0x33, 0x34, 0x35  ,0x0d, 0x0a};
    unsigned char buf2[100] = {0x0d, 0x0a, '+', 'r','=',  0x33, 0x34, 0x35  ,0x0d, 0x0a, 0x0d, 0x0a, '+', 'r','=',  0x77, 0x77,0x77  ,0x0d, 0x0a};
    unsigned char buf3[100] = {0x0d, 0x0a, '+', 'r','=',  0x33, 0x34, 0x35  ,0x0d, 0x0a, 
                               0x0d, 0x0a, '+', 'r','=',  0x77, 0x77, 0x77  ,0x0d, 0x0a,   
                               0x0d, 0x0a, '+', 'r','=',  0x00, 0x00, 0x00  ,0x0d, 0x0a,   
                               0x0d, 0x0a, '+', 'r','=',  0x88, 0x88, 0x88  ,0x0d, 0x0a};
    
    

//     bw_getFrame(buf, 4);
    bw_getFrame(buf0, 5);
//     bw_getFrame(buf3, 20);
    //bw_getFrame(buf2, 20);
    return 0;
}
