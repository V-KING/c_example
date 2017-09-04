#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct St{
	int id;
}St;

St* returnPointer(void) 
{ 
	St* p=calloc(1,sizeof(St));
	p->id=100;
	return p;
} 

St returnStruct(void) 
{ 
	St st;
	st.id=100;
	return st;
} 

int main()
{
	St st1=*(returnPointer()); 
	St st2=returnStruct(); 
	printf("%d\n", st1.id);
	printf("%d\n", st2.id);

	return 0;
}
