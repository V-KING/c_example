#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "./read_config_file.h"




static INIFileFmtDef  NETCFG_FMT[] = 
{
	{"DHCP", EN_TYPE_UCHAR, MEMBER_OFFSET(struct net_parameter, DHCP_switch)},
	{"address", EN_TYPE_IP, MEMBER_OFFSET(struct net_parameter, ip_addr)},
	{"netmask", EN_TYPE_IP, MEMBER_OFFSET(struct net_parameter, netmask)},
	{"gateway", EN_TYPE_IP, MEMBER_OFFSET(struct net_parameter, gateway)},
	{NULL, EN_TYPE_BLANK, 0}	// 以pszFmt = NULL为结尾标志
};  

struct net_parameter net_param = {
	.DHCP_switch = 0,
	.ip_addr= 0,
	.netmask= 0,
	.gateway= 0
};

/**
 * if 'line' have matched item in 'net_fmt_def', 
 * then return: index of matched item
 *     0: is DHCP
 *     1: is address
 *     2: is netmask
 *     3: is gateway
 *    -1: no matched item
 * */
int matched_cfg_item(char *line, INIFileFmtDef *net_fmt_def )
{
	int index = 0,ret = 0;

	while(net_fmt_def[index].pszFmt != NULL){
		if(strstr(line, "DHCP") != NULL){
			ret= 0;
		}
		else if(strstr(line, "address") != NULL ){
			ret = 1;
		}else if(strstr(line, "netmask") != NULL){
			ret = 2;
		}else if(strstr(line, "gateway") != NULL){
			ret = 3;
		}
		else{
			ret = -1;
		}
		index++;
	}
	printf("index = %d\n",ret);
	return ret;
}


void read_config_file(char *path, INIFileFmtDef *net_fmt_def, void *base_addr){
	char *line = NULL;
	size_t n;
	FILE *pFile = fopen(path, "r");
	char temp[50] = {0};
	char buf[50] = {0};
	int index = 0;
	int a;

	while ( getline(&line, &n, pFile) != -1)  {
		index = matched_cfg_item(line, net_fmt_def);
		switch(index){
		case 0:
			sprintf(temp, "%s =", net_fmt_def[index].pszFmt);
			strcat(temp, " %d");
			sscanf(line, temp, &a);
			*(UINT8 *)((char *)base_addr + net_fmt_def[index].lOffSet) = (UINT8)a;
			break;
		case 1:
		case 2:
		case 3:
			sprintf(temp, "%s =", net_fmt_def[index].pszFmt);
			strcat(temp, " %s");
			sscanf(line, temp, buf);
			//unsigned long ulh_addr = ntohl(inet_addr(buf)); // use host order to store
			unsigned long ulh_addr = (inet_addr(buf));// use net order to store
			*(UINT32 *)((char *)base_addr + net_fmt_def[index].lOffSet) = ulh_addr;
			break;
		default:
			break;
		}
		index++;
	}

	fclose(pFile);
}

//#define BASIC_TEST
#ifdef BASIC_TEST
int main(int argc, const char *argv[])
{
	//char buf[500];
	char *buf=NULL;
	buf = (char *)malloc(100);
	memset(buf,0, 100);

	char *str1=NULL,*str2=NULL,*str3=NULL;
	char *szTemp = " = %s";
	// must be corresponded one by one 
	int n = sscanf("DHCP = 0", "DHCP = %s", buf);// buf="0";
	printf("sucess convert %d bytes\n",n);
	printf("buf = %s\n",buf);
	/*
	// The str1 must have a alloc space,it mean must have a static addr
	int n = sscanf("str1 str2 str3","%s %s %s",str1,str2,str3);
	printf("sucess convert %d\n",n);
	printf("%s\t%s\t%s\n",str1,str2,str3);
	*/
	free(buf);
	return 0;
}
#endif

#define CONFIG_FILE_TEST
#ifdef CONFIG_FILE_TEST
int main(int argc, const char *argv[])
{
	/* Read the config file, add the parameter to 'net_param' */
	read_config_file("./config", NETCFG_FMT, (void *)&net_param);
	printf("-----------------------\n");
	printf("net_param = \n");
	printf("	.DHCP_switch= %u\n" , net_param.DHCP_switch);
	printf("	.ip_addr   = %s\n", inet_ntoa(*(struct in_addr *)&net_param.ip_addr));
	printf("	.netmask   = %s\n", inet_ntoa(*(struct in_addr *)&net_param.netmask));
	printf("	.gateway   = %s\n", inet_ntoa(*(struct in_addr *)&net_param.gateway));
	return 0;
}
#endif
