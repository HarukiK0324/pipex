/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haruki <haruki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 00:35:30 by hkasamat          #+#    #+#             */
/*   Updated: 2025/03/29 18:10:42 by haruki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

int				ft_strncmp(const char *s1, const char *s2, unsigned int n);
char			*ft_access(char *path, char *cmd);
char			*get_path(char *argv);
void				ft_exec(char *cmd);
void			exec_cmd(char *argv);
int				ft_strlen(char *s);
char			*ft_join(char *s1, char *s2);
unsigned int	count_words(const char *s, char c);
char			*substring(char const *s, unsigned int index, char c);
void			free_all(char **arr, unsigned int i);
char			**ft_split(char const *s, char c);
void			cmd_error(char *msg, char *cmd);
int	open_file(char *argv, int i);
void here_doc(int argc, char *argv[]);
void	get_input(char *limiter);

#endif
