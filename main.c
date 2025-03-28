/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haruki <haruki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 00:34:47 by hkasamat          #+#    #+#             */
/*   Updated: 2025/03/28 17:12:46 by haruki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

extern char	**environ;

char	*get_path(char *argv)
{
	char	**paths;
	int		i;
	char	*path;

	i = 0;
	while (*(++environ) != NULL)
	{
		if (ft_strncmp(*environ, "PATH=", 5) == 0)
			break ;
	}
	paths = ft_split(*environ + 5, ':');
	while (paths[i] != NULL)
	{
		path = ft_access(paths[i], argv);
		if (path != NULL)
			break ;
		i++;
	}
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
	if(path == NULL)
		cmd_error("zsh: command not found: ", argv);
	return (path);
}

int	ft_exec(char *cmd)
{
	int		i;
	char	**args;
	char	*path;

	i = 0;
	args = ft_split(cmd, ' ');
	path = get_path(args[0]);
	if (path && args)
		execve(path, args, NULL);
	while (args && args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
	free(path);
	return (perror("exec failed"), 1);
}

void	exec_cmd(char *argv)
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
		close(fd[1]);
		ft_exec(argv);
	}
	else if (pid > 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		waitpid(pid, NULL, 0);
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
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
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

void here_doc(int argc, char *argv[])
{
	int i;
	int outfile;


	i = 3;
	outfile = open_file(argv[argc - 1], 2);
	get_input(argv[2]);
	while (i < argc - 2)
		exec_cmd(argv[i++]);
	dup2(outfile, STDOUT_FILENO);
	ft_exec(argv[i]);
	if(outfile == -1)
		exit(EXIT_FAILURE);
}

int	main(int argc, char *argv[])
{
	int	i;
	int	infile;
	int	outfile;

	if ((ft_strncmp(argv[1], "here_doc", 8) != 0 && argc >= 5) || argc >= 6)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
			here_doc(argc, argv);
		else
		{
			i = 2;
			infile = open_file(argv[1],0);
			if(infile == -1)
				exit(EXIT_FAILURE);
			outfile = open_file(argv[argc - 1],1);
			dup2(infile, STDIN_FILENO);
			while (i < argc - 2)
				exec_cmd(argv[i++]);
			dup2(outfile, STDOUT_FILENO);
			ft_exec(argv[i]);
			if(outfile == -1)
				exit(EXIT_FAILURE);
		}
	}
	return (perror("usage: ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2"), 1);
}
