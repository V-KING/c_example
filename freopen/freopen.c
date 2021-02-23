/**
 * when you run this program. the screen not print.
 * but output into output.txt.
 * redirecting to output.txt
 * */
#include <stdio.h>
int main(void)
{
	int i;
	if (freopen ("output.txt", "w", stdout) == NULL)
		fprintf(stderr, "error redirecting stdout\n");
	for (i = 0; i < 10; i++)
		printf("%3d", i);
	printf("\n");
	fclose(stdout);
	return 0;
}
