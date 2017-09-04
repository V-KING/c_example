#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./getPidByName.h"

/*
 * shell excute cmd, return stardard string
 * return pid.
 */
int getPidByName(const char *name)
{

	char _name[15] = {0} ;
	if (strlen(name)>15) {
		strncpy(_name, name, 14);			
	}
	else{
		strcpy(_name,name);
	}
	int n = 0;
	char *temp = (char *)malloc(100);
	strcpy(temp,"ps -e | grep \'");
	strcat(temp,_name);
	strcat(temp, "\' | awk \'{print $1}\'");
		
	//FILE *fp = popen("ps -e | grep \'send_ARM_firmwa\' | awk \'{print $1}\'", "r");//打开管道，执行shell 命令
	FILE *fp = popen(temp, "r");//打开管道，执行shell 命令
	char buffer[10] = {0};
	while (NULL != fgets(buffer, 10, fp)) //逐行读取执行结果并打印
	{
		n++;	
	}
	if (n>1){
		return -1;
	}
	pclose(fp); //关闭返回的文件指针，注意不是用fclose噢
	return atoi(buffer);
}

#ifdef testmain
int main(int argc, const char *argv[])
{
	printf("pid = %d\n",getPidByName("send_ARM_firmwa"));
	return 0;
}
#endif

