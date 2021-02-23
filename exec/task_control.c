#include <stdio.h>
#include <errno.h>
#include "./test/getPidByName.h"


void helpPrint()
{
		printf("######################################\n");
		printf("##  Useg: ./send_ARM_firmware 103\n");
		printf("##  Please select a num:\n");
		printf("##  1) start .... send_ARM_firmware\n");
		printf("##  2) kill  ....send_ARM_firmware pid\n");
		printf("######################################\n");
}


void start_task()
{
	if (fork() == 0)
	{
		printf("--------------1.  start_task_ls...");
		if(execl("../send_ARM_firmware/send_ARM_firmware","send_ARM_firmware","103",NULL)<0)
		{		
			perror("start_task_ls error\n");
			exit(errno);
		}
	}
}

void kill_task()
{
	if (fork() == 0)
	{
		printf("--------------2.  kill_send_ARM_firmware ...");
		/* Be carefull, the parameter's length can not bigger than 15 */
		int pid = getPidByName("send_ARM_firmwa");
		char strPid[10] = {0};
		sprintf(strPid,"%d",pid);
		printf("pid --> %s\n",strPid);
		if(execl("/bin/kill","kill","-9",strPid,NULL)<0)
		{		
			perror("kill_task_ls error\n");
			exit(errno);
		}
	}
}

int main(int argc, const char *argv[])
{

	int num;
	helpPrint();
	scanf("%d",&num);

	switch(num){
	case 1:
		start_task();
		break;
	case 2:
		kill_task();
		break;
	}
			
	return 0;
}
