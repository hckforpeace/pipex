#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
    int fd[2];
    int ret = pipe(fd);

    int outfile = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outfile < 0) {
        perror("open outfile");
        exit(EXIT_FAILURE);
    }
    if (ret < 0) {
        perror("pipe");
        return (EXIT_FAILURE);
    }

    pid_t pid1 = fork();
    if (pid1 == 0) {
        // First child process: execute `cat`
        close(fd[0]); // Close unused read end of the pipe
        
        // Redirect stdin to /dev/stdin
        int dev_stdin = open("/dev/stdin", O_RDONLY);
        if (dev_stdin < 0) {
            perror("open /dev/stdin");
            exit(EXIT_FAILURE);
        }
        dup2(dev_stdin, STDIN_FILENO);
        close(dev_stdin);

        // Redirect stdout to the write end of the pipe
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]); // Close the write end of the pipe after duplicating

        char *args[] = {"cat", NULL};
        execve("/usr/bin/cat", args, envp);
        // If execve fails
        perror("execve cat");
        exit(EXIT_FAILURE);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        // Second child process: execute `ls`
        close(fd[1]); // Close unused write end of the pipe

        // Redirect stdin to the read end of the pipe
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]); // Close the read end of the pipe after duplicating

        // Redirect stdout to outfile
        dup2(outfile, STDOUT_FILENO);
        close(outfile);

        char *args[] = {"ls", NULL};
        execve("/usr/bin/ls", args, envp);
        // If execve fails
        perror("execve ls");
        exit(EXIT_FAILURE);
    }

    // Parent process: close both ends of the pipe and wait for children to finish
    close(fd[0]);
    close(fd[1]);

    waitpid(pid1, NULL, 0); // Wait for the first child
    fprintf(stderr, "first child ended\n");
    waitpid(pid2, NULL, 0); // Wait for the second child
    fprintf(stderr, "second child ended\n");
    return 0;
}
