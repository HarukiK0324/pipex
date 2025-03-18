/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haruki <haruki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 00:34:47 by hkasamat          #+#    #+#             */
/*   Updated: 2025/03/18 18:04:34 by haruki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

extern char	**environ;

char	*ft_access(char *path, char *cmd)
{
	char	*tmp;

	tmp = ft_join(path, "/");
	path = ft_join(tmp, cmd);
	if (tmp)
		free(tmp);
	if (access(path, F_OK) == 0)
		return (path);
	if (path)
		free(path);
	return (NULL);
}

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
	if (!paths || !argv)
		return (perror("split failed"), NULL);
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

int	main(int argc, char *argv[])
{
	int	i;
	int	infile;
	int	outfile;

	if (argc >= 5)
	{
		i = 2;
		if(ft_strncmp(argv[1], "here_doc", 8) == 0)
			outfile = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
		else
			outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		infile = open(argv[1], O_RDONLY);
		if (infile == -1 || outfile == -1)
			return (perror("open failed"), 1);
		dup2(infile, STDIN_FILENO);
		close(infile);
		while (++i < argc - 2)
			exec_cmd(argv[i]);
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
		ft_exec(argv[i]);
	}
	perror("usage: ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2");
	return (0);
}
