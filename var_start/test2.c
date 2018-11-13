#include <stdio.h>
#include <stdarg.h>

void PrintLines(char *first,...)
{
    char *str;
    va_list v1;
    str = first;
    va_start(v1,first);
    do 
    {
        printf("%s\n",str);
        str=va_arg(v1,char*);
    } while (str != NULL );
    va_end(v1);
}

int main(int argc, char* argv[])
{
    PrintLines("First","Second","Third","Fourth",NULL);
    return 0;
}
