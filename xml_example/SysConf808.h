#ifndef _SysConf808_h
#define _SysConf808_h

#include "libxml/xmlmemory.h"
#include "libxml/parser.h"
#include "libxml/xmlstring.h"

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

/* create or add*/
extern void set_RfidModule_item(RfidModule *RfidModule_item) ;
extern int add_RfidModule_to_SysConf808(xmlNodePtr root_node) ;
extern int create_SysConf808(const char *RfidModule_book_file) ;
extern int add_Childs_to_SysConf808(const char *RfidModule_book_file) ;
/* get*/
extern tSRfidModule *get_RfidModule() ;
extern void *getSysConf808(const char *file_name, void *(*pfGetSysConf808Child)()) ;
/* set or modify*/
extern int set_Network(void *arg) ;
extern int set_RfidModule(void *arg) ;
extern int set_SysConf808(const char *file_name, int(*setFunc)(void *), void *arg) ;


#endif