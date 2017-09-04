#include <stdio.h>  
#include <strings.h>  
#include <stdarg.h>   
/**not base type*/
typedef struct
{
	unsigned char		nValue;
	char *				pValue;
} llrp_u8v_t;


int setXXX( char *fmt, ... )    
{    
	va_list argp;    
	int argno = 0;     
	llrp_u8v_t *		pDeviceSN;
	int					len;

	va_start(argp, fmt);    
	//while (1)    
	{    
		//1. llrp_u8v_t
		printf("1-------\n");
		pDeviceSN = (llrp_u8v_t *)va_arg(argp, llrp_u8v_t *);    
		printf("2-------sizeof=%d \n",sizeof(*pDeviceSN));
		printf("pDeviceSN->nValue = %d",pDeviceSN->nValue);
		printf("pDeviceSN->pValue = %s",pDeviceSN->pValue);
		//2. unsigned char 
		printf("3-------\n");
		len = va_arg(argp, int);    
		printf("4-------\n");
		printf("len				  = %d\n",len);
		

		argno++;    
	}
	va_end( argp );    
	return 0;    
}   

int demo( char *fmt, ... )    
{    
	va_list argp;    
	int argno = 0;     
	char *para;    
	va_start(argp, fmt);    
	while (1)    
	{    
		para = va_arg(argp, char *);    
		if (strcmp( para, "") == 0)    
			break;    
		printf("Parameter #%d is: %s\n", argno, para);    
		argno++;    
	}
	va_end( argp );    
	return 0;    
}   

int len = 77;
llrp_u8v_t DeviceSN = {
	.nValue = 10,
	.pValue = "invengo123",
};

int main()    
{    
	//demo("DEMO", "This", "is", "a", "demo!", "");    
	
	setXXX(&DeviceSN, len);
	return 0;   
}    

