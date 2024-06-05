#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include "include/pipex.h"
#include <fcntl.h>

int	main()
{
	char *str[] = {"ls", NULL};
	execve("/usr/bin/ls", str, NULL);
	printf("\n===%d", errno);
}
