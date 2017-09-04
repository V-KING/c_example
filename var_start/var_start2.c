/* *
   int _vsnprintf(char* str, size_t size, const char* format, va_list ap);k
   参数说明:
   1. char *str [out],把生成的格式化的字符串存放在这里.
   2. size_t size [in], str可接受的最大字符数[1]  (非字节数，UNICODE一个字符两个字节),防止产生数组越界.
   3. const char *format [in], 指定输出格式的字符串，它决定了你需要提供的可变参数的类型、个数和顺序。
   4. va_list ap [in], va_list变量. va:variable-argument:可变参数
   函数功能：将可变参数格式化输出到一个字符数组。
   用法类似于vsprintf，不过加了size的限制，防止了内存溢出（size为str所指的存储空间的大小）。
   * */


#include <stdio.h>
#include <stdarg.h>

int mon_log(char* format, ...)
{
	char str_tmp[50];
	int i=0;
	va_list vArgList;                            //定义一个va_list型的变量,这个变量是指向参数的指针.
	va_start (vArgList, format);                 //用va_start宏初始化变量,这个宏的第二个参数是第一个可变参数的前一个参数,是一个固定的参数
	i=vsnprintf(str_tmp, 50, format, vArgList); //注意,不要漏掉前面的_
	printf(str_tmp);
	va_end(vArgList);                            //用va_end宏结束可变参数的获取
	return i;                                    //返回参数的字符个数中间有逗号间隔
}

void main()
{
	int i=mon_log("%s,%d,%d,%d\n","asd",2,3,4);
	printf("%d\n",i);
}
