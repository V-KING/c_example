
#include <stdio.h>
#include <assert.h>

#include <libxml2/libxml/xmlmemory.h>
#include <libxml2/libxml/parser.h>

#define DEFAULT_XML_FILE "phone_book.xml"

/*
 * @brief: 
 * @param doc:
 * @param cur:
 * @param str_IoReset_Flag: value to set
 * @param str_IoReset_Time: value to set
 */
static int set_RfidModule(xmlDocPtr doc, xmlNodePtr cur, char* str_IoReset_Flag, char* str_IoReset_Time)
{
    if(NULL == doc || NULL == cur){
        printf("doc||cur is null , return -1");
        return -1;
    }
    xmlChar *key;
    
    
    cur = cur->xmlChildrenNode;
    while (cur != NULL)
    {
        /*获取IoReset_Flag*/
        if ((!xmlStrcmp(cur->name, (const xmlChar *)"IoReset_Flag")))
        {
            printf("before: IoReset_Flag: %s\n", cur->content);
            //######set
            xmlNodeSetContent(cur, BAD_CAST str_IoReset_Flag);
            
            key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            printf("after : IoReset_Flag: %s\n", key);
            xmlFree(key);
            printf("-----\n");
        }
        /*获取IoReset_Time*/
        if ((!xmlStrcmp(cur->name, (const xmlChar *)"IoReset_Time")))
        {
            printf("before: IoReset_Time: %s\n", cur->content);
            //######set
            xmlNodeSetContent(cur, BAD_CAST str_IoReset_Time);
            
            key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            printf("after : IoReset_Time: %s\n", key);
            xmlFree(key);
            printf("-----\n");
        }
        cur = cur->next;
    }
    return 0;
}

static int set_SysConf808(const char *file_name)
{
	assert(file_name);

	xmlDocPtr doc;   //xml整个文档的树形结构
	xmlNodePtr cur;  //xml节点
	xmlChar *id;     //phone id

	//获取树形结构
	doc = xmlParseFile(file_name);
	if (doc == NULL)
	{
		fprintf(stderr, "Failed to parse xml file:%s\n", file_name);
		goto FAILED;
	}

	//获取根节点
	cur = xmlDocGetRootElement(doc);
	if (cur == NULL)
	{
		fprintf(stderr, "Root is empty.\n");
		goto FAILED;
	}

	if ((xmlStrcmp(cur->name, (const xmlChar *)"SysConf808")))
	{
		fprintf(stderr, "The root is not SysConf808.\n");
		goto FAILED;
	}

	//遍历处理根节点的每一个子节点
	cur = cur->xmlChildrenNode;
	while (cur != NULL)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"RfidModule")))
		{
			//id = xmlGetProp(cur, "id");
			//printf("id:%s\t",id);
			/*###### TODO:*/
			int ret = set_RfidModule(doc, cur, "qqq", "bbb");
            if (ret < 0){
                printf("err set_RfidModule\n");
                goto FAILED;
            }
		}
		cur = cur->next;
        printf("\n");
	}
	
	/*
     * save xml file*/
	xmlSaveFormatFileEnc(DEFAULT_XML_FILE, doc, "UTF-8", 1);
    
	xmlFreeDoc(doc);
	return 0;
FAILED:
	if (doc)
	{
		xmlFreeDoc(doc);
	}
	return -1;
}

int main(int argc, char*argv[])
{
	char *xml_file = DEFAULT_XML_FILE;

	if (argc == 2)
	{
		xml_file = argv[1];
	}

// 	if (set_SysConf808(xml_file, set_RfidModule) != 0)
    if (set_SysConf808(xml_file) != 0)
	{
		fprintf(stderr, "Failed to parse SysConf808 node.\n");
		return -1;
	}
    xmlCleanupParser();
	return 0;
}
