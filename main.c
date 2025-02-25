/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haruki <hkasamat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 19:03:32 by haruki            #+#    #+#             */
/*   Updated: 2025/02/21 17:40:00 by haruki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

extern char    **environ;

int ft_access(char *path)
{
    if(access(path, F_OK) == 0)
    {
        free(path);
        return 0;
    }
    return 1;
}
char *get_path(char *argv)
{
    char **paths;
    int i;
    char *path;


    i = 0;
    paths = ft_split(environ + 5, ':');
    if(!paths || !argv)
        return (perror("split failed"),NULL);
    while(paths[i] != NULL)
    {
        if(ft_access(ft_join(paths[i],argv)) == 0)
            path = paths[i];
        paths++;
    }
    return path;
}

int ft_exec(char *cmd)
{
    int i;
    char **args;
    char *path;

    i = 0;
    args = ft_split(cmd, ' ');
    path = get_path(args[0]);
    if(path && args)
        execve(path, args, NULL);
    while(args && args[i])
    {
        free(args[i]);
        i++;
    }
    free(args);
    free(path);
    return (perror("exec failed"),1);
}

void exec_cmd(char *argv)
{
    int fd[2];
    pid_t pid;

    if((pid = fork()) == -1)
        return (perror("fork failed"),1);
    if(pid == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        ft_exec(argv);
    }
    else if(pid > 0)
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        waitpid(pid, NULL, 0);
    }
}

int	main(int argc, char *argv[])
{
    int i;
    int infile;
    int outfile;

    if(argc >= 5)
    {
        i = 2;
        infile = open(argv[1], O_RDONLY | O_CREAT | O_TRUNC, 0644);
        outfile = open(argv[argc-1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(infile, STDIN_FILENO);
        while(i < argc - 2)
        {
            exec_cmd(argv[i]);
            i++;
        }
        dup2(outfile, STDOUT_FILENO);
        ft_exec(argv[i]);
    }
	return (0);
}
