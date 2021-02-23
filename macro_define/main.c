#include<stddef.h>
#define STR(s)   #s
#define err_null(p)   if(NULL == p) printf("%s is null\n", STR(p))
int main(int argc, const char *argv[])
{
    void *p = NULL;	
	err_null(p);
    void *pTr = NULL;	
	err_null(pTr);
	return 0;
}
