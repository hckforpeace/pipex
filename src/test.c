#include "../include/pipex.h"

int main(int argc, char **argv, char **envp)
{
	if (argc == 1)
	{
		char *path = "/usr/bin/sleep";
		char *args[] = {"sleep", "2", NULL}; 
		int ret = execve(path, args, envp);
		printf("%d", ret);
	}
}