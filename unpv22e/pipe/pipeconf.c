#include	"unpipc.h"

int
main(int argc, char **argv)
{
	if (argc != 2)
		err_quit("usage: pipeconf <pathname>");
    printf("_PC_PIPE_BUF = %d,%s\n", _PC_PIPE_BUF, argv[1]);
	printf("PIPE_BUF = %ld, OPEN_MAX = %ld\n",
		   Pathconf(argv[1], _PC_PIPE_BUF), Sysconf(_SC_OPEN_MAX));
	exit(0);
}
