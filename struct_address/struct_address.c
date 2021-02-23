#include <stdio.h>

#include <syslog.h>

#define print_dbg(fmt, arg...)		printf("[DBG][%s:%d %s]"fmt, __FILE__, __LINE__, __FUNCTION__, ##arg)
#define print_info(fmt, arg...)		printf("[INFO][%s:%d %s]"fmt, __FILE__, __LINE__, __FUNCTION__, ##arg)
#define print_err(fmt, arg...)		printf("[ERR][%s:%d %s]"fmt, __FILE__, __LINE__, __FUNCTION__, ##arg)

typedef struct Peaple
{
	/* member */
	int age;
	int nName;
	char *pName;
} tPeaple;


tPeaple Peaple = {
	.age =1,
	.pName = "liubaolong",
	.nName = 10,
};
tPeaple Peaple1 = {
	.age =2,
	.pName = "vk",
	.nName = 2,
};
tPeaple *pPeaple = NULL;

int main(int argc, const char *argv[])
{
	pPeaple = &Peaple1;	
	print_dbg("&Peaple :%d\n", &Peaple);	
	print_dbg("&Peaple1:%d\n", &Peaple1);	
	print_dbg("pPeaple :%d\n", pPeaple);	

	&Peaple = pPeaple;	
	print_dbg("-------\n");
	print_dbg("&Peaple :%d\n", &Peaple);	

	
	
	return 0;
}
