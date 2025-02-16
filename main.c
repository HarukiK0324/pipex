/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haruki <haruki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 19:03:32 by haruki            #+#    #+#             */
/*   Updated: 2025/02/16 12:55:08 by haruki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int ft_strlen(char *s)
{
    int i;

    i = 0;
    while(s[i])
        i++;
    return (i);
}



char *ft_join(char *s1, char *s2)
{
    char *str;
    int i;

    i = 0;
    str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    if (!str)
        return (NULL);
    while(s1[i] != '\0')
    {
        str[i] = s1[i];
        i++;
    }
    while(*s2 != '\0')
    {
        str[i] = *s2;
        i++;
        s2++;
    }
    str[i] = '\0';
    return (str);
}

int exec_cmd(char *path,char *args,int *p[])
{
    close(*p[1]);
    dup2(*p[0], 0);
    close(*p[0]);
    if(execve(path, args, NULL) == -1)
        return (perror("execve failed"),1);
    return (0);
}

int exec(char *cmd,int *p[])
{
    int i;
    char **args;
    char *path;

    i = 0;
    args = ft_split(cmd, ' ');
    if(!args)
        return (1);
    path = ft_join("/bin/",args[0]);
    if(!path)
        return (1);
    exec_cmd(path,args,p);
    while(args[i])
    {
        free(args[i]);
        i++;
    }
    free(args[i]);
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
    while(i < argc-1)
    {
        pid = fork();
        if(pid == -1)
            return (perror("fork failed"),1);
        if(pid == 0)
        {
            if(exec(argv[i],&p) == 1)
                return (1);
        }else if(pid > 0)
            free(argv[i]);
        i++;
    }

	return (0);
}
