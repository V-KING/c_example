#ifndef  _REGEXP_H
#define  _REGEXP_H 

extern int matchstar(int c, char *regexp, char *text);
extern int matchhere(char *regexp, char *text);
export int match(char *regexp, char *text);

#endif