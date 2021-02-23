#include <stdlib.h>
#include <malloc.h>
#include <sys/queue.h>
#include <stdint.h>
#include <unistd.h>



#if 0
#define print_dbg(fmt, arg...)
#define print_info(fmt, arg...)
#define print_err(fmt, arg...)
#define __print_errno
#define print_pAddr(p1, p2)
#define print_buf(buf, len)
#define __pBegin
#define __pEnd
#define print_y(fmt, arg...)
#else
#define print_y(fmt, arg...)        printf("\033[33m[DBG ][%s: %s:%d]"fmt, __FILE__, __FUNCTION__, __LINE__, ##arg)
#define print_dbg(fmt, arg...)      printf("\033[37m[DBG ][%s: %s:%d]"fmt, __FILE__, __FUNCTION__, __LINE__, ##arg)
#define print_info(fmt, arg...)     printf("\033[32m[INFO][%s: %s:%d]"fmt, __FILE__, __FUNCTION__, __LINE__, ##arg)
#define print_err(fmt, arg...)      printf("\033[31m[ERR ][%s: %s:%d]"fmt, __FILE__, __FUNCTION__, __LINE__, ##arg)
#define __print_errno               print_err("[errno, err] = [%d, %s]\n", errno, strerror(errno));
#define print_pAddr(p1, p2)         printf("\033[37m[Addr compare][%s: %s:%d][0x%x :: 0x%x]\n", __FILE__, __FUNCTION__, __LINE__, p1,p2)
#define __pBegin print_y("begin ..\n");
#define __pEnd   print_y("end   ..\n");
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
#define __print_errno
#define print_pAddr(p1, p2)
#define print_buf(buf, len)
#define __pBegin
#define __pEnd
#define print_y(fmt, arg...)
#endif
/**
 * Converts u32 number into EBV format. The EBV is stored in parameter ebv.
 * Parameter len will be set to the length of data in ebv.
 * @param value u32 value to convert into EBV
 * @param ebv array to store the EBV
 * @param len number of data in ebv
 */
void u32ToEbv(uint32_t value, uint8_t *ebv, uint8_t *len)
{
    uint8_t lsbytefirst[6];  //additional byte for setting extension bit in loop
    uint8_t *buf = &lsbytefirst[0];
    int i;
    
    *len = 0;
    *buf = 0;
    do {
        (*buf) |= (uint8_t)(value & 0x7F);
        value = value >> 7;
        buf++;
        (*len)++;
        *buf = 0x80;   //set extension bit in next block
    } while (value > 0);
    
    //the EBV in buf starts with LSByte -> reorder the content into ebv array
    for (i=0; i<(*len); i++)
    {
        buf--;
        ebv[i] = *buf;
    }
}
int main(){
	uint32_t value = 129;
	 uint8_t ebv[5] ={0};
	  uint8_t len;
	  u32ToEbv( value,  ebv, &len);
      int i;
      for(i = 0; i < len; i++ ){
          printf("%02x ", ebv[i]); 
      }
      printf("\n==================\n");
}
