/* linux-2.6.38.8/include/linux/compiler-gcc4.h */  
#define __compiler_offsetof(a,b) __builtin_offsetof(a,b)  

/* linux-2.6.38.8/include/linux/stddef.h */  
#undef offsetof  
#ifdef __compiler_offsetof  
#define offsetof(TYPE,MEMBER) __compiler_offsetof(TYPE,MEMBER)  
#else  
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)  
#endif  

/* linux-2.6.38.8/include/linux/kernel.h * 
 *  * container_of - cast a member of a structure out to the containing
 *  structure 
 *   * @ptr: the pointer to the member. 
 *    * @type:   the type of the container struct this is embedded in. 
 *     * @member:    the name of the member within the struct. 
 *      * 
 *       */  
#define container_of(ptr, type, member) ({      \  
		const typeof( ((type *)0)->member ) *__mptr = (ptr);    \  
		(type *)( (char *)__mptr - offsetof(type,member) );})  

#include <stdio.h>  

struct test_struct {  
	int num;  
	char ch;  
	float fl;  
};  

typedef struct _test_struct2 {  
	int num;  
	char *pCh;  
	float fl;  
} tTest_struct2;  

int main(void)  
{  
	struct test_struct init_test_struct = { 99, 'C', 59.12 };  

	char *char_ptr = &init_test_struct.ch;  

	struct test_struct *test_struct = container_of(char_ptr, struct test_struct, ch);  

	printf(" test_struct->num = %d\n test_struct->ch = %c\n test_struct->fl = %f\n",   
			test_struct->num, test_struct->ch, test_struct->fl);  


	printf("==============================\n");

	tTest_struct2 *p = (tTest_struct2 *)malloc(sizeof(tTest_struct2));
	char *pCh = "222";
	p->num = 111;
	p->pCh = pCh;
	p->fl = 33.33;
	
	char *pCh2 = pCh;
	tTest_struct2 *p2 = container_of(&pCh2, tTest_struct2, pCh);
	tTest_struct2 Test_struct3 = {444,"555",666.666};

	tTest_struct2 *p3 = container_of(&pCh, tTest_struct2, pCh);

	printf("&pCh     = 0x%x\n", &pCh);
	printf("&pCh2    = 0x%x\n", pCh2);
	printf("&p2->pCh = 0x%x\n", &p2->pCh);
	printf("==============================\n");
	printf("[p->num, p->pCh, p->fl] = [%d, %s, %f]\n", p->num, p->pCh, p->fl);
	printf("[p2->num, p2->pCh, p2->fl] = [%d, %s, %f]\n", p2->num, p2->pCh, p2->fl);
	printf("[p3->num, p3->pCh, p3->fl] = [%d, %s, %f]\n", p3->num, p3->pCh, p3->fl);
/*
	tTest_struct2 *p3 = (tTest_struct2 *)malloc(sizeof(tTest_struct2));
	tTest_struct2 *p3 = container_of(pCh2, tTest_struct2, pCh);
	printf("[p->num, p->pCh, p->fl] = [%d, %s, %f]\n", p3->num, p3->pCh, p3->fl);
*/
	return 0;  
}  
