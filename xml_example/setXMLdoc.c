
#include <stdio.h>
#include <assert.h>
#include <memory.h>

#include "libxml/xmlmemory.h"
#include "libxml/parser.h"
#include "libxml/xmlstring.h"
#include "SysConf808.h"


static xmlDocPtr _Doc;
static xmlNodePtr _Cur;

/*
 * @brief: set xml's node: SysConf808.Network
 * @return :
 *      0, success
 *      -1, err
 */
int set_Network(void *arg) {
    if(NULL == arg) {
        fprintf(stderr, "arg is null, return -1\n");
        return -1;
    }
    xmlChar *key;

    tSNetwork Network;
    memcpy(&Network, arg, sizeof(tSNetwork));

    char* str_NodeName     = Network.nodeName;
    char* ip = Network.ip;
    char* mac = Network.mac;
    if ((!xmlStrcmp(_Cur->name, (const xmlChar *) str_NodeName))) {
        _Cur = _Cur->xmlChildrenNode;
        while (_Cur != NULL) {
            /*获取IoReset_Flag*/
            if ((!xmlStrcmp(_Cur->name, (const xmlChar *)"ip"))) {
                key = xmlNodeListGetString(_Doc, _Cur->xmlChildrenNode, 1);
                printf("before: ip: %s\n", key);
                xmlFree(key);
                //######set
                xmlNodeSetContent(_Cur, BAD_CAST ip);

                key = xmlNodeListGetString(_Doc, _Cur->xmlChildrenNode, 1);
                printf("after : ip: %s\n", key);
                xmlFree(key);
                printf("-----\n");
            }
            /*获取IoReset_Time*/
            if ((!xmlStrcmp(_Cur->name, (const xmlChar *)"mac"))) {
                key = xmlNodeListGetString(_Doc, _Cur->xmlChildrenNode, 1);
                printf("before: mac: %s\n", key);
                xmlFree(key);                //######set
                xmlNodeSetContent(_Cur, BAD_CAST mac);

                key = xmlNodeListGetString(_Doc, _Cur->xmlChildrenNode, 1);
                printf("after : mac: %s\n", key);
                xmlFree(key);
                printf("-----\n");
            }
            _Cur = _Cur->next;
        }
    }

    return 0;
}
/*
 * @brief: set xml's node: SysConf808.RfidModule
 * @return :
 *      0, success
 *      -1, err
 */
int set_RfidModule(void *arg) {
    if(NULL == arg) {
        fprintf(stderr, "arg is null, return -1\n");
        return -1;
    }
    xmlChar *key;

    tSRfidModule RfidModule;
    memcpy(&RfidModule, arg, sizeof(tSRfidModule));

    char* str_NodeName     = RfidModule.nodeName;
    char* str_IoReset_Flag = RfidModule.str_IoReset_Flag;
    char* str_IoReset_Time = RfidModule.str_IoReset_Time;
    if ((!xmlStrcmp(_Cur->name, (const xmlChar *) str_NodeName))) {
        _Cur = _Cur->xmlChildrenNode;
        while (_Cur != NULL) {
            /*获取IoReset_Flag*/
            if ((!xmlStrcmp(_Cur->name, (const xmlChar *)"IoReset_Flag"))) {
                key = xmlNodeListGetString(_Doc, _Cur->xmlChildrenNode, 1);
                printf("before: IoReset_Flag: %s\n", key);
                xmlFree(key);                //######set
                xmlNodeSetContent(_Cur, BAD_CAST str_IoReset_Flag);

                key = xmlNodeListGetString(_Doc, _Cur->xmlChildrenNode, 1);
                printf("after : IoReset_Flag: %s\n", key);
                xmlFree(key);
                printf("-----\n");
            }
            /*获取IoReset_Time*/
            if ((!xmlStrcmp(_Cur->name, (const xmlChar *)"IoReset_Time"))) {
                key = xmlNodeListGetString(_Doc, _Cur->xmlChildrenNode, 1);
                printf("before: IoReset_Time: %s\n", key);
                xmlFree(key);                //######set
                xmlNodeSetContent(_Cur, BAD_CAST str_IoReset_Time);

                key = xmlNodeListGetString(_Doc, _Cur->xmlChildrenNode, 1);
                printf("after : IoReset_Time: %s\n", key);
                xmlFree(key);
                printf("-----\n");
            }
            _Cur = _Cur->next;
        }
    }

    return 0;
}

/*
 * @brief:
 * @param doc:
 * @param cur:
 * @param str_IoReset_Flag: value to set
 * @param str_IoReset_Time: value to set
 */
static int set_SysConf808Child(xmlDocPtr doc, xmlNodePtr cur, int(*setFunc)(void *), void *arg) {
    if(NULL == doc || NULL == cur || NULL == setFunc) {
        printf("doc||cur is null , return -1");
        return -1;
    }

    _Doc = doc;
    _Cur = cur;
    int ret = setFunc(arg);

    return ret;
}



int set_SysConf808(const char *file_name, int(*setFunc)(void *), void *arg) {
    assert(file_name);

    xmlDocPtr doc;   //xml整个文档的树形结构
    xmlNodePtr cur;  //xml节点
    //xmlChar *id;     //phone id

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
    while (cur != NULL) {
        /*###### TODO:*/
        int ret = set_SysConf808Child(doc, cur, setFunc, arg);
        if (ret < 0) {
            printf("err set_RfidModule\n");
            goto FAILED;
        }
        cur = cur->next;
        printf("\n");
    }

    /*
     * save xml file*/
    xmlSaveFormatFileEnc(DEFAULT_XML_FILE, doc, "UTF-8", 1);
    xmlFreeDoc(doc);
    xmlCleanupParser();
    return 0;

FAILED:
    if (doc) {
        xmlFreeDoc(doc);
    }
    xmlCleanupParser();
    return -1;
}

#ifdef MAIN_RELEASE
int main(int argc, char*argv[]) {
    char *xml_file = DEFAULT_XML_FILE;

    if (argc == 2) {
        xml_file = argv[1];
    }

    tSRfidModule RfidModule;
    //RfidModule.nodeName = "RfidModule";
    //RfidModule.str_IoReset_Flag = "yes";
    //RfidModule.str_IoReset_Time = "2000";
    memcpy(RfidModule.nodeName, "RfidModule", NAME_STR_LEN);
    memcpy(RfidModule.str_IoReset_Flag, "yes", NAME_STR_LEN);
    memcpy(RfidModule.str_IoReset_Time, "2000", NAME_STR_LEN);
    if (set_SysConf808(xml_file, set_RfidModule, &RfidModule) != 0) {
        fprintf(stderr, "Failed to set_RfidModule node.\n");
        return -1;
    }
    
    tSNetwork Network;
//     Network.nodeName = "Network";
//     Network.ip = "192.168.1.1";
//     Network.mac = "ff:ee:dd:aa";
    memcpy(Network.nodeName, "RfidModule", NAME_STR_LEN);
    memcpy(Network.ip, "192.168.1.1", NAME_STR_LEN);
    memcpy(Network.mac, "ff:ee:dd:aa", NAME_STR_LEN);
    if (set_SysConf808(xml_file, set_Network, &Network) != 0) {
        fprintf(stderr, "Failed to set_Network node.\n");
        return -1;
    }

    return 0;
}
#endif
