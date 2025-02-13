/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkasamat <hkasamat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:02:50 by hkasamat          #+#    #+#             */
/*   Updated: 2025/02/13 19:14:45 by hkasamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	pid_t	pid;
	int		file;
	char	*command;
	char	*args[] = {"ls", "-l", NULL};

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		file = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		if (dup2(file, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		command = "/bin/ls";
		if (execve(command, args, NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
		close(file);
	}
	else
	{
		wait(NULL);
	}
	return (0);
}
