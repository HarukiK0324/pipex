/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haruki <haruki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 19:03:32 by haruki            #+#    #+#             */
/*   Updated: 2025/02/21 17:03:11 by haruki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void exec_cmd(char *path,char *args,int *p[])
{
    if(execve(path, args, NULL) == -1)
        perror("execve failed");
    return;
}

int ft_exec(char *cmd,int *p[])
{
    int i;
    char **args;
    char *path;

    i = 0;
    args = ft_split(cmd, ' ');
    if(!args)
        return (perror("exec failed"),1);
    path = ft_join("/bin/",args[0]);
    if(!path)
        return (perror("exec failed"),1);
    exec_cmd(path,args,p);
    while(args[i])
    {
        free(args[i]);
        i++;
    }
    free(args);
    free(path);
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
            if(ft_exec(argv[i],&p) == 1)
                return (1);
        }else if(pid > 0)
        {
            wait(NULL);
            free(argv[i]);
        }
        i++;
    }
	return (0);
}
