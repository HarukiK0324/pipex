/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkasamat <hkasamat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:40:55 by rkaga             #+#    #+#             */
/*   Updated: 2025/02/13 19:43:24 by hkasamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int *pipe_fd, char *cmd, char **envp)
{
	char	**cmd_args;

	close(pipe_fd[0]);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		perror("dup2");
	cmd_args = ft_split(cmd, ' ');
	if (execve(cmd_args[0], cmd_args, envp) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	second_process(int *pipe_fd, char *cmd, char **envp, char *file2)
{
	char	**cmd_args;
	int		file;

	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		perror("dup2");
	file = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(file, STDOUT_FILENO) == -1)
		perror("dup2");
	cmd_args = ft_split(cmd, ' ');
	if (execve(cmd_args[0], cmd_args, envp) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	int		file1;
	pid_t	child_pid1;
	pid_t	child_pid2;

	if (argc != 5)
		return (write(1, "Use format ./pipex file1 cmd1 cmd2 file2\n", 42), 1);
	file1 = open(argv[1], O_RDONLY);
	if (file1 == -1)
		return (perror("open"), 1);
	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), 1);
	child_pid1 = fork();
	if (child_pid1 == -1)
		return (perror("fork"), 1);
	if (child_pid1 == 0)
	{
		if (dup2(file1, STDIN_FILENO) == -1)
			perror("dup2");
		child_process(pipe_fd, argv[2], envp);
	}
	child_pid2 = fork();
	if (child_pid2 == -1)
		return (perror("fork"), 1);
	if (child_pid2 == 0)
		second_process(pipe_fd, argv[3], envp, argv[4]);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(child_pid1, NULL, 0);
	waitpid(child_pid2, NULL, 0);
	close(file1);
	return (0);
}
