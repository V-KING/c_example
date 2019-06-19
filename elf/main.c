#include <stdio.h>

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

/*
I find that there is better method wiith objcopy: 
objcopy --add-section versection=version_text main main_version. 
And with 
"objdump -s -j versection main_version"
,the version can be retrieved
*/


/*
$ echo 'int main() { puts ("Hello world"); }' | gcc -x c - -c -o hello.o

$ echo "this is my special data" >version

$ objcopy --add-section .version=version --set-section-flags .version=noload,readonly hello.o hello2.o

$ gcc hello2.o -o hello

$ ./hello
Hello world

$ objdump -sj .version hello
*/


/*
 objcopy -I binary -O elf32-i386 -B i386 14_95_13.jpg image.o
 */

extern char _binary_version_start;
extern char _binary_version_end;
extern char _binary_version_size;

int main(int argc, const char *argv[])
{
    unsigned long s = (unsigned long)&_binary_version_size;
    printf("_binary_version_start :0x%lx\n",(unsigned long)&_binary_version_start);
    printf("_binary_version_end   :0x%lx\n",(unsigned long)&_binary_version_end);
    printf("_binary_version_size  :%ld\n",(unsigned long)&_binary_version_size);
    print_dbg("version = %s\n", (char *)&_binary_version_start);
    print_buf(&_binary_version_start, s);
    
	return 0;
}
