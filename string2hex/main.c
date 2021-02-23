#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include "debug.h"

#define FIFO1           "/tmp/fifo.1"
#define FILE_MODE       (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)


int string2hex(unsigned char *str, unsigned char hex[])
{
    int len = strlen(str);
    char *p;
    long ret;
    
    for(int i = 0,j = 0;  i < len; i += 3, j++){
        ret = strtol(&str[i], &p, 16);
        hex[j] = ret;
        //print_dbg("hex[j] = %x\n", hex[j]);
    }
    return 0;
}

void hex2IrpFrame(unsigned char hex[], int len_hex, unsigned char buf[], int *len_buf)
{
    int i = 0;
    buf[i++] = 0x55;
    buf[i++] = (len_hex ) >> 8;
    buf[i++] = (len_hex );
    memcpy(&buf[i], hex, len_hex);
    i += len_hex;
    
    uint16_t crc = CRC16_CalculateBuf(buf+1, len_hex+2);
    buf[i++] = crc >> 8;
    buf[i++] = crc;
    
    *len_buf = i;
    
    
}

int main(int argc, const char *argv[])
{
    unsigned char *hex;
    int len;
    int ret;
    int fd_fifo;
    
    /* 4Create two FIFOs; OK if they already exist */
    if ((mkfifo(FIFO1, FILE_MODE) < 0) && (errno != EEXIST)){
        print_err("can't create %s", FIFO1);
    }
    
    fd_fifo = open(FIFO1, O_RDWR);
    
    FILE* fp = fopen("Tags.txt", "r");
    if(fp == NULL){
        print_err("err: %s\n", strerror(errno));
    }
    
    //send  to fifo.1
    char strline[2048]  = {0};
    char tmp[2048]      = {0};
    int  len_tmp = 0;
    int line = 0;
    while(fgets(strline, 2048, fp) != NULL){
//         print_dbg("line %d, line=%s\n", ++line, strline);
        len = (strlen(strline)-1)/3 + 1;
        hex = malloc(len);
        string2hex(strline, hex);
        
        hex2IrpFrame(hex, len, tmp, &len_tmp);
        
//         print_buf(tmp, len_tmp);
        ret = write(fd_fifo, tmp, len_tmp);
        if(ret < 0){
            print_err("err:  %s\n", strerror(errno));
        }
        free(hex);
        usleep(300000);
    }
    
    fclose(fp);
    close(fd_fifo);
    
//     while(2){
//         hex = malloc(10);
//         usleep(100000) ;
//         print_dbg("malloc 10 bytes\n");
//     }
    char *s = "ni" 
              "hao" 
              "a";
    
    return 0;
}
