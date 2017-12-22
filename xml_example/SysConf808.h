#ifndef _SysConf808_h
#define _SysConf808_h

/****start <RfidModule>**********************
<SysConf808>
    <RfidModule>
        <IoReset_Flag>yes</IoReset_Flag>
        <IoReset_Time>fuck</IoReset_Time>
    </RfidModule>
</SysConf808>
*/
typedef struct RfidModule {
    /* Must have this menber*/
    char *nodeName;
    /* below according the need to add and define*/
    char* str_IoReset_Flag;
    char* str_IoReset_Time;
} tSRfidModule;
/****end  <RfidModule>**********************/


/****start <Network>**********************
<SysConf808>
    <Network>
        <ip>yes</ip>
        <mac>fuck</mac>
    </Network>
</SysConf808>
*/
typedef struct Network {
    /* Must have this menber*/
    char *nodeName;
    /* below according the need to add and define*/
    char* ip;
    char* mac;
} tSNetwork;
/****end  <Network>**********************/


#endif