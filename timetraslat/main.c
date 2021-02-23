#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

#include <stdio.h>
#include <errno.h>

#define print_buf(buf, len)     do{         \
    int i = 0;                              \
    print_info("");                     \
    printf("buf data = {");                 \
    for(i = 0; i < len; i++)                \
        printf("0x%02x, ", *(buf+i));           \
    printf("}\n");                          \
}while(0)


#if 0
#define print_dbg(fmt, arg...)
#define print_info(fmt, arg...)
#define print_err(fmt, arg...)
#else
#define print_dbg(fmt, arg...)      printf("\033[37m[DBG ][%s: %s:%d]"fmt, __FILE__, __FUNCTION__, __LINE__, ##arg);
#define print_info(fmt, arg...)     printf("\033[32m[INFO][%s: %s:%d]"fmt, __FILE__, __FUNCTION__, __LINE__, ##arg);
#define print_err(fmt, arg...)      printf("\033[31m[ERR ][%s: %s:%d]"fmt, __FILE__, __FUNCTION__, __LINE__, ##arg);
#define print_pAddr(p1, p2)         printf("\033[37m[Addr compare][%s: %s:%d][0x%x :: 0x%x]\n", __FILE__, __FUNCTION__, __LINE__, p1,p2);
#endif

#ifdef INVG_RELEASE
#define print_dbg(fmt, arg...)
#define print_info(fmt, arg...)
#define print_err(fmt, arg...)
#define print_pAddr(p1, p2)
#endif


/*
 * 2018-01-12, 11:22:33
 * 33 22 11 12 01 18
 */
void put_time(unsigned char *data_utc)
{
    long int curr_time = 0;
    struct tm * t;

    time(&curr_time);

    printf("time=%ld\n", curr_time);

    t = localtime(&curr_time);
    
    printf("%d-%d-%d", t->tm_year+1900, t->tm_mon+1, t->tm_mday);
    printf("  ");
    printf("%d:%d:%d\n", t->tm_hour, t->tm_min, t->tm_sec);  
    data_utc[0] = t->tm_sec;
    data_utc[1] = t->tm_min;
    data_utc[2] = t->tm_hour;
    data_utc[3] = t->tm_mday;
    data_utc[4] = t->tm_mon+1;
    data_utc[5] = (t->tm_year+1900)%100;
}

void main(void)
{
   unsigned char data_utc[8];
   //put_time(data_utc);
    //print_buf(data_utc, 6);
    
//     struct timeval tv;
//     struct timezone tz;
//     gettimeofday(&tv, &tz);
//     printf("tv_sec; %d\n", tv.tv_sec);
//     printf("tv_usec; %d\n", tv.tv_usec);
//     printf("tz_minuteswest; %d\n", tz.tz_minuteswest);
//     printf("tz_dsttime, %d\n", tz.tz_dsttime);
        //unsigned char param_buf[]={0x5a, 0x58, 0x6c, 0x2f, 0x00, 0x0d, 0x52, 0x28, };//2018-08-08 11:22:33
        unsigned char param_buf[]= {0x5a, 0x58, 0x6d, 0x95, 0x00, 0x06, 0xc6, 0x60, };//2018-08-08 11:22:33
        struct timeval currentv;
        int RESvalue;

        struct timezone tz;
//         tz.tz_minuteswest = -60*8;
        tz.tz_minuteswest = -60*7;
        tz.tz_dsttime = 0;
         
        print_buf(param_buf, 8);
        currentv.tv_sec = param_buf[0]<<24|param_buf[1]<<16|param_buf[2]<<8|param_buf[3];
        currentv.tv_usec = param_buf[4]<<24|param_buf[5]<<16|param_buf[6]<<8|param_buf[7];
        
        //RESvalue=settimeofday(&currentv,NULL);
        RESvalue=settimeofday(&currentv, &tz);
        
        system("/sbin/hwclock -w -u");
        
        long int curr_time = 0;
        struct tm * t;
        time(&curr_time);
        printf("time=%ld\n", curr_time);
        t = localtime(&curr_time);
        printf("%d-%d-%d", t->tm_year+1900, t->tm_mon+1, t->tm_mday);
        printf("  ");
        printf("%d:%d:%d\n", t->tm_hour, t->tm_min, t->tm_sec);  
        
//         char tmp[50];
//         //sprintf(tmp, "%d-%d-%d %d:%d:%d", t->tm_year+1900, t->tm_mon+1, t->tm_mday, );
//    
//         if (fork() == 0) {
//             if(execl("/bin/date","date","-s","2008-08-08 12:00:00",NULL)<0) {       
//                 perror("execl error!\n");
//                 exit(errno);
//             }
//             exit(0);
//         }
   
   
// 	printf("%s", ctime(&curr_time));
// 
// 	printf("%s", asctime(t));
}
