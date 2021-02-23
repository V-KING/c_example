#include <sys/types.h>
    
#pragma pack(1)
typedef struct _CmdRfidReset {
    //unsigned char head;
    unsigned short int len;
    unsigned char cmdH;
    unsigned char cmdL;
    unsigned char setOrQurey;
    unsigned char IoReset_flag;
    unsigned char IoReset_time;
    unsigned char reserved[8];
    unsigned short int crc;
} CmdRfidReset;
typedef CmdRfidReset tSCmdRfidReset;
    

int main(){

    struct _CmdRfidResetUpload{
        unsigned char head;             //this is different to tSCmdRfidReset
        unsigned short int len;
        unsigned char cmdH;
        unsigned char cmdL;
        //unsigned char setOrQurey;   //this is different to tSCmdRfidReset
        unsigned char IoReset_flag;
        unsigned char IoReset_time;
        unsigned char reserved[8];
        unsigned short int crc;
    } CmdRfidResetUpload;

    

    printf("sizeof CmdRfidResetUpload = %d\n", sizeof(CmdRfidResetUpload));
    
    printf("sizeof RfidReset= %d\n", sizeof(tSCmdRfidReset));
    

    
    return 0;
}