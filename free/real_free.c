/*
 * 对NULL 空指针free多次，就不会报错
 * 安全起见：释放之前
 *          0. pass a (char **str) to destruct
 *          1. 将那一块地址都设置为NULL, memset(addr, 0, size);
 *          2. addr = NULL;
 */

#include <stdio.h>
#include <errno.h>

#define TEST0
#define TEST1
#define TEST2
#define TEST3

void real_freePointer(char **a){
    printf("addr, a=%d\n",*a);
    free(*a);
    *a = NULL;
}
#if 1
int main(int argc, const char *argv[])
{
    char *a=NULL;
    a=(char *)malloc(10);
    strcpy(a,"testtest");
    printf("%s\n",a);

    //destruct
#ifdef TEST0
    memset(a, 0, 10);
#endif
    printf("before addr, a=%d\n",a);
    real_freePointer(&a);
//     free(a);//can't free twice
    if(NULL == a)
        printf("1111\n");
    else
        printf("2222=|%s|\n",a);//atfter free will not be NULL
    
    if(*a==0){
        printf("is null string, already set 0, be free. but some case: set value = 0\n");
    }


#ifdef TEST1
    a=NULL;
#endif

#ifdef TEST2
    free(NULL);
    free(NULL);
    free(NULL);
#endif
    free(a);
    free(a);



    return 0;
}
#endif

