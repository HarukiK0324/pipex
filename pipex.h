/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkasamat <hkasamat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:40:55 by rkaga             #+#    #+#             */
/*   Updated: 2025/02/13 19:36:51 by hkasamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

void	child_process(int *pipe_fd, char *cmd, char **envp);
void	second_process(int *pipe_fd, char *cmd, char **envp, char *file2);
int		ft_printf(const char *format, ...);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);

#endif
