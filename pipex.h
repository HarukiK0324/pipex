/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haruki <haruki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 00:35:30 by hkasamat          #+#    #+#             */
/*   Updated: 2025/03/18 22:14:44 by haruki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

int				ft_strncmp(const char *s1, const char *s2, unsigned int n);
char			*ft_access(char *path, char *cmd);
char			*get_path(char *argv);
int				ft_exec(char *cmd);
void			exec_cmd(char *argv);
int				ft_strlen(char *s);
char			*ft_join(char *s1, char *s2);
unsigned int	count_words(const char *s, char c);
char			*substring(char const *s, unsigned int index, char c);
void			free_all(char **arr, unsigned int i);
char			**ft_split(char const *s, char c);

#endif
