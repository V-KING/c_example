#include <stdio.h>
#include <errno.h>
typedef struct _Box{
	int high;
} tSBox;

int main(int argc, const char *argv[])
{
	tSBox Box;
    Box.high = 100;
		
	printf("high = %d\n", Box.high);
	free(&Box);
	return 0;
}
