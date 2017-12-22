#ifndef _SysConf808_h
#define _SysConf808_h

#define DEFAULT_XML_FILE "phone_book.xml"

#define NAME_STR_LEN         32

/****start <RfidModule>**********************
<SysConf808>
    <RfidModule>
        <IoReset_Flag>yes</IoReset_Flag>
        <IoReset_Time>fuck</IoReset_Time>
    </RfidModule>
</SysConf808>
*/
typedef struct _RfidModule{
    /* Must have this menber*/
    char nodeName[NAME_STR_LEN];
    /* below according the need to add and define*/
    char str_IoReset_Flag[NAME_STR_LEN];
    char str_IoReset_Time[NAME_STR_LEN];
} RfidModule;
typedef RfidModule tSRfidModule;
/****end  <RfidModule>**********************/


/****start <Network>**********************
<SysConf808>
    <Network>
        <ip>yes</ip>
        <mac>fuck</mac>
    </Network>
</SysConf808>
*/
typedef struct _Network {
    /* Must have this menber*/
    char nodeName[NAME_STR_LEN];
    /* below according the need to add and define*/
    char ip[NAME_STR_LEN];
    char mac[NAME_STR_LEN];
} Network;
typedef Network tSNetwork;
/****end  <Network>**********************/


#endif