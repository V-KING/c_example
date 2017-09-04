#include<string.h>
#include<stdio.h>

int main()
{
	int len, nel;
	char query[] ="user_command=appleboy&test=1&test2=2";
	char *q, *name, *value;
	/* Parse into individualassignments */
	q = query;
	len = strlen(query);
	nel = 1;
	
	fprintf(stderr, "CGI[query string] : %s\n",query);
	fprintf(stderr, "=========================\n");
	char *tmp;
	while (tmp = strsep(&q, "&")){
		nel++;
		fprintf(stderr, "strsep return                 : %s\n", tmp);
		fprintf(stderr, "strsep's first arg is remained: %s\n", q);
	}
	
	fprintf(stderr, "=========================\n");
	fprintf(stderr, "CGI[nel string] : %d\n", nel);
	fprintf(stderr, "=========================\n");
	for (q = query; q< (query + len);) {
		value = name = q;
		/* Skip to next assignment */
		fprintf(stderr, "CGI[string] :%s\n", q);
		fprintf(stderr, "CGI[stringlen] : %d\n", strlen(q));
		fprintf(stderr, "CGI[address] :%p\n", q);
		for (q += strlen(q); q < (query +len) && !*q; q++);
		/* Assign variable  */
		name = strsep(&value,"=");
		fprintf(stderr, "CGI[name ] :%s\n", name);
		fprintf(stderr, "CGI[value] :%s\n", value);
		fprintf(stderr, "-----------------\n");
		
	}
	return 0;

}
