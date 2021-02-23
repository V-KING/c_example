#include "stdio.h"
#include "math.h"
#include "string.h"
int str_is_mac_addr(char *str){    //判断字符串是否为 MAC 地址
	int flag = 1, count = 0;
	char *lst, *p;
	lst = (char *)malloc(20);
	strncpy(lst, str, 19);    //实现深拷贝
	p = strtok(lst, ":");
	while (p != NULL)
	{
		if (strlen(p) != 2) flag = 0;
		for (int i=0; i<strlen(p); i++)
		{
			char *tp;
			int x = 0;
			tp = "0123456789ABCDEFabcdef";    //所有 MAC 地址的字符
			while (*tp != '\0')
			{
				if(p[i] == *tp) break;    //MAC 地址中除 ':' 符号以外的字符都应该在 tp 中
				tp++;
				x++;
			}
			if (x == 22)    //MAC 地址中有不合规的字符
			{
				flag = 0;
				break;
			}
		}
		count++;
		p = strtok(NULL, ":");
	}
	free(lst);    //释放空间
	if(flag && count == 6) return 1;    //只有是 x:x:x:x:x:x 这种形式才返回 1
	else return 0;
}
 
int str_is_ip_addr(char *str){    //判断字符串是否为 IP 地址
	int flag = 1, count = 0;
	char *lst,*p;
	lst = (char *)malloc(20);
	strncpy(lst, str, 16);    //实现深拷贝
	p = strtok(lst, ".");
	while (p != NULL)
	{
		if (strlen(p) < 1 || strlen(p) > 3) flag = 0;    //确保 p 是一到三位数
		for (int i=0; i<strlen(p); i++)    //确保 p 的每个字符都是'0'-'9'
		{
			if (p[i] < '0' || p[i] > '9') flag = 0;
		}
		int x = atoi(p);
		if (x < 0 || x > 255) flag = 0;    //p 的范围须在0-255
		if (x < 10 && strlen(p) > 1) flag = 0;    //防止出现 01 和 001 这种值
		if (x < 100 && strlen(p) > 2) flag = 0;    //防止出现 011 这种值
		count++;
		p = strtok(NULL, ".");
	}
	free(lst);    //释放空间
	if (flag && count == 4) return 1;    //只有是 x.x.x.x 这种形式才返回 1
	else return 0;
}
 
int main(){
	char lst[20];
	gets(lst);
	int flagm = str_is_mac_addr(lst);
	int flagi = str_is_ip_addr(lst);
	char *prtfm, *prtfi, *cont;
	prtfm = (flagm == 1) ? "is mac address" : "is not mac address";
	prtfi = (flagi == 1) ? "is ip address" : "is not ip address";
	cont = (flagm == flagi) ? "and" : "but";
	printf("This str %s %s %s\n", prtfm, cont, prtfi);
	return 0;
}
