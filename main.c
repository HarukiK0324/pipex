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

void exec_cmd(char *path,char **args)
{
    if(execve(path, args, NULL) == -1)
        perror("execve failed");
    return;
}

int ft_exec(char *cmd)
{
    int i;
    char **args;
    char *path;

    i = 0;
    args = ft_split(cmd, ' ');
    if(!args)
        return (perror("exec failed"),1);
    path = ft_join("/usr/bin/",args[0]);
    if(!path)
        return (perror("exec failed"),1);
    exec_cmd(path,args);
    while(args[i])
    {
        free(args[i]);
        i++;
    }
    free(args);
    free(path);
    return (0);
}

int write_result(int *p, char *file)
{
    int fd;
    char *line;

    close(p[1]);
    fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd == -1)
        return (perror("open failed"),1);
    while(get_next_line(p[0],&line) > 0)
    {
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    close(fd);
    return (0);
}

int	main(int argc, char *argv[])
{
    int p[2];
    int i;
    pid_t pid;

    i = 2;
    if(pipe(p) == -1)
        return (perror("pipe failed"),1);
    dup2(p[1], 1);
    close(p[1]);
    dup2(p[0], 0);
    close(p[0]);
    argv[2] = ft_join_with_space(argv[2],argv[1]);
    while(i < argc-1)
    {
        if((pid = fork()) == -1)
            return (perror("fork failed"),1);
        if(pid == 0)
        {
            if(ft_exec(argv[i]) == 1)
                return (1);
        }else if(pid > 0)
        {
            wait(NULL);
            free(argv[i]);
        }
        i++;
    }
    if(write_result(&p, argv[argc-1]) == -1)
        return (perror("failed to write"),1);
	return (0);
}
