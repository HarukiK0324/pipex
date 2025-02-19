#include "pipex.h"

int main()
{
    int pipefd[2];
    int pid;

    if(pipe(pipefd) == -1)
    {
        perror("pipe");
        return 1;
    }
    pid = fork();
    if(pid == -1)
    {
        perror("fork");
        return 1;
    }
    if(pid == 0)
    {
        close(pipefd[0]);
        dup2(pipefd[1], 1);
        close(pipefd[1]);
        char *args[] = {"wc", "Makefile", NULL};
        if(execve("/usr/bin/wc", args, NULL) == -1)
        {
            perror("execve");
        }
        return 0;
    }
    else if(pid > 0)
    {
        wait(NULL);
        close(pipefd[1]);
        dup2(pipefd[0], 0);
        close(pipefd[0]);
        char *args[] = {"wc", NULL};
        if(execve("/usr/bin/wc", args, NULL) == -1)
        {
            perror("execve");
        }
        return 0;
    }
    return 0;
}