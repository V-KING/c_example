#include "regexp.h"


// #define INVG_RELEASE

#ifdef INVG_RELEASE
    #define print_dbg(fmt, arg...)
    #define print_err(fmt, arg...)  printf(fmt, ##arg);
    #define print_info(fmt, arg...) printf(fmt, ##arg);
    #define print_pAddr(p1, p2)
    #define print_buf(buf, len)
    #define pBegin
    #define pEnd
    #define print_y(fmt, arg...) 
#else
    #if 0 
    #define print_dbg(fmt, arg...)
    #define print_info(fmt, arg...) printf(fmt, ##arg);
    #define print_err(fmt, arg...)  printf(fmt, ##arg);
    #define print_pAddr(p1, p2)
    #define print_buf(buf, len)
    #define pBegin
    #define pEnd
    #define print_y(fmt, arg...)
    #else
#include <malloc.h>
    //printf(KERN_NOTICE "request_irq:ret is %d\r\n",ret);
    #define print_dbg(fmt, arg...)      printf("\033[37m[DBG ][%s: %s:%d]"fmt, __FILE__, __FUNCTION__, __LINE__, ##arg);
    #define print_info(fmt, arg...)     printf("\033[32m[INFO][%s: %s:%d]"fmt, __FILE__, __FUNCTION__, __LINE__, ##arg);
    #define print_err(fmt, arg...)      printf("\033[31m[ERR ][%s: %s:%d]"fmt, __FILE__, __FUNCTION__, __LINE__, ##arg);
    #define print_pAddr(p1, p2)         printf("\033[37m[Addr compare][%s: %s:%d][0x%x :: 0x%x]\n", __FILE__, __FUNCTION__, __LINE__, p1,p2);
    #define print_y(fmt, arg...)        printf("\033[33m[DBG ][%s: %s:%d]"fmt, __FILE__, __FUNCTION__, __LINE__, ##arg);
    #define pBegin                      print_y("## Begin..\n")
    #define pEnd                        print_y("## E n d..\n")

    #define print_buf(buf, len)     do{         \
        int i = 0;                              \
        print_dbg("");                     \
        printf("buf data = {");                 \
        for(i = 0; i < len; i++)                \
            printf("0x%02x, ", *((unsigned char*)buf+i));           \
        printf("}\n");                          \
    }while(0)
    #endif
#endif

/*
    ability
    .（句点）    匹配任意的单个字符
    ^           匹配输入字符串的开头
    $           匹配输入字符串的结尾
    *           匹配前一个字符的零个或者多个出现
*/

/* match: search for regexp anywhere in text */
int match(char *regexp, char *text)
{
    if (regexp[0] == '^')
        return matchhere(regexp+1, text);
    do { /* must look even if string is empty */
        if (matchhere(regexp, text))
            return 1;
    } while (*text++ != '\0');
    return 0;
}

/* matchhere: search for regexp at beginning of text */
int matchhere(char *regexp, char *text)
{
    if (regexp[0] == '\0')
        return 1;
    if (regexp[1] == '*')
        return matchstar(regexp[0], regexp+2, text);
    if (regexp[0] == '$' && regexp[1] == '\0')
        return *text == '\0';
    if (*text!='\0' && (regexp[0]=='.' || regexp[0]==*text))
        return matchhere(regexp+1, text+1);
    return 0;
}

/* matchstar: search for c*regexp at beginning of text */
int matchstar(int c, char *regexp, char *text)
{
    do { /* a * matches zero or more instances */
    if (matchhere(regexp, text))
        return 1;
    } while (*text != '\0' && (*text++ == c || c == '.'));
    return 0;
}


#if 0
typedef struct _Re_String{
    unsigned char  *pBuf;
    unsigned short *n;
} tSRe_String;

tSRe_String* construct_Re_String(){
    tSRe_String *pRe_String;
    pRe_String       = (tSRe_String *)malloc(sizeof(tSRe_String)); 
    if(pRe_String == NULL){
        printf("construct_Re_String: malloc err\n");
        return NULL;
    }
    pRe_String->pBuf = (unsigned char*)malloc(pRe_String->n); 
    return pRe_String;
}

void destruct_Re_String(tSRe_String *pRe_String){
    free(pRe_String->pBuf);
    free(pRe_String);
}


typedef struct _Exp{
    unsigned char   regexp[50];
    unsigned char   text[50];
} tSExp;


tSExp Exp[10] = {
    {"com",  "123abc23144@qq.com"},
    {"qq",   "123abc23144@qq.com"},
    {"^123", "123abc23144@qq.com"},
    {"com$", "123abc23144@qq.com.xxx"},
    {"1com$", "123abc23144@qq.com.xxx"},
    {"^123a*com$", "123abc23144@qq.com.xxx"},
};
int main(){
    int ret;
    int i;
    for(i=0; i<10; i++){
        if(Exp[i].regexp == NULL && Exp[i].text == NULL){
            continue;
        }
        ret = match(Exp[i].regexp , Exp[i].text);
        print_dbg("ret = [%d, match(\"%s\", \"%s\")]\n", ret, Exp[i].regexp , Exp[i].text);
    }
    return 0;
}
#endif