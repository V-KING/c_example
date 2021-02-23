#include <stdio.h>  
#include <stdlib.h>  

#define DEBUG1( fmt,  arg  ... )  \  
do{printf("[DEBUG] " fmt ,  ##arg );  }while(0);  

#define DEBUG2( fmt,  arg  ... ) \  
do{printf("[%s: %s:%d]" fmt ,\  
		__FILE__, __FUNCTION__, __LINE__,  ##arg );  }while(0);  

#define debug_black( fmt,  arg  ... )   \  
do{printf("\033[30m""[%s: %s:%d]" fmt"\033[0m" ,\  
		__FILE__, __FUNCTION__, __LINE__,  ##arg );  }while(0);  

#define debug_red( fmt,  arg  ... )   \  
do{printf("\033[31m""[%s: %s:%d]" fmt"\033[0m" ,\  
		__FILE__, __FUNCTION__, __LINE__,  ##arg );  }while(0);  

#define debug_grean( fmt,  arg  ... )   \  
do{printf("\033[32m""[%s: %s:%d]" fmt"\033[0m" , \
		__FILE__, __FUNCTION__, __LINE__,  ##arg );  }while(0);  

#define debug_yellow( fmt,  arg  ... )   \  
do{printf("\033[33m""[%s: %s:%d]" fmt"\033[0m" ,\  
		__FILE__, __FUNCTION__, __LINE__,  ##arg );  }while(0);  

#define debug_blue( fmt,  arg  ... )   \  
do{printf("\033[34m""[%s: %s:%d]" fmt"\033[0m" ,\  
		__FILE__, __FUNCTION__, __LINE__,  ##arg );  }while(0);  

#define debug_purple( fmt,  arg  ... )   \  
do{printf("\033[35m""[%s: %s:%d]" fmt"\033[0m" ,\  
		__FILE__, __FUNCTION__, __LINE__,  ##arg );  }while(0);  

#define debug_cyan( fmt,  arg  ... )    \  
do{printf("\033[36m""[%s: %s:%d]" fmt"\033[0m" ,\  
		__FILE__, __FUNCTION__, __LINE__,  ##arg );  }while(0);  

int main()  
{  
	printf("I AM IN macro.c\n");  

	DEBUG1("I AM IN macro.c\n");  
	DEBUG2("I AM IN macro.c\n");  

	debug_black("I AM IN macro.c\n");  
	debug_red("I AM IN macro.c\n");  
	debug_grean("I AM IN macro.c\n");  
	debug_blue("I AM IN macro.c\n");  

	return 0;  
}  
