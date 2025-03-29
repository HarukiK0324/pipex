/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haruki <haruki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 00:34:47 by hkasamat          #+#    #+#             */
/*   Updated: 2025/03/29 21:34:47 by haruki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd(char *argv, char *environ[])
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (perror("pipe failed"));
	pid = fork();
	if (pid == -1)
		return (perror("fork failed"));
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		ft_exec(argv, environ);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}
}

void	get_input(char *limiter)
{
	pid_t	pid;
	char	*line;
	int		fd[2];

	if (pipe(fd) == -1)
		return (perror("pipe failed"));
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		line = get_next_line(STDIN_FILENO);
		while (line)
		{
			if (ft_strcmp(line, limiter) == 0)
				exit(0);
			write(fd[1], line, ft_strlen(line));
			line = get_next_line(STDIN_FILENO);
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

void	here_doc(int argc, char *argv[], char *environ[])
{
	int	i;
	int	outfile;

	i = 3;
	outfile = open_file(argv[argc - 1], 2);
	get_input(argv[2]);
	while (i < argc - 2)
		exec_cmd(argv[i++], environ);
	dup2(outfile, STDOUT_FILENO);
	if (outfile == -1)
		exit(EXIT_FAILURE);
	ft_exec(argv[i], environ);
}

void	pipex(int argc, char *argv[], char *environ[])
{
	int	i;
	int	infile;
	int	outfile;

	i = 2;
	infile = open_file(argv[1], 0);
	if (infile == -1)
		infile = open("/dev/null", O_RDONLY);
	outfile = open_file(argv[argc - 1], 1);
	dup2(infile, STDIN_FILENO);
	while (i < argc - 2)
		exec_cmd(argv[i++], environ);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	if (outfile == -1)
		exit(EXIT_FAILURE);
	ft_exec(argv[i], environ);
}

int	main(int argc, char *argv[], char *environ[])
{
	if ((argc >= 5 && ft_strncmp(argv[1], "here_doc", 8) != 0) || argc >= 6)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
			here_doc(argc, argv, environ);
		else
			pipex(argc, argv, environ);
	}
	return (perror("usage: ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2"), 0);
}
