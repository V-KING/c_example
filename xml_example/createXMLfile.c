/****************************************
 *@author: liubaolong, 20171222
 * ***************************************/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#include "libxml/parser.h"
#include "libxml/tree.h"
#include "libxml/xmlmemory.h"
#include "SysConf808.h"





//设置通讯录项
void set_RfidModule_item(RfidModule *RfidModule_item) {
    assert(RfidModule_item);

    snprintf(RfidModule_item->str_IoReset_Flag, NAME_STR_LEN, "%s", "1");
    snprintf(RfidModule_item->str_IoReset_Time, NAME_STR_LEN, "%s", "90");
}

//创建RfidModule节点
static xmlNodePtr create_RfidModule_node(const RfidModule *RfidModule_item) {
    assert(RfidModule_item);

    //char id[ID_STR_LEN] = {0};
    xmlNodePtr RfidModule_node = NULL;

    RfidModule_node = xmlNewNode(NULL, BAD_CAST"RfidModule");
    if (RfidModule_node == NULL) {
        fprintf(stderr, "Failed to create new node.\n");
        return NULL;
    }
    //设置属性
    //snprintf(id, ID_STR_LEN, "%d", RfidModule_item->id);
    //xmlNewProp(RfidModule_node, BAD_CAST"id", (xmlChar*)id);

    xmlNewChild(RfidModule_node, NULL, BAD_CAST"IoReset_Flag", (xmlChar *)RfidModule_item->str_IoReset_Flag);
    xmlNewChild(RfidModule_node, NULL, BAD_CAST"IoReset_Time", (xmlChar *)RfidModule_item->str_IoReset_Time);

    return RfidModule_node;
}

//向根节点中添加一个RfidModule节点
int add_RfidModule_to_SysConf808(xmlNodePtr root_node) {
    xmlNodePtr RfidModule_node = NULL;
    RfidModule *RfidModule_item = NULL;

    //创建一个新的RfidModule
    RfidModule_item = (RfidModule *)malloc(sizeof(RfidModule));
    if (RfidModule_item == NULL) {
        fprintf(stderr, "Failed to malloc memory.\n");
        return -1;
    }
    set_RfidModule_item(RfidModule_item);

    //创建一个RfidModule节点
    RfidModule_node = create_RfidModule_node(RfidModule_item);
    if (RfidModule_node == NULL) {
        fprintf(stderr, "Failed to create RfidModule node.\n");
        goto FAILED;
    }
    //根节点添加一个子节点
    xmlAddChild(root_node, RfidModule_node);
    free(RfidModule_item);

    return 0;
FAILED:
    if (RfidModule_item) {
        free(RfidModule_item);
    }
    return -1;
}

/*
 * @brief: create a default config file
 */
int create_SysConf808(const char *RfidModule_book_file) {
    assert(RfidModule_book_file);

    xmlDocPtr doc = NULL;
    xmlNodePtr root_node = NULL;

    //创建一个xml 文档
    doc = xmlNewDoc(BAD_CAST"1.0");
    if (doc == NULL) {
        fprintf(stderr, "Failed to new doc.\n");
        return -1;
    }

    //创建根节点
    root_node = xmlNewNode(NULL, BAD_CAST"SysConf808");
    if (root_node == NULL) {
        fprintf(stderr, "Failed to new root node.\n");
        goto FAILED;
    }
    //将根节点添加到文档中
    xmlDocSetRootElement(doc, root_node);

    if (add_RfidModule_to_SysConf808(root_node) != 0) {
        fprintf(stderr, "Failed to add a new RfidModule node.\n");
        goto FAILED;
    }
    //将文档保存到文件中，按照utf-8编码格式保存
    xmlSaveFormatFileEnc(RfidModule_book_file, doc, "UTF-8", 1);
    //xmlSaveFile("test.xml", doc);
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

int add_Childs_to_SysConf808(const char *RfidModule_book_file) {
    assert(RfidModule_book_file);

    xmlDocPtr doc = NULL;
    xmlNodePtr root_node = NULL;
    //xmlNodePtr RfidModule_node = NULL;
    //RfidModule *RfidModule_item = NULL;

    doc = xmlParseFile(RfidModule_book_file);
    if (doc == NULL) {
        fprintf(stderr, "Failed to parser xml file:%s\n", RfidModule_book_file);
        return -1;
    }

    root_node = xmlDocGetRootElement(doc);
    if (root_node == NULL) {
        fprintf(stderr, "Failed to get root node.\n");
        goto FAILED;
    }

    /* TODO: ### add customize define here*/
    if (add_RfidModule_to_SysConf808(root_node) != 0) {
        fprintf(stderr, "Failed to add a new RfidModule node.\n");
        goto FAILED;
    }
    //将文档保存到文件中，按照utf-8编码格式保存
    xmlSaveFormatFileEnc(RfidModule_book_file, doc, "UTF-8", 1);
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
int main(int argc, char *argv[]) {
    char *RfidModule_book_file = DEFAULT_XML_FILE;

    if (argc == 2) {
        RfidModule_book_file = argv[1];
    }

    if (access(RfidModule_book_file, F_OK) == 0) {
        //文件存在，添加一个新的RfidModule节点
        add_Childs_to_SysConf808(RfidModule_book_file);
    } else {
        //文件不存在，创建一个信息的RfidModule book
        create_SysConf808(RfidModule_book_file);
    }

    return 0;
}
#endif