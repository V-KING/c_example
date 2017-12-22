
#include <stdio.h>
#include <assert.h>

#include <libxml2/libxml/xmlmemory.h>
#include <libxml2/libxml/parser.h>
#include "SysConf808.h"


#if 1
#define print_y(fmt, arg...)
#define print_dbg(fmt, arg...)
#define print_info(fmt, arg...)
#define print_err(fmt, arg...)
#define print_pAddr(p1, p2)
#else
#define print_y(fmt, arg...)        printf("\033[33m[DBG ][%s: %s:%d]"fmt, __FILE__, __FUNCTION__, __LINE__, ##arg);
#define print_dbg(fmt, arg...)      printf("\033[37m[DBG ][%s: %s:%d]"fmt, __FILE__, __FUNCTION__, __LINE__, ##arg);
#define print_info(fmt, arg...)     printf("\033[32m[INFO][%s: %s:%d]"fmt, __FILE__, __FUNCTION__, __LINE__, ##arg);
#define print_err(fmt, arg...)      printf("\033[31m[ERR ][%s: %s:%d]"fmt, __FILE__, __FUNCTION__, __LINE__, ##arg);
#define print_pAddr(p1, p2)         printf("\033[37m[Addr compare][%s: %s:%d][0x%x :: 0x%x]\n", __FILE__, __FUNCTION__, __LINE__, p1,p2);
#endif

#ifdef INVG_RELEASE
#define print_y(fmt, arg...)
#define print_dbg(fmt, arg...)
#define print_info(fmt, arg...)
#define print_err(fmt, arg...)
#define print_pAddr(p1, p2)
#endif

#define DEFAULT_XML_FILE "phone_book.xml"

static xmlDocPtr _Doc;
static volatile   xmlNodePtr  _Cur;


static char *malloc_str(const unsigned char * const pValue) {
    int len = strlen(pValue) + 1;
    unsigned char *p = (unsigned char *)malloc(len);
    memcpy(p, pValue, len);
    return p;
}

tSRfidModule *get_RfidModule() {
    print_y("#Begin..\n");
    xmlChar *key;
    tSRfidModule *pRfidModule = NULL;
    if ((!xmlStrcmp(_Cur->name, (const xmlChar *)"RfidModule"))) {
        pRfidModule = (tSRfidModule *)malloc(sizeof(tSRfidModule));
        _Cur = _Cur->xmlChildrenNode;
        while (_Cur != NULL) {
            //获取IoReset_Flag
            if ((!xmlStrcmp(_Cur->name, (const xmlChar *)"IoReset_Flag"))) {
                key = xmlNodeListGetString(_Doc, _Cur->xmlChildrenNode, 1);
                print_dbg("IoReset_Flag: %s\n", key);
                pRfidModule->str_IoReset_Flag = malloc_str((char *)key);
                print_dbg("IoReset_Flag: %s\n", pRfidModule->str_IoReset_Flag);
                xmlFree(key);
            }
            //获取tel
            if ((!xmlStrcmp(_Cur->name, (const xmlChar *)"IoReset_Time"))) {
                key = xmlNodeListGetString(_Doc, _Cur->xmlChildrenNode, 1);
                print_dbg("IoReset_Time: %s\n", key);
                pRfidModule->str_IoReset_Time = malloc_str((char *)key);
                print_dbg("IoReset_Flag: %s\n", pRfidModule->str_IoReset_Time);
                xmlFree(key);
            }
            _Cur = _Cur->next;
        }
    }
    print_y("#End..\n");
    return pRfidModule;
}

/*
 * @brief: this function will malloc a struct{} according 'void*(*pfGetSysConf808Child)()' return;
 * 这个函数会malloc一个结构体，这个结构体的类型就是pfGetSysConf808Child的正真返回值(注意void*可以转化成任何类型指针)
 * @param 'void*(*pfGetSysConf808Child)()': 一个函数指针，这里返回类型虽然是void*,但是你可以传任何类型函数指针，返回类型可以自定义，例如(tSRfidModule *)
 * @return: 根据这个函数指针的返回类型来进行强转;如果定义之后传进来的函数指针pfGetSysConf808Child返回类型是(tSRfidModule *)， 那么getSysConf808的返回值也是(tSRfidModule *)
 */
void *getSysConf808(const char *file_name, void *(*pfGetSysConf808Child)()) {
    assert(file_name);

    xmlDocPtr doc;   //xml整个文档的树形结构
    xmlNodePtr cur;  //xml节点
    //xmlChar *id;     //phone id
    //tSRfidModule *pRfidModule;
    void *pRfidModule;

    //获取树形结构
    doc = xmlParseFile(file_name);
    if (doc == NULL) {
        fprintf(stderr, "Failed to parse xml file:%s\n", file_name);
        goto FAILED;
    }

    //获取根节点
    cur = xmlDocGetRootElement(doc);
    if (cur == NULL) {
        fprintf(stderr, "Root is empty.\n");
        goto FAILED;
    }

    if ((xmlStrcmp(cur->name, (const xmlChar *)"SysConf808"))) {
        fprintf(stderr, "The root is not SysConf808.\n");
        goto FAILED;
    }

    //遍历处理根节点的每一个子节点
    cur = cur->xmlChildrenNode;
    _Doc = doc;
    _Cur = cur;
    while (cur != NULL) {
        // TODO: pfGetSysConf808Child:
        _Cur = cur;
        pRfidModule = pfGetSysConf808Child();
        if(NULL != pRfidModule) {

            return pRfidModule;
        }
        cur = cur->next;
        print_info("----\n");
    }
    xmlFreeDoc(doc);
    xmlCleanupParser();
    return NULL;

FAILED:
    if (doc) {
        xmlFreeDoc(doc);
    }
    xmlCleanupParser();
    return NULL;
}

#ifdef MAIN_RELEASE
int main(int argc, char*argv[]) {
    char *xml_file = DEFAULT_XML_FILE;

    if (argc == 2) {
        xml_file = argv[1];
    }

    tSRfidModule *pRfidModule = (tSRfidModule *)getSysConf808(xml_file, get_RfidModule);
    if(NULL != pRfidModule) {
        printf("[IoReset_Flag, IoReset_Time] = [%s, %s]\n", pRfidModule->str_IoReset_Flag, pRfidModule->str_IoReset_Time);
    }
    /*
     * TODO: */
    //destruct_RfidModule(pRfidModule);

    return 0;
}
#endif